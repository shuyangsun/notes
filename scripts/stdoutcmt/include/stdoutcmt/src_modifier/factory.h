#ifndef STDOUTCMT_INCLUDE_STDOUTCMT_SRC_MODIFIER_FACTORY_H_
#define STDOUTCMT_INCLUDE_STDOUTCMT_SRC_MODIFIER_FACTORY_H_

#include <exception>
#include <memory>

#include "stdoutcmt/src_modifier/interface.h"
#include "stdoutcmt/src_modifier/cpp.h"
#include "stdoutcmt/src_type/src_type.h"

namespace outcmt::src {

class SrcModifierFactory {
 public:
  SrcModifierFactory() = default;
  ~SrcModifierFactory() = default;

  [[nodiscard]] std::unique_ptr<ISrcModifier> BuildSrcModifier(const FileType& file_type) const {
    switch (file_type) {
      case FileType::Cpp:
        return std::make_unique<SrcModifierCpp>();
      default:
        throw std::invalid_argument("Cannot construct SrcModifier with unknown file type.");
    }
  }
};

}

#endif  // STDOUTCMT_INCLUDE_STDOUTCMT_SRC_MODIFIER_FACTORY_H_
