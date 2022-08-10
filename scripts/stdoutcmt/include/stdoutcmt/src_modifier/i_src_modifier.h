#ifndef STDOUTCMT_INCLUDE_STDOUTCMT_SRC_MODIFIER_I_SRC_MODIFIER_H_
#define STDOUTCMT_INCLUDE_STDOUTCMT_SRC_MODIFIER_I_SRC_MODIFIER_H_

#include <string_view>
#include <vector>
#include <unordered_map>

#include "stdoutcmt/src_parser/i_src_parser.h"

namespace outcmt::modifier {

class ISrcModifier {
 public:
  virtual ~ISrcModifier() = default;

  [[nodiscard]] virtual std::vector<std::string> ModifiedLines(const std::vector<std::string_view>& lines, const parser::LineOffsetMap& line_to_offset) const = 0;
};

}  // namespace outcmt::modifier

#endif  // STDOUTCMT_INCLUDE_STDOUTCMT_SRC_MODIFIER_I_SRC_MODIFIER_H_
