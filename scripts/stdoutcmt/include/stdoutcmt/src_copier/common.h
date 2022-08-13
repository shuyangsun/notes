#ifndef STDOUTCMT_INCLUDE_STDOUTCMT_SRC_COPIER_COMMON_H_
#define STDOUTCMT_INCLUDE_STDOUTCMT_SRC_COPIER_COMMON_H_

#include <iostream>
#include <exception>
#include <filesystem>
#include <random>
#include <sstream>

#include "stdoutcmt/src_copier/interface.h"
#include "stdoutcmt/util/util.h"

namespace outcmt::src {

namespace {

// Copied from: https://stackoverflow.com/questions/51431425/how-to-recursively-copy-files-and-directories
template<typename F>
void CopyDirRecursive(const std::filesystem::path& src, const std::filesystem::path& target, F predicate) noexcept {
  namespace fs = std::filesystem;
  try {
    if (fs::is_regular_file(src)) {
      fs::copy(src, target, fs::copy_options::overwrite_existing);
      return;
    }
    for (const auto& dirEntry : fs::recursive_directory_iterator(src)) {
      const auto& p = dirEntry.path();
      if (predicate(p)) {
        // Create path in target, if not existing.
        const auto relativeSrc = fs::relative(p, src);
        const auto targetParentPath = target / relativeSrc.parent_path();
        fs::create_directories(targetParentPath);

        // Copy to the targetParentPath which we just created.
        fs::copy(p, targetParentPath, fs::copy_options::overwrite_existing);
      }
    }
  } catch (std::exception& e) {
    std::cerr << e.what();
  }
}

// Copied from: https://stackoverflow.com/questions/24365331/how-can-i-generate-uuid-in-c-without-using-boost-library
static std::random_device              rd;
static std::mt19937                    gen(rd());
static std::uniform_int_distribution<> dis(0, 15);
static std::uniform_int_distribution<> dis2(8, 11);

std::string GenerateUUIDv4() {
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

std::filesystem::path CreateTmpDir() {
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
    const fs::path result{CreateTmpDir() / fname};
    auto predicate = [&](const fs::path& _p){ return true; };
    if (consider_ignore_files) {
      // TODO
    }
    CopyDirRecursive(path, result, predicate);
    return result;
  }

};

}  // namespace outcmt::src

#endif  // STDOUTCMT_INCLUDE_STDOUTCMT_SRC_COPIER_COMMON_H_
