#ifndef STDOUTCMT_INCLUDE_STDOUTCMT_CMT_MODIFIER_FACTORY_H_
#define STDOUTCMT_INCLUDE_STDOUTCMT_CMT_MODIFIER_FACTORY_H_

#include <utility>
#include <memory>

#include "stdoutcmt/cmt_modifier/interface.h"
#include "stdoutcmt/cmt_modifier/cpp.h"
#include "stdoutcmt/src_type/src_type.h"

namespace outcmt::src {

namespace {

[[nodiscard]] std::vector<std::pair<std::string_view, std::string>> ReplaceComments(
    const ParsedComments& lines,
    const std::map<std::size_t, std::string_view>& new_comments,
    const std::string_view& cmt_header
) {
  std::unordered_set<std::size_t> prefix_space{};
  for (const auto& [line_num, cmt]: new_comments) {
    if (util::TrimWS(cmt).empty()) {
      continue;
    }
    const auto& cur_line = lines[line_num - 1];
    if (!util::EndsWith(std::get<0>(cur_line), " ")) {
      prefix_space.emplace(line_num);
    }
  }
  std::vector<std::pair<std::string_view, std::string>> result{};
  result.reserve(lines.size());
  for (std::size_t i{0}; i < lines.size(); ++i) {
    const std::string_view& code {std::get<0>(lines[i])};
    const std::string_view& old_cmt {std::get<1>(lines[i])};
    if (new_comments.find(i + 1) == new_comments.end()) {
      result.emplace_back(std::make_pair(code, old_cmt));
    } else {
      std::stringstream ss{};
      if (prefix_space.find(i + 1) != prefix_space.end()) {
        ss << ' ';
      }
      ss << cmt_header;
      ss << new_comments.at(i + 1);
      result.emplace_back(std::make_pair(code, ss.str()));
    }
  }
  return result;
}

void UpdateCommentsToBeAligned(std::vector<std::pair<std::string_view, std::string>>& lines) {
  // TODO: impl
}

}  // anonymous namespace


class CmtModifier {
 public:
  CmtModifier() = delete;
  explicit CmtModifier(std::unique_ptr<ICmtParser>&& cmt_parser, const std::string_view& cmt_header):
    cmt_parser_{std::move(cmt_parser)},
    cmt_header_{cmt_header}
    {}
  ~CmtModifier() = default;

  [[nodiscard]] std::string ParseAndReplaceComments(
      const std::string_view& content,
      const std::map<std::size_t, std::string_view>& new_comments,
      const bool align_comments
  ) const {
    const ParsedComments parsed{this->cmt_parser_->ParseComments(content)};
    std::vector<std::pair<std::string_view, std::string>> replaced_cmt{ReplaceComments(parsed, new_comments, this->cmt_header_)};
    if (align_comments) {
      UpdateCommentsToBeAligned(replaced_cmt);
    }
    std::stringstream ss{};
    std::size_t i{0};
    for (auto&& [code, cmt]: std::move(replaced_cmt)) {
      ss << code << cmt;
      if (i < parsed.size() - 1) {
        ss << '\n';
      }
      ++i;
    }
    return ss.str();
  }
 private:
  std::unique_ptr<ICmtParser> cmt_parser_;
  std::string cmt_header_;
};

class CmtModifierFactory {
 public:
  CmtModifierFactory() = default;
  ~CmtModifierFactory() = default;

  [[nodiscard]] CmtModifier BuildModifier(const FileType& file_type) const {
    switch (file_type) {
      case FileType::Cpp:
        return CmtModifier(std::make_unique<CmtParserCpp>(), "// ");
      default:
        throw std::invalid_argument("Unrecognized file type.");
    }
  }
};

}  // namespace outcmt::src

#endif  // STDOUTCMT_INCLUDE_STDOUTCMT_CMT_MODIFIER_FACTORY_H_
