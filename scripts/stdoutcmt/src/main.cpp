#include "stdoutcmt/src_modifier/factory.h"
#include "stdoutcmt/src_parser/factory.h"
#include "stdoutcmt/util/util.h"

#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char** argv) {
  const std::string_view path{"/Users/shuyang/developer/notes/cpp/effective_cpp/items/item_1/item_1.cpp"};
  std::ifstream ifs(path);
  std::string content( (std::istreambuf_iterator<char>(ifs) ),
                       (std::istreambuf_iterator<char>()    ) );
  const outcmt::src::FileType file_type{outcmt::src::GetFileType(path)};

  const outcmt::src::SrcParserFactory parser_factory{};
  const outcmt::src::SrcModifierFactory modifier_factory{};
  const auto parser{parser_factory.BuildSrcParser(file_type)};
  const auto modifier{modifier_factory.BuildSrcModifier(file_type)};
  const std::vector<std::string_view> lines{outcmt::util::ToLines(content)};
  const outcmt::src::LineOffsetMap offset_map{parser->GetCmtLineOffset(lines)};

  for (const auto& [key, value]: offset_map) {
    std::cout << key << ": " << value << std::endl;
  }

  std::cout << "***************" << std::endl;

  const std::vector<std::string> modified{modifier->ModifiedLines(lines, offset_map)};
  for (const std::string& line: modified) {
    std::cout << line << std::endl;
  }
  return 0;
}
