#include "stdoutcmt/src_modifier/factory.h"
#include "stdoutcmt/src_parser/factory.h"
#include "stdoutcmt/src_copier/factory.h"
#include "stdoutcmt/util/util.h"

#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char** argv) {
  const std::string_view path{"/Users/shuyang/developer/notes/cpp/effective_cpp"};

  const outcmt::src::SrcCopierFactory copier_factory{};
  const std::unique_ptr<outcmt::src::ISrcCopier> copier{copier_factory.BuildSrcCopier()};
  std::filesystem::path tmp_path{copier->DuplicateDirToTmp(path, false)};
  tmp_path /= "items/item_1/item_1.cpp";
  std::cout << "Tmp path: " << tmp_path <<  std::endl;

  std::ifstream ifs(tmp_path);
  std::string content( (std::istreambuf_iterator<char>(ifs) ),
                       (std::istreambuf_iterator<char>()    ) );
  const outcmt::src::FileType file_type{outcmt::src::GetFileType(tmp_path)};

  const outcmt::src::SrcParserFactory parser_factory{};
  const outcmt::src::SrcModifierFactory modifier_factory{};

  const auto parser{parser_factory.BuildSrcParser(file_type)};
  const auto modifier{modifier_factory.BuildSrcModifier(file_type)};
  const std::vector<std::string_view> lines{outcmt::util::ToLines(content)};
  const outcmt::src::LineOffsetMap offset_map{parser->GetCmtLineOffset(lines)};

  const std::vector<std::string> modified{modifier->ModifiedLines(lines, offset_map)};
  for (const std::string& line: modified) {
    std::cout << line << std::endl;
  }

  return 0;
}
