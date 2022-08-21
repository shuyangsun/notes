#ifndef STDOUTCMT_INCLUDE_STDOUTCMT_UTIL_UTIL_H_
#define STDOUTCMT_INCLUDE_STDOUTCMT_UTIL_UTIL_H_

#include <string_view>
#include <string>
#include <cstdlib>
#include <exception>
#include <unordered_set>
#include <vector>
#include <filesystem>
#include <fstream>
#include <utility>

#include "stdoutcmt/util/to_num.h"
#include "stdoutcmt/util/string.h"

namespace outcmt::util {


[[nodiscard]] std::pair<std::string_view, std::string_view> LineToCodeCmt(const std::string_view& line, const std::string_view& comment_header, const std::unordered_set<char>& str_quotes = {'"'}) {
  const std::size_t cmt_len{comment_header.length()};
  if (cmt_len <= 0) {
    throw std::invalid_argument("Comments cannot start with empty string.");
  }
  std::string_view empty_str{line.substr(0, 0)};
  if (line.length() >= cmt_len && line.substr(0, cmt_len) == comment_header) {
    return std::make_pair(empty_str, line);
  }
  bool is_in_str{false};
  for (std::size_t i{0}; i < line.length(); ++i) {
    const char ch{line[i]};
    if (ch == comment_header[0]) {
      if (i <= line.length() - cmt_len && line.substr(i, cmt_len) == comment_header && !is_in_str) {
        return std::make_pair(line.substr(0, i), line.substr(i, line.length() - i));
      }
    } else if (str_quotes.find(ch) != str_quotes.end()) {  // TODO: need to track first char to handle " a ' # fake cmt ' c " in Python
      if (!is_in_str) {
        is_in_str = true;
      } else if (i > 0 && line[i - 1] != '\\') {
        is_in_str = false;
      }
    }
  }
  return std::make_pair(line.substr(0, line.length()), empty_str);
}

void Replace(std::string& str, const std::string_view& from, const std::string_view& to) {
  std::size_t start_pos{0};
  std::size_t search_pos{str.find(from, start_pos)};
  while (search_pos != std::string::npos) {
    str.replace(search_pos, from.length(), to);
    start_pos = search_pos + to.length();
    search_pos = str.find(from, start_pos);
  }
}

std::vector<std::string_view> Split(const std::string_view& str, const std::string_view& delim) {
  std::vector<std::string_view> result{};
  std::size_t start_pos{0};
  std::size_t search_pos{str.find(delim, start_pos)};
  while (search_pos != std::string::npos) {
    result.emplace_back(str.substr(start_pos, search_pos));
    start_pos = search_pos + delim.length();
    search_pos = str.find(delim, start_pos);
  }
  if (start_pos < str.length()) {
    result.emplace_back(str.substr(start_pos, str.length() - start_pos));
  }
  return result;
}

[[nodiscard]] std::string Read(const std::filesystem::path& path) {
  if (!std::filesystem::exists(path)) {
    throw std::invalid_argument("File \"" + path.string() + "\" does not exist.");
  }
  if (std::filesystem::is_directory(path)) {
    throw std::invalid_argument("Cannot read directory \"" + path.string() + "\".");
  }
  std::ifstream ifs{path};
  std::string content{(std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>())};
  ifs.close();
  return content;
}

void ClearContent(const std::filesystem::path& path) {
  std::ofstream ofs;
  ofs.open(path, std::ofstream::out | std::ofstream::trunc);
  ofs.close();
}

void Write(const std::filesystem::path& path, const std::string_view& content) {
  std::ofstream ofs;
  ofs.open (path);
  ofs << content;
  ofs.close();
}

template<typename T>
[[nodiscard]] std::string Join(const std::vector<T>& strs, const std::string_view& delim) {
  std::string result{};
  for (std::size_t i{0}; i < strs.size(); ++i) {
    result += strs[i];
    if (i < strs.size() - 1) {
      result += delim;
    }
  }
  return result;
}

[[nodiscard]] std::optional<std::string> GetEnvSafe(const std::string_view& env_var) {
  char const * const result{std::getenv(env_var.data())};
  if (result == nullptr) {
    return {};
  }
  return {std::string{*result}};
}

}  // namespace outcmt::util

#endif  // STDOUTCMT_INCLUDE_STDOUTCMT_UTIL_UTIL_H_
