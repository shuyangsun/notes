#ifndef STDOUTCMT_INCLUDE_STDOUTCMT_SRC_COPIER_MODIFIER_WRAPPER_H_
#define STDOUTCMT_INCLUDE_STDOUTCMT_SRC_COPIER_MODIFIER_WRAPPER_H_

#include <memory>
#include <unordered_map>

#include "stdoutcmt/src_copier/interface.h"
#include "stdoutcmt/src_modifier/interface.h"
#include "stdoutcmt/src_type/src_type.h"
#include "stdoutcmt/util/util.h"

namespace outcmt::src {


class SrcModifyThenCopy: public ISrcCopier {
 public:
  SrcModifyThenCopy(std::unique_ptr<ISrcCopier>&& copier): copier_{std::move(copier)} {}
  ~SrcModifyThenCopy() override = default;

  void AddModifiers(std::unordered_map<FileType, std::unique_ptr<ISrcModifier>>&& modifier_map) {
    this->modifier_map_ = std::move(modifier_map);
  }

  [[nodiscard]] virtual std::filesystem::path DuplicateDirToTmp(const std::filesystem::path& path, const bool consider_ignore_files) const final {
    const std::filesystem::path result{this->copier_->DuplicateDirToTmp(path, consider_ignore_files)};
    // TODO: recursively walk through all files and use modifiers to change content if file_type is found in map.
    return result;
  }

 private:
  std::unordered_map<FileType, std::unique_ptr<ISrcModifier>> modifier_map_{};
  std::unique_ptr<ISrcCopier> copier_;
};

}  // namespace outcmt::src

#endif  // STDOUTCMT_INCLUDE_STDOUTCMT_SRC_COPIER_MODIFIER_WRAPPER_H_
