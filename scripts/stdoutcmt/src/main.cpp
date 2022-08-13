#include "stdoutcmt/src_copier/factory.h"
#include "stdoutcmt/util/util.h"

#include <iostream>
#include <string>

int main(int argc, char** argv) {
  const std::string_view path{"/Users/shuyang/developer/notes/"};

  const outcmt::src::SrcCopierFactory copier_factory{};
  const std::unique_ptr<outcmt::src::ISrcCopier> copier{copier_factory.BuildSrcCopierWithModifiers()};
  std::filesystem::path tmp_path{copier->DuplicateDirToTmp(path, true)};
  std::cout << "Files copied to: " << tmp_path << std::endl;
  tmp_path /= "cpp/effective_cpp/items/item_1/item_1.cpp";
  std::cout << "Path to \"item_1.cpp\": " << tmp_path << std::endl;

  return 0;
}
