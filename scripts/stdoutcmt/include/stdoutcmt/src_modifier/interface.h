#ifndef STDOUTCMT_INCLUDE_STDOUTCMT_SRC_MODIFIER_INTERFACE_H_
#define STDOUTCMT_INCLUDE_STDOUTCMT_SRC_MODIFIER_INTERFACE_H_

#include <string_view>
#include <vector>
#include <unordered_map>

#include "stdoutcmt/src_parser/interface.h"

namespace outcmt::src {

class ISrcModifier {
 public:
  virtual ~ISrcModifier() = default;

  [[nodiscard]] virtual std::vector<std::string> ModifiedLines(const std::vector<std::string_view>& lines, const LineOffsetMap& line_to_offset) const = 0;
};

}  // namespace outcmt::src

#endif  // STDOUTCMT_INCLUDE_STDOUTCMT_SRC_MODIFIER_INTERFACE_H_
