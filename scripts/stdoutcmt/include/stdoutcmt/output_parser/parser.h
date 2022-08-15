#ifndef STDOUTCMT_INCLUDE_STDOUTCMT_OUTPUT_PARSER_PARSER_H_
#define STDOUTCMT_INCLUDE_STDOUTCMT_OUTPUT_PARSER_PARSER_H_

#include <string_view>
#include <filesystem>
#include <unordered_map>
#include <map>
#include <regex>
#include <sstream>

#include "stdoutcmt/util/util.h"

namespace outcmt::output {

using CommentMap = typename std::unordered_map<std::string, std::map<std::size_t, std::string_view>>;

class OutputParser{
 public:
  OutputParser(): cmt_regex_{"\\[.+:[1-9][0-9]*\\]:"} {};
  OutputParser(const std::filesystem::path& tmp_dir_path) {
    std::string escaped{tmp_dir_path};
    util::Replace(escaped, "\\", "\\\\");
    util::Replace(escaped, "/", "\\/");
    std::stringstream ss;
    ss << "\\[";
    ss << escaped;
    ss << ".*:[1-9][0-9]*\\]:";
    this->cmt_regex_ = std::regex{ss.str()};
  }
  ~OutputParser() = default;

  [[nodiscard]] CommentMap Parse(const std::string_view& content) const {
    CommentMap result{};
    return result;
  }

 private:
  std::regex cmt_regex_;
};

}  // namespace outcmt::output

#endif  // STDOUTCMT_INCLUDE_STDOUTCMT_OUTPUT_PARSER_PARSER_H_
