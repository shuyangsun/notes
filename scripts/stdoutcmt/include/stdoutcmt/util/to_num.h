#ifndef STDOUTCMT_INCLUDE_STDOUTCMT_UTIL_TO_NUM_H_
#define STDOUTCMT_INCLUDE_STDOUTCMT_UTIL_TO_NUM_H_

#include <cstdint>
#include <climits>

#include "stdoutcmt/util/string.h"

namespace outcmt::util {

namespace {

[[nodiscard]] bool IsValidInteger(const std::string_view& str) {
  if (str.length() <= 0) {
    return false;
  }
  auto iter{str.begin()};
  while (iter != str.end()) {
    const char ch{*iter};
    if (std::isdigit(ch) || ch == '-' && iter == str.begin()) {
      ++iter;
      continue;
    }
    return false;
  }
  return true;
}

}  // anonymous namespace

template<typename T>
[[nodiscard]] std::optional<T> FromStr(const std::string_view& str) {
  return {};
}

template<>
[[nodiscard]] std::optional<bool> FromStr(const std::string_view& str) {
  const std::string lower{ToLower(str)};
  if (lower == "true") {
    return {true};
  }
  if (lower == "false") {
    return {false};
  }
  return {};
}

template<>
[[nodiscard]] std::optional<int16_t> FromStr(const std::string_view& str) {
  if (!IsValidInteger(str)) {
    return {};
  }
  char* end{nullptr};
  const std::string tmp_str{str};
  const long res{std::strtol(tmp_str.c_str(), &end, 10)};
  if (*end == '\0' && res >= INT16_MIN && res <= INT16_MAX) {
    return static_cast<int16_t>(res);
  }
  return {};
}

template<>
[[nodiscard]] std::optional<uint16_t> FromStr(const std::string_view& str) {
  if (!IsValidInteger(str) || *str.begin() == '-') {
    return {};
  }
  char* end{nullptr};
  const std::string tmp_str{str};
  const unsigned long res{std::strtoul(tmp_str.c_str(), &end, 10)};
  if (*end == '\0' && res <= UINT16_MAX) {
    return static_cast<uint16_t>(res);
  }
  return {};
}

template<>
[[nodiscard]] std::optional<int32_t> FromStr(const std::string_view& str) {
  if (!IsValidInteger(str)) {
    return {};
  }
  char* end{nullptr};
  const std::string tmp_str{str};
  const long res{std::strtol(tmp_str.c_str(), &end, 10)};
  if (*end == '\0' && res >= INT32_MIN && res <= INT32_MAX) {
    return static_cast<int32_t>(res);
  }
  return {};
}

template<>
[[nodiscard]] std::optional<uint32_t> FromStr(const std::string_view& str) {
  if (!IsValidInteger(str) || *str.begin() == '-') {
    return {};
  }
  char* end{nullptr};
  const std::string tmp_str{str};
  const unsigned long res{std::strtoul(tmp_str.c_str(), &end, 10)};
  if (*end == '\0' && res <= UINT32_MAX) {
    return static_cast<uint32_t>(res);
  }
  return {};
}

template<>
[[nodiscard]] std::optional<int64_t> FromStr(const std::string_view& str) {
  if (!IsValidInteger(str)) {
    return {};
  }
  char* end{nullptr};
  const std::string tmp_str{str};
  const long long res{std::strtoll(tmp_str.c_str(), &end, 10)};
  if (*end == '\0' && res >= INT64_MIN && res <= INT64_MAX) {
    return static_cast<int64_t>(res);
  }
  return {};
}

template<>
[[nodiscard]] std::optional<uint64_t> FromStr(const std::string_view& str) {
  if (!IsValidInteger(str) || *str.begin() == '-') {
    return {};
  }
  char* end{nullptr};
  const std::string tmp_str{str};
  const unsigned long long res{std::strtoull(tmp_str.c_str(), &end, 10)};
  if (*end == '\0'  && res <= UINT64_MAX) {
    return static_cast<uint64_t>(res);
  }
  return {};
}

}  // namespace outcmt::util

#endif  // STDOUTCMT_INCLUDE_STDOUTCMT_UTIL_TO_NUM_H_
