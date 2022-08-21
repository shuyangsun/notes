#ifndef STDOUTCMT_INCLUDE_STDOUTCMT_OUTPUT_PARSER_PARSER_H_
#define STDOUTCMT_INCLUDE_STDOUTCMT_OUTPUT_PARSER_PARSER_H_

#include <cmath>
#include <filesystem>
#include <map>
#include <optional>
#include <regex>
#include <sstream>
#include <string_view>
#include <unordered_map>

#include "stdoutcmt/util/util.h"

namespace outcmt::output {

using CommentMap =
    typename std::unordered_map<std::string,
                                std::map<std::size_t, std::string_view>>;

class OutputParser {
 public:
  OutputParser() : cmt_regex_{"\\[.+:[1-9][0-9]*\\]:"} {};
  explicit OutputParser(const std::filesystem::path& tmp_dir_path) {
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

    using RegexIter = typename std::regex_iterator<std::string_view::iterator>;

    RegexIter beg{content.begin(), content.end(), this->cmt_regex_};
    RegexIter end{};
    std::vector<std::pair<std::size_t, std::size_t>> match_pos{};
    for (std::regex_iterator iter{beg}; iter != end; ++iter) {
      const auto& match{*iter};
      const auto pos{match.position(0)};
      const auto len{match.length(0)};
      match_pos.emplace_back(std::make_pair(pos, len));
      const std::string cur_match{match.str()};
    }
    for (std::size_t i{0}; i < match_pos.size(); ++i) {
      const std::size_t cur_pos{std::get<0>(match_pos[i])};
      const std::size_t cur_len{std::get<1>(match_pos[i])};
      const std::size_t cmt_start_pos{cur_pos + cur_len};
      std::optional<std::size_t> next_match_pos{};
      if (i < match_pos.size() - 1) {
        next_match_pos = std::get<0>(match_pos[i + 1]);
        if (cmt_start_pos == next_match_pos) {
          continue;
        }
      }
      std::size_t cmt_end_pos{content.find('\r', cmt_start_pos)};
      if (cmt_end_pos == std::string::npos) {
        cmt_end_pos = content.find('\n', cur_pos + cur_len);
      }
      if (cmt_end_pos == std::string::npos) {
        cmt_end_pos = content.length();
      }
      if (next_match_pos.has_value()) {
        cmt_end_pos = std::min(cmt_end_pos, next_match_pos.value());
      }
      const std::string_view cur_cmt{
          content.substr(cmt_start_pos, cmt_end_pos - cmt_start_pos)};
      if (util::TrimWS(cur_cmt).empty()) {
        continue;
      }
      const std::vector<std::string_view> fname_linenum{
          util::Split(content.substr(cur_pos + 1, cur_len - 3), ":")};
      std::string file_name{fname_linenum.at(0)};
      std::string line_number{fname_linenum.at(1)};
      const char* const line_number_str{line_number.c_str()};
      char* pEnd{nullptr};
      const std::size_t line_num{
          static_cast<std::size_t>(std::strtol(line_number_str, &pEnd, 10))};

      if (result.find(file_name) == result.end()) {
        result.emplace(file_name, std::map<std::size_t, std::string_view>{
                                      {line_num, cur_cmt}});
      } else {
        result[file_name].emplace(line_num, cur_cmt);
      }
    }
    return result;
  }

 private:
  std::regex cmt_regex_;
};

}  // namespace outcmt::output

#endif  // STDOUTCMT_INCLUDE_STDOUTCMT_OUTPUT_PARSER_PARSER_H_
