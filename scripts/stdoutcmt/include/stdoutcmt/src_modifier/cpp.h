#ifndef STDOUTCMT_INCLUDE_STDOUTCMT_SRC_MODIFIER_CPP_H_
#define STDOUTCMT_INCLUDE_STDOUTCMT_SRC_MODIFIER_CPP_H_

#include <cstdint>
#include <optional>
#include <string>
#include <string_view>

#include "stdoutcmt/src_modifier/i_src_modifier.h"
#include "stdoutcmt/util/util.h"

namespace outcmt::modifier {

namespace {

constexpr std::string_view IOSTREAM_INCLUSION{"#include<iostream>"};

[[nodiscard]] bool DidIncludeIOStream(const std::vector<std::string_view>& lines) {
  for (const auto& line: lines) {
    std::string line_nospace{};
    for (const auto ch: outcmt::util::TrimWS(line)) {
      if (ch == ' ') {
        continue;
      }
      line_nospace += ch;
    }
    if (line_nospace == IOSTREAM_INCLUSION) {
      return true;
    }
  }
  return false;
}

[[nodiscard]] std::string FileAndLinePrintStmt(const std::size_t offset) {
  std::string result{"std::cout << '[' << __FILE__ << ':' << "};
  if (offset == 0) {
    result += "__LINE__";
  } else {
    result += "(__LINE__ + " + std::to_string(offset) + ")";
  }
  result += " << \"]:\"; ";
  return result;
}

}  // anonymous namespace

class SrcModifierCpp: ISrcModifier {
 public:
  [[nodiscard]] std::vector<std::string> ModifiedLines(const std::vector<std::string_view> &lines,
                                                       const parser::LineOffsetMap &line_to_offset) const final {
    const bool has_iostream{DidIncludeIOStream(lines)};
    int offset_padding{0};
    std::vector<std::string> result{};
    if (!has_iostream) {
      result.emplace_back(IOSTREAM_INCLUSION);
      offset_padding = -1;
    }
    for (std::size_t i{0}; i < lines.size(); ++i) {
      const std::string_view cur_line{lines.at(i)};
      if (line_to_offset.find(i) != line_to_offset.end()) {
        const int64_t final_line_offset{line_to_offset.at(i) + offset_padding};
        std::string line_with_print{FileAndLinePrintStmt(final_line_offset)};
        line_with_print += cur_line;
        result.emplace_back(line_with_print);
      } else {
        result.emplace_back(cur_line);
      }
    }
    return result;
  }
};

}  // namespace outcmt::modifer

#endif  // STDOUTCMT_INCLUDE_STDOUTCMT_SRC_MODIFIER_CPP_H_
