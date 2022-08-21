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

    const outcmt::output::OutputParser output_parser{};  // TODO: initialize with tmp_path, not working now
    const outcmt::output::CommentMap parsed_output{output_parser.Parse(output)};

    for (const auto& [file_name, lines]: parsed_output) {
      std::string original_file_name{file_name};
      // Cannot use "Replace" here, on macOS sometimes "/private" is ignored.
      const std::size_t pos{original_file_name.find(tmp_path)};
      if (pos != std::string::npos) {
        const std::size_t start_pos{pos + tmp_path.length()};
        original_file_name = std::string{src_path} + original_file_name.substr(start_pos, original_file_name.length() - start_pos);
      }
      const outcmt::src::FileType file_type{outcmt::src::GetFileType(original_file_name)};
      const outcmt::src::CmtModifierFactory factory{};
      const outcmt::src::CmtModifier cmt_modifier{factory.BuildModifier(file_type)};
      const std::string content{outcmt::util::Read(original_file_name)};
      const std::string new_content{cmt_modifier.ParseAndReplaceComments(content, lines, true)};
      outcmt::util::Write(original_file_name, new_content);
      std::cout << "Modified file \"" << original_file_name << '"' << std::endl;
    }
  }

  return 0;
}
