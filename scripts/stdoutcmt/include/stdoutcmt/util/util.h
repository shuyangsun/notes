#ifndef STDOUTCMT_INCLUDE_STDOUTCMT_UTIL_UTIL_H_
#define STDOUTCMT_INCLUDE_STDOUTCMT_UTIL_UTIL_H_

#include <string_view>
#include <string>
#include <unordered_set>
#include <vector>
#include <filesystem>
#include <fstream>

namespace outcmt::util {

namespace {

[[nodiscard]] std::string_view TrimPrefixWS(const std::string_view& str) {
  if (str.empty()) {
    return str;
  }
  constexpr std::string_view ws_chars{" \t\n\r"};
  std::string_view result{str};
  const std::string_view::size_type first_non_space{result.find_first_not_of(ws_chars)};
  if (first_non_space == std::string_view::npos) {
    return str.substr(0, 0);
  }
  result.remove_prefix(first_non_space);
  return result;
}

[[nodiscard]] std::string_view TrimPostfixWS(const std::string_view& str) {
  if (str.empty()) {
    return str;
  }
  constexpr std::string_view ws_chars{" \t\n\r"};
  std::string_view result{str};
  const std::string_view::size_type last_non_space{result.find_last_not_of(ws_chars)};
  if (last_non_space == std::string_view::npos) {
    return str.substr(0, 0);
  }
  result.remove_suffix(result.size() - last_non_space - 1);
  return result;
}

[[nodiscard]] std::string_view TrimWS(const std::string_view& str) {
  return TrimPostfixWS(TrimPrefixWS(str));
}

[[nodiscard]] uint8_t NewLineCharLen(const std::string_view &content, std::size_t pos) {
  const char &ch{content.at(pos)};
  if (ch != '\n' && ch != '\r') {
    return 0;
  }
  if (ch == '\r' && pos < content.length() - 1 && content[pos + 1] == '\n') {
    return 2;
  }
  return 1;
}

} // anonymous namespace

[[nodiscard]] bool StartsWith(const std::string_view& str, const std::string_view& prefix) {
  return str.length() >= prefix.length() && str.substr(0, prefix.length()) == prefix;
}

[[nodiscard]] std::string ToLower(const std::string_view& str) {
  std::string result{str};
  std::transform(result.begin(), result.end(), result.begin(),
                 [](unsigned char c){ return std::tolower(c); });
  return result;
}

[[nodiscard]] std::vector<std::string_view> ToLines(const std::string_view& content) {
  std::vector<std::string_view> result{};
  std::size_t i{0};
  std::size_t line_start{0};
  while (i < content.length()) {
    const uint8_t newline_len{NewLineCharLen(content, i)};
    if (newline_len <= 0) {
      ++i;
      continue;
    }
    result.emplace_back(content.substr(line_start, i - line_start));
    i += newline_len;
    line_start = i;
  }
  result.emplace_back(content.substr(line_start, i - line_start));
  return result;
}

[[nodiscard]] std::string_view LineWithoutTrailingComment(const std::string_view& line, const std::string_view& comment_header) {
  const std::size_t cmt_len{comment_header.length()};
  if (cmt_len <= 0) {
    throw std::invalid_argument("Comments cannot start with empty string.");
  }
  if (line.length() >= cmt_len && line.substr(0, cmt_len) == comment_header) {
    return line.substr(0, 0);
  }
  std::size_t res{0};
  bool is_in_str{false};
  for (std::size_t i{0}; i < line.length(); ++i) {
    const char ch{line[i]};
    if (ch == comment_header[0]) {
      if (i <= line.length() - cmt_len && line.substr(i, cmt_len) == comment_header && !is_in_str) {
        return line.substr(0, i);
      }
    } else if (ch == '"') {
      if (!is_in_str) {
        is_in_str = true;
      } else if (i > 0 && line[i - 1] != '\\') {
        is_in_str = false;
      }
    }
  }
  return line;
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

}  // namespace outcmt::util

#endif  // STDOUTCMT_INCLUDE_STDOUTCMT_UTIL_UTIL_H_
