#include "stdoutcmt/src_modifier/cpp.h"
#include "stdoutcmt/src_parser/cpp.h"
#include "stdoutcmt/util/util.h"

#include <iostream>

int main(int argc, char** argv) {
  std::string_view str{"#include <iostream>\n\nint main(int argc, char** argv) {\n#pragma notes cmtbeg\nint x{0};\n#pragma notes cmtend\nreturn 0;\n}"};

  const outcmt::parser::SrcParserCpp parser{};
  const outcmt::modifier::SrcModifierCpp modifier{};
  const std::vector<std::string_view> lines{outcmt::util::ToLines(str)};
  const outcmt::parser::LineOffsetMap offset_map{parser.GetCmtLineOffset(lines)};

  for (const auto& [key, value]: offset_map) {
    std::cout << key << ": " << value << std::endl;
  }

  std::cout << "***************" << std::endl;

  const std::vector<std::string> modified{modifier.ModifiedLines(lines, offset_map)};
  for (const std::string& line: modified) {
    std::cout << line << std::endl;
  }
  return 0;
}
