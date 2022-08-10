#ifndef STDOUTCMT_INCLUDE_STDOUTCMT_SRC_PARSER_FACTORY_H_
#define STDOUTCMT_INCLUDE_STDOUTCMT_SRC_PARSER_FACTORY_H_

#include <exception>
#include <memory>

#include "stdoutcmt/src_parser/interface.h"
#include "stdoutcmt/src_parser/cpp.h"
#include "stdoutcmt/src_type/src_type.h"

namespace outcmt::src {

class SrcParserFactory {
 public:
  SrcParserFactory() = default;
  ~SrcParserFactory() = default;

  [[nodiscard]] std::unique_ptr<ISrcParser> BuildSrcParser(const FileType& file_type) const {
    switch (file_type) {
      case FileType::Cpp:
        return std::make_unique<SrcParserCpp>();
      default:
        throw std::invalid_argument("Cannot construct SrcParser with unknown file type.");
    }
  }
};

}

#endif  // STDOUTCMT_INCLUDE_STDOUTCMT_SRC_PARSER_FACTORY_H_
