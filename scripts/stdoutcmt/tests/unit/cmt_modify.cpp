#include <gtest/gtest.h>
#include <nlohmann/json.hpp>

#include <memory>
#include <string_view>

#include "stdoutcmt/cmt_modifier/factory.h"
#include "stdoutcmt/src_type/src_type.h"
#include "stdoutcmt/util/util.h"

static const outcmt::src::CmtModifierFactory FACTORY{};
static const outcmt::src::CmtModifier MODIFIER_CPP{FACTORY.BuildModifier(outcmt::src::FileType::Cpp)};

std::filesystem::path GetDataPath(const std::filesystem::path& path) {
  const std::filesystem::path data_path{"tests/data/unit_test"};
  return data_path/path;
}

std::map<std::size_t, std::string_view> JsonToCommentsMap(const nlohmann::json& content) {
  std::map<std::size_t, std::string_view> res{};
  for (auto&& [line, cmt]: content.items()) {
    const uint64_t line_num{outcmt::util::FromStr<uint64_t>(line).value()};
    const std::string_view comment{cmt.get<std::string_view>()};
    res.emplace(line_num, comment);
  }
  return res;
}

#define CMT_MODIFIER_TEST(TEST_NAME, ALIGN_CMT) \
TEST(CmtModifier, TEST_NAME) {\
  const std::string test_name{#TEST_NAME};\
  const std::string input_src{outcmt::util::Read(GetDataPath("cmt_modifier/" + test_name + "_input_src.txt"))};\
  std::ifstream input_cmt_stream{GetDataPath("cmt_modifier/" + test_name + "_input_cmt.json")};\
  nlohmann::json input_cmt{nlohmann::json::parse(input_cmt_stream)};\
  const std::string output{outcmt::util::Read(GetDataPath("cmt_modifier/" + test_name + "_output.txt"))};\
  std::map<std::size_t, std::string_view> comments_map{JsonToCommentsMap(input_cmt["comments"])};\
  const std::string res{MODIFIER_CPP.ParseAndReplaceComments(input_src, comments_map, ALIGN_CMT)};\
  EXPECT_STREQ(output.c_str(), res.c_str());\
}

CMT_MODIFIER_TEST(cpp_001, false);
CMT_MODIFIER_TEST(cpp_002, false);
CMT_MODIFIER_TEST(cpp_003, false);
CMT_MODIFIER_TEST(cpp_004, false);
CMT_MODIFIER_TEST(cpp_005, false);
CMT_MODIFIER_TEST(cpp_006, true);
