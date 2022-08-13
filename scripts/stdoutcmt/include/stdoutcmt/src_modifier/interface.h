#ifndef STDOUTCMT_INCLUDE_STDOUTCMT_SRC_MODIFIER_INTERFACE_H_
#define STDOUTCMT_INCLUDE_STDOUTCMT_SRC_MODIFIER_INTERFACE_H_

#include <string_view>
#include <vector>
#include <unordered_map>
#include <memory>

#include "stdoutcmt/src_parser/interface.h"
#include "stdoutcmt/util/util.h"

namespace outcmt::src {

class ISrcModifier {
 public:
  virtual ~ISrcModifier() = default;

  [[nodiscard]] virtual std::vector<std::string> ModifiedLines(const std::vector<std::string_view>& lines, const LineOffsetMap& line_to_offset) const = 0;
};

class ParserAndModifier {
 public:
  ParserAndModifier(std::unique_ptr<ISrcParser>&& parser, std::unique_ptr<ISrcModifier>&& modifier):
    parser_{std::move(parser)},
    modifier_{std::move(modifier)} {}
  ParserAndModifier(ParserAndModifier&& other):
    parser_{std::move(other.parser_)},
    modifier_{std::move(other.modifier_)} {}
  ~ParserAndModifier() = default;

  [[nodiscard]] std::string ParseThenModify(const std::string_view& content) const {
    const std::vector<std::string_view> lines{util::ToLines(content)};
    const LineOffsetMap offset_map{this->parser_->GetCmtLineOffset(lines)};
    const std::vector<std::string> modified_lines{this->modifier_->ModifiedLines(lines, offset_map)};
    return util::Join(modified_lines, "\n");
  }

 private:
  std::unique_ptr<ISrcParser> parser_;
  std::unique_ptr<ISrcModifier> modifier_;
};

}  // namespace outcmt::src

#endif  // STDOUTCMT_INCLUDE_STDOUTCMT_SRC_MODIFIER_INTERFACE_H_
