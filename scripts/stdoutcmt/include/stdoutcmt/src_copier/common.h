#ifndef STDOUTCMT_INCLUDE_STDOUTCMT_SRC_COPIER_COMMON_H_
#define STDOUTCMT_INCLUDE_STDOUTCMT_SRC_COPIER_COMMON_H_

#include <iostream>
#include <exception>
#include <filesystem>
#include <random>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_set>

#include "stdoutcmt/src_copier/interface.h"
#include "stdoutcmt/util/util.h"

static std::random_device              rd;
static std::mt19937                    gen(rd());
static std::uniform_int_distribution<> dis(0, 15);
static std::uniform_int_distribution<> dis2(8, 11);

namespace outcmt::src {

namespace {

using IgnoreSet = typename std::vector<std::unordered_set<std::string>>;

[[nodiscard]] std::unordered_set<std::string> FindIgnores(const std::filesystem::path& path) {
  namespace fs = std::filesystem;
  constexpr std::string_view ignore_file_name{".gitignore"};
  const fs::path ignore_path{path / ignore_file_name};
  if (!fs::exists(ignore_path) || !fs::is_regular_file(ignore_path)) {
    return {};
  }
  std::unordered_set<std::string> result{};
  const std::string content{util::Read(ignore_path)};
  for (const auto& line: util::ToLines(content)) {
    const std::string_view& line_no_comment{util::TrimWS(util::LineWithoutTrailingComment(line, "#"))};
    if (!line_no_comment.empty()) {
      result.emplace(line_no_comment);
    }
  }
  return result; // TODO: use glob pattern matching.
}

void CopyDirRecursive(const std::filesystem::path& src, const std::filesystem::path& target, IgnoreSet& ignores) noexcept {
  namespace fs = std::filesystem;
  try {
    if (fs::is_directory(src)) {
      fs::create_directories(target);
    }
    if (fs::is_regular_file(src)) {
      fs::copy_file(src, target);
      return;
    }

    std::unordered_set<std::string> cur_ignores{FindIgnores(src)};
    bool found_ignores{!cur_ignores.empty()};
    if (found_ignores) {
      ignores.emplace_back(std::move(cur_ignores));
    }
    for (const auto& dir_entry : fs::directory_iterator(src)) {
      const fs::path& cur_src{dir_entry.path()};
      const fs::path cur_target{target / cur_src.filename()};

      bool should_ignore{false};
      if (!ignores.empty()) {
        for (const auto& pattern: ignores) {
          if (pattern.find(cur_src.filename()) != pattern.end()) {
            should_ignore = true;
            break;
          }
        }
      }
      if (should_ignore) {
        continue;
      }
      CopyDirRecursive(cur_src, cur_target, ignores);
    }
    if (!ignores.empty() && found_ignores) {
      ignores.pop_back();
    }
  } catch (std::exception& e) {
    std::cerr << e.what();
  }
}

[[nodiscard]] std::string GenerateUUIDv4() {
  std::stringstream ss;
  int i;
  ss << std::hex;
  for (i = 0; i < 8; i++) {
    ss << dis(gen);
  }
  ss << "-";
  for (i = 0; i < 4; i++) {
    ss << dis(gen);
  }
  ss << "-4";
  for (i = 0; i < 3; i++) {
    ss << dis(gen);
  }
  ss << "-";
  ss << dis2(gen);
  for (i = 0; i < 3; i++) {
    ss << dis(gen);
  }
  ss << "-";
  for (i = 0; i < 12; i++) {
    ss << dis(gen);
  };
  return ss.str();
}

[[nodiscard]] std::filesystem::path CreateTmpDir() {
  const std::filesystem::path tmp_dir{std::filesystem::temp_directory_path()};
  return tmp_dir / GenerateUUIDv4();
}

}  // anonymous namespace


class SrcCopier: public ISrcCopier {
 public:
  SrcCopier() = default;
  ~SrcCopier() override = default;

  [[nodiscard]] virtual std::filesystem::path DuplicateDirToTmp(const std::filesystem::path& path, const bool consider_ignore_files) const final {
    namespace fs = std::filesystem;
    if (!fs::exists(path)) {
      throw std::invalid_argument("Path to copy does not exist.");
    }
    fs::path fname{path.filename()};
    if (fname.empty()) {
      fname = path.parent_path().filename();
    }
    fs::path result{CreateTmpDir() / fname};
    IgnoreSet ignores{};
    CopyDirRecursive(path, result, ignores);
    return result;
  }

};

}  // namespace outcmt::src

#endif  // STDOUTCMT_INCLUDE_STDOUTCMT_SRC_COPIER_COMMON_H_
