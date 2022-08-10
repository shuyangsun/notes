#ifndef STDOUTCMT_INCLUDE_STDOUTCMT_SRC_PARSER_CPP_H_
#define STDOUTCMT_INCLUDE_STDOUTCMT_SRC_PARSER_CPP_H_

#include <cstdint>
#include <cstdlib>
#include <exception>
#include <optional>
#include <stack>
#include <string>
#include <string_view>

#include "stdoutcmt/src_parser/interface.h"
#include "stdoutcmt/util/util.h"

namespace outcmt::src {

namespace {
constexpr std::string_view STDOUT_COMMENT_BEG{"#pragma notes cmtbeg"};
constexpr std::string_view STDOUT_COMMENT_END{"#pragma notes cmtend"};
}  // anonymous namespace

class SrcParserCpp: public ISrcParser {
 public:
  SrcParserCpp() = default;
  ~SrcParserCpp() override = default;

  [[nodiscard]] LineOffsetMap GetCmtLineOffset(const std::vector<std::string_view>& lines) const final {
    LineOffsetMap result{};
    std::stack<int64_t> s{};
    for (std::size_t i{0}; i < lines.size(); ++i) {
      const std::string_view cur_line{util::TrimWS(lines[i])};
      if (cur_line.length() >= STDOUT_COMMENT_BEG.length() && cur_line.substr(0, STDOUT_COMMENT_BEG.length()) == STDOUT_COMMENT_BEG) {
        int64_t offset{0};
        if (cur_line.length() > STDOUT_COMMENT_BEG.length()) {
          const std::size_t offset_str_len{cur_line.length() - STDOUT_COMMENT_BEG.length()};
          const char * const offset_str{cur_line.substr(STDOUT_COMMENT_BEG.length(), offset_str_len).data()};
          char * pEnd;
          offset = std::strtol(offset_str, &pEnd, 10);
        }
        s.push(offset);
        continue;
      } else if (cur_line.length() >= STDOUT_COMMENT_END.length() && cur_line.substr(0, STDOUT_COMMENT_END.length()) == STDOUT_COMMENT_END) {
        if (s.empty()) {
          throw std::invalid_argument("Found extra source code comment block end on line " + std::to_string(i) + ".");
        }
        s.pop();
      } else if (!s.empty() && !cur_line.empty()) {
        result.emplace(i, s.top());
      }
    }
    if (!s.empty()) {
      throw std::invalid_argument("Comment block did not end properly with \"" + std::string{STDOUT_COMMENT_END} + "\".");
    }
    return result;
  }
};

}  // namespace outcmt::src

#endif  // STDOUTCMT_INCLUDE_STDOUTCMT_SRC_PARSER_CPP_H_
