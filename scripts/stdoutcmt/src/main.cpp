#include "stdoutcmt/src_modifier/factory.h"
#include "stdoutcmt/src_parser/factory.h"
#include "stdoutcmt/src_copier/factory.h"
#include "stdoutcmt/util/util.h"

#include <iostream>
#include <string>

int main(int argc, char** argv) {
  const std::string_view path{"/Users/shuyang/developer/notes/"};

  const outcmt::src::SrcCopierFactory copier_factory{};
  const std::unique_ptr<outcmt::src::ISrcCopier> copier{copier_factory.BuildSrcCopier()};
  std::filesystem::path tmp_path{copier->DuplicateDirToTmp(path, false)};
  tmp_path /= "cpp/effective_cpp/items/item_1/item_1.cpp";

  const std::string content{outcmt::util::Read(tmp_path)};
  const outcmt::src::FileType file_type{outcmt::src::GetFileType(tmp_path)};

  const outcmt::src::SrcParserFactory parser_factory{};
  const outcmt::src::SrcModifierFactory modifier_factory{};

  const auto parser{parser_factory.BuildSrcParser(file_type)};
  const auto modifier{modifier_factory.BuildSrcModifier(file_type)};
  const std::vector<std::string_view> lines{outcmt::util::ToLines(content)};
  const outcmt::src::LineOffsetMap offset_map{parser->GetCmtLineOffset(lines)};

  const std::vector<std::string> modified{modifier->ModifiedLines(lines, offset_map)};
  std::cout << modified.size() << std::endl;
  // for (const std::string& line: modified) {
  //   std::cout << line << std::endl;
  // }

  return 0;
}
