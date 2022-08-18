#ifndef STDOUTCMT_INCLUDE_STDOUTCMT_CMT_MODIFIER_CPP_H_
#define STDOUTCMT_INCLUDE_STDOUTCMT_CMT_MODIFIER_CPP_H_

#include <utility>

#include "stdoutcmt/cmt_modifier/interface.h"
#include "stdoutcmt/util/util.h"

namespace outcmt::src {

class CmtParserCpp: public ICmtParser {
 public:
  CmtParserCpp() = default;
  ~CmtParserCpp() final = default;

  [[nodiscard]] ParsedComments ParseComments(const std::string_view& content) const final {
    std::vector<std::string_view> lines{util::ToLines(content)};
    ParsedComments result{lines.size()};
    for (auto&& line: std::move(lines)) {
      result.emplace_back(util::LineToCodeCmt(line, "//"));
    }
    return result;
  }
};

}  // namespace outcmt::src

#endif  // STDOUTCMT_INCLUDE_STDOUTCMT_CMT_MODIFIER_CPP_H_
