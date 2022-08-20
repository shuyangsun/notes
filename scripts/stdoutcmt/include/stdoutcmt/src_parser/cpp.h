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

constexpr std::string_view STDOUT_COMMENT_BEG{"#pragma cmt beg"};
constexpr std::string_view STDOUT_COMMENT_END{"#pragma cmt end"};
constexpr std::string_view STDOUT_COMMENT_IGNORE_ONCE{"#pragma cmt ignore_once"};

bool IsLineEndingStmt(const std::string_view& line) {
  const std::string_view no_comment{util::TrimWS(std::get<0>(util::LineToCodeCmt(line, "//")))};
  return no_comment.empty() || no_comment[no_comment.length() - 1] == ';';
}

}  // anonymous namespace

class SrcParserCpp: public ISrcParser {
 public:
  SrcParserCpp() = default;
  ~SrcParserCpp() override = default;

  [[nodiscard]] LineOffsetMap GetCmtLineOffset(const std::vector<std::string_view>& lines) const final {
    LineOffsetMap result{};
    std::stack<int64_t> s{};
    bool should_ignore{false};
    std::optional<std::size_t> last_line_non_stmt{};
    for (std::size_t i{0}; i < lines.size(); ++i) {
      const std::string_view cur_line{util::TrimWS(lines[i])};
      if (util::StartsWith(cur_line, STDOUT_COMMENT_BEG)) {
        int64_t offset{0};
        if (cur_line.length() > STDOUT_COMMENT_BEG.length()) {
          const std::size_t offset_str_len{cur_line.length() - STDOUT_COMMENT_BEG.length()};
          const std::string tmp_str{std::string{cur_line.substr(STDOUT_COMMENT_BEG.length(), offset_str_len)}};
          const char * const offset_str{tmp_str.c_str()};
          char * pEnd;
          offset = std::strtol(offset_str, &pEnd, 10);
        }
        s.push(offset);
        continue;
      } else if (util::StartsWith(cur_line, STDOUT_COMMENT_END)) {
        if (s.empty()) {
          throw std::invalid_argument("Found extra source code comment block end on line " + std::to_string(i) + ".");
        }
        s.pop();
      } else if (util::StartsWith(cur_line, STDOUT_COMMENT_IGNORE_ONCE)) {
        should_ignore = true;
      } else if (!s.empty() && !cur_line.empty()) {
        const bool is_line_stmt{IsLineEndingStmt(cur_line)};
        std::size_t stmt_beg_line_idx{i};
        int64_t offset{s.top()};
        if (is_line_stmt) {
          if (last_line_non_stmt.has_value()) {
            stmt_beg_line_idx = last_line_non_stmt.value();
            if (offset >= 0) {
              offset += static_cast<int64_t>(i - stmt_beg_line_idx);
            }
          }
          last_line_non_stmt.reset();
        } else {
          if (!last_line_non_stmt.has_value()) {
            last_line_non_stmt = i;
          }
          continue;
        }
        if (!should_ignore) {
          result.emplace(stmt_beg_line_idx + 1, offset);
        }
        should_ignore = false;
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
