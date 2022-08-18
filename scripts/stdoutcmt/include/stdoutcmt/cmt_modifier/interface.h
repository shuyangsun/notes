#ifndef STDOUTCMT_INCLUDE_STDOUTCMT_CMT_MODIFIER_INTERFACE_H_
#define STDOUTCMT_INCLUDE_STDOUTCMT_CMT_MODIFIER_INTERFACE_H_

#include <vector>
#include <string_view>
#include <string>
#include <utility>
#include <map>
#include <sstream>

#include "stdoutcmt/util/util.h"

namespace outcmt::src {

using ParsedComments = typename std::vector<std::pair<std::string_view, std::string_view>>;

class ICmtParser {
 public:
  virtual ~ICmtParser() = default;

  [[nodiscard]] virtual ParsedComments ParseComments(const std::string_view& content) const = 0;
};

} // namespace outcmt::src

#endif  // STDOUTCMT_INCLUDE_STDOUTCMT_CMT_MODIFIER_INTERFACE_H_
