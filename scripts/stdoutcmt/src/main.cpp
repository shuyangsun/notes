#include <iostream>
#include <string>

#include "stdoutcmt/src_copier/factory.h"
#include "stdoutcmt/output_parser/parser.h"
#include "stdoutcmt/cmt_modifier/factory.h"
#include "stdoutcmt/util/util.h"

int main(int argc, char** argv) {
  if (argc == 3 && std::strcmp(argv[1], "--copy") == 0) {
    const std::string_view path{argv[2]};
    const outcmt::src::SrcCopierFactory copier_factory{};
    const std::unique_ptr<outcmt::src::ISrcCopier> copier{
        copier_factory.BuildSrcCopierWithModifiers()};
    std::filesystem::path tmp_path{copier->DuplicateDirToTmp(path, true)};

    std::cout << tmp_path.string();
  } else if (argc == 5 && std::strcmp(argv[1], "--gencmt") == 0) {
    const std::string_view src_path{argv[2]};
    const std::string_view tmp_path{argv[3]};
    const std::string_view output{argv[4]};

    const outcmt::output::OutputParser output_parser{tmp_path};
    outcmt::output::CommentMap parsed_output{output_parser.Parse(output)};
    for (auto&& [file_name, lines]: parsed_output) {
      std::string original_file_name{file_name};
      outcmt::util::Replace(original_file_name, tmp_path, src_path);
      const outcmt::src::FileType file_type{outcmt::src::GetFileType(original_file_name)};
      const outcmt::src::CmtModifierFactory factory{};
      const outcmt::src::CmtModifier cmt_modifier{factory.BuildModifier(file_type)};
      const std::string content{outcmt::util::Read(original_file_name)};
      const std::string new_content{cmt_modifier.ParseAndReplaceComments(content, lines, true)};
      outcmt::util::Write(original_file_name, new_content);
      std::cout << "Modified file " << original_file_name << std::endl;
    }
  }

  return 0;
}
