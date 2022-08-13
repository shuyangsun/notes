#ifndef STDOUTCMT_INCLUDE_STDOUTCMT_SRC_COPIER_FACTORY_H_
#define STDOUTCMT_INCLUDE_STDOUTCMT_SRC_COPIER_FACTORY_H_

#include <array>
#include <unordered_map>

#include "stdoutcmt/src_copier/common.h"
#include "stdoutcmt/src_copier/modifier_wrapper.h"
#include "stdoutcmt/src_modifier/factory.h"
#include "stdoutcmt/src_type/src_type.h"

namespace outcmt::src {

class SrcCopierFactory {
 public:
  SrcCopierFactory() = default;
  ~SrcCopierFactory() = default;

  [[nodiscard]] std::unique_ptr<ISrcCopier> BuildSrcCopier() const {
    return std::make_unique<SrcCopier>();
  }

  [[nodiscard]] std::unique_ptr<ISrcCopier> BuildSrcCopierWithModifiers() const {
    auto res = std::make_unique<SrcModifyThenCopy>(this->BuildSrcCopier());

    std::unordered_map<FileType, std::unique_ptr<ISrcModifier>> modifier_map{};
    SrcModifierFactory modifier_factory{};
    const std::array<FileType, 1> file_types{FileType::Cpp};
    for (const auto& ele: file_types) {
      modifier_map.emplace(ele, modifier_factory.BuildSrcModifier(ele));
    }
    res->AddModifiers(std::move(modifier_map));

    return res;
  }

};

}

#endif  // STDOUTCMT_INCLUDE_STDOUTCMT_SRC_COPIER_FACTORY_H_
