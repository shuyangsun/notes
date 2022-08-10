#ifndef STDOUTCMT_INCLUDE_STDOUTCMT_SRC_TYPE_SRC_TYPE_H_
#define STDOUTCMT_INCLUDE_STDOUTCMT_SRC_TYPE_SRC_TYPE_H_

#include <algorithm>
#include <cctype>
#include <filesystem>
#include <string_view>

#include "stdoutcmt/util/util.h"

namespace outcmt::src {

enum class FileType {
  Unknown,
  Cpp,
};

[[nodiscard]] FileType GetFileType(const std::string_view& file_name) {
  std::filesystem::path path{file_name};
  std::string extension{util::ToLower(path.extension().c_str())};
  if (extension == ".h"
      || extension == ".hpp"
      || extension == ".hxx"
      || extension == ".c"
      || extension == ".cpp"
      || extension == ".cxx") {
    return FileType::Cpp;
  }
  return FileType::Unknown;
};

}  // namespace outcmt::src

#endif  // STDOUTCMT_INCLUDE_STDOUTCMT_SRC_TYPE_SRC_TYPE_H_
