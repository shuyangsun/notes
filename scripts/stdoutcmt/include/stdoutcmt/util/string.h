#ifndef STDOUTCMT_INCLUDE_STDOUTCMT_UTIL_STRING_H_
#define STDOUTCMT_INCLUDE_STDOUTCMT_UTIL_STRING_H_

#include <algorithm>
#include <cctype>
#include <string>
#include <string_view>

namespace outcmt::util {

namespace {

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


[[nodiscard]] std::string ToLower(const std::string_view& str) {
  std::string res{str};
  std::transform(res.begin(), res.end(), res.begin(),
                 [](unsigned char c){ return std::tolower(c); });
  return res;
}

[[nodiscard]] std::string ToUpper(const std::string_view& str) {
  std::string res{str};
  std::transform(res.begin(), res.end(), res.begin(),
                 [](unsigned char c){ return std::toupper(c); });
  return res;
}

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

[[nodiscard]] bool StartsWith(const std::string_view& str, const std::string_view& prefix) {
  return str.length() >= prefix.length() && str.substr(0, prefix.length()) == prefix;
}

[[nodiscard]] bool EndsWith(const std::string_view& str, const std::string_view& postfix) {
  return str.length() >= postfix.length() && str.substr(str.length() - postfix.length(), postfix.length()) == postfix;
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

}  // namespace outcmt::util

#endif  // STDOUTCMT_INCLUDE_STDOUTCMT_UTIL_STRING_H_
