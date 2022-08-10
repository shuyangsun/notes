#ifndef STDOUTCMT_INCLUDE_STDOUTCMT_SRC_PARSER_I_SRC_PARSER_H_
#define STDOUTCMT_INCLUDE_STDOUTCMT_SRC_PARSER_I_SRC_PARSER_H_

#include <cstdint>
#include <string_view>
#include <unordered_map>

namespace outcmt::parser {

using LineOffsetMap = typename std::unordered_map<std::size_t, int64_t>;

class ISrcParser {
 public:
  virtual ~ISrcParser() = default;

  [[nodiscard]] virtual LineOffsetMap GetCmtLineOffset(const std::vector<std::string_view>& lines) const = 0;
};

}  // namespace outcmt::parser

#endif  // STDOUTCMT_INCLUDE_STDOUTCMT_SRC_PARSER_I_SRC_PARSER_H_
