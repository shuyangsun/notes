#include <iostream>
#include <string>

#include "stdoutcmt/src_copier/factory.h"
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

    std::cout << src_path << std::endl;
    std::cout << tmp_path << std::endl;
    std::cout << output << std::endl;
  }

  return 0;
}
