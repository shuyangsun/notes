#ifndef STDOUTCMT_INCLUDE_STDOUTCMT_SRC_COPIER_INTERFACE_H_
#define STDOUTCMT_INCLUDE_STDOUTCMT_SRC_COPIER_INTERFACE_H_

#include <string_view>
#include <filesystem>

namespace outcmt::src {

class ISrcCopier {
 public:
  virtual ~ISrcCopier() = default;

  [[nodiscard]] virtual std::filesystem::path DuplicateDirToTmp(const std::filesystem::path& path, const bool consider_ignore_files) const = 0;
};

}  // namespace outcmt::src

#endif  // STDOUTCMT_INCLUDE_STDOUTCMT_SRC_COPIER_INTERFACE_H_
