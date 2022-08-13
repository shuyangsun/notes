#ifndef STDOUTCMT_INCLUDE_STDOUTCMT_SRC_COPIER_MODIFIER_WRAPPER_H_
#define STDOUTCMT_INCLUDE_STDOUTCMT_SRC_COPIER_MODIFIER_WRAPPER_H_

#include <memory>
#include <unordered_map>

#include "stdoutcmt/src_copier/interface.h"
#include "stdoutcmt/src_parser/interface.h"
#include "stdoutcmt/src_modifier/interface.h"
#include "stdoutcmt/src_type/src_type.h"
#include "stdoutcmt/util/util.h"

namespace outcmt::src {


class SrcModifyThenCopy: public ISrcCopier {
 public:
  SrcModifyThenCopy(std::unique_ptr<ISrcCopier>&& copier): copier_{std::move(copier)} {}
  ~SrcModifyThenCopy() override = default;

  void AddModifiers(const FileType& file_type, ParserAndModifier&& parser_modifier) {
    this->ftype_map_.emplace(file_type, std::move(parser_modifier));
  }

  [[nodiscard]] virtual std::filesystem::path DuplicateDirToTmp(const std::filesystem::path& path, const bool consider_ignore_files) const final {
    namespace fs = std::filesystem;
    fs::path copied_path{this->copier_->DuplicateDirToTmp(path, consider_ignore_files)};
    for (const auto& dir_entry : fs::recursive_directory_iterator(copied_path)) {
      if (!fs::is_regular_file(dir_entry)) {
        continue;
      }
      FileType file_type{GetFileType(dir_entry.path())};
      if (this->ftype_map_.find(file_type) != this->ftype_map_.end()) {
        const ParserAndModifier& cur{this->ftype_map_.find(file_type)->second};
        const std::string content{util::Read(dir_entry.path())};
        const std::string modified_content{cur.ParseThenModify(content)};
        util::ClearContent(dir_entry.path());
        util::Write(dir_entry.path(), modified_content);
      }
    }
    return copied_path;
  }

 private:
  std::unordered_map<FileType, ParserAndModifier> ftype_map_{};
  std::unique_ptr<ISrcCopier> copier_;
};

}  // namespace outcmt::src

#endif  // STDOUTCMT_INCLUDE_STDOUTCMT_SRC_COPIER_MODIFIER_WRAPPER_H_
