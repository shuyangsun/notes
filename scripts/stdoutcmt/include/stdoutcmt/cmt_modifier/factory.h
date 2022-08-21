#ifndef STDOUTCMT_INCLUDE_STDOUTCMT_CMT_MODIFIER_FACTORY_H_
#define STDOUTCMT_INCLUDE_STDOUTCMT_CMT_MODIFIER_FACTORY_H_

#include <cassert>
#include <cmath>
#include <memory>
#include <utility>
#include <tuple>

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

auto FindCommentBlocks(const std::vector<std::pair<std::string_view, std::string>>& lines) -> std::vector<std::tuple<std::size_t, std::size_t, std::size_t>> {
  std::vector<std::tuple<std::size_t, std::size_t, std::size_t>> res{}; // start_pos, stop_pos, max_len
  std::optional<std::size_t> block_start;
  std::optional<std::size_t> block_max;
  for (std::size_t i{0}; i < lines.size(); ++i) {
    const std::string_view& code{std::get<0>(lines[i])};
    const std::string_view& cmt{std::get<1>(lines[i])};
    const std::string_view code_no_ws{util::TrimWS(code)};
    const std::string_view cmt_no_ws{util::TrimWS(cmt)};
    const bool is_end_of_block{code_no_ws.empty() || cmt_no_ws.empty()};
    if (is_end_of_block) {
      if (block_start.has_value()) {
        res.emplace_back(std::make_tuple(block_start.value(), i, block_max.value()));
        block_start.reset();
        block_max.reset();
      }
      continue;
    }
    const std::size_t code_len{util::TrimPostfixWS(code).length()};
    if (!block_start.has_value()) {
      block_start = i;
      block_max = code_len;
    }
    block_max = std::max(block_max.value(), code_len);
  }
  if (block_start.has_value()) {
    res.emplace_back(std::make_tuple(block_start.value(), lines.size(), block_max.value()));
  }
  return res;
}

void UpdateCommentsToBeAligned(std::vector<std::pair<std::string_view, std::string>>& lines) {
  std::vector<std::tuple<std::size_t, std::size_t, std::size_t>> blocks{FindCommentBlocks((lines))};
  for (const auto& [start_pos, stop_pos, max_len]: blocks) {
    for (std::size_t i{start_pos}; i < stop_pos; ++i) {
      const std::string_view code{util::TrimPostfixWS(std::get<0>(lines[i]))};
      assert(code.length() <= max_len);
      const std::size_t space_count{max_len + 1 - code.length()};
      std::stringstream ss{};
      for (std::size_t j{0}; j < space_count; ++j) {
        ss << ' ';
      }
      ss << util::TrimWS(std::get<1>(lines[i]));
      const std::string cmt{ss.str()};
      lines[i] = std::make_pair(code, cmt);
    }
  }
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
