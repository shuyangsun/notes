#include <gtest/gtest.h>
#include <nlohmann/json.hpp>

#include <cstdint>
#include <string>
#include <filesystem>
#include <memory>

#include "stdoutcmt/src_parser/factory.h"
#include "stdoutcmt/util/util.h"

static const std::unique_ptr<outcmt::src::SrcParserCpp> SRC_PARSER_CPP{};

std::filesystem::path GetDataPath(const std::filesystem::path& path) {
  const std::filesystem::path data_path{"tests/data/unit_test"};
  return data_path/path;
}

#define SRC_PARSER_TEST(TEST_NAME); \
TEST(SrcParser, TEST_NAME) {        \
  const std::string test_name{#TEST_NAME}; \
  const std::string input{outcmt::util::Read(GetDataPath("src_parsing/" + test_name + "_input.txt"))}; \
  std::ifstream out_file(GetDataPath("src_parsing/" + test_name + "_output.json")); \
  nlohmann::json data = nlohmann::json::parse(out_file); \
  const outcmt::src::LineOffsetMap res{SRC_PARSER_CPP->GetCmtLineOffset(outcmt::util::ToLines(input))}; \
  EXPECT_EQ(res.size(), data["cmt_offset"].size()); \
  for (auto&& [line, offset]: data["cmt_offset"].items()) { \
    const uint64_t line_num{outcmt::util::FromStr<uint64_t>(line).value()}; \
    const int64_t offset_num{offset.get<int64_t>()}; \
    const std::string err_msg{"Expecting line " + std::to_string(line_num) + " to have offset " + std::to_string(offset_num) + "."}; \
    EXPECT_TRUE(res.find(line_num) != res.end()) << err_msg; \
    EXPECT_EQ(res.at(line_num), offset_num) << err_msg; \
  } \
}

SRC_PARSER_TEST(cpp_001);
SRC_PARSER_TEST(cpp_002);
SRC_PARSER_TEST(cpp_003);
SRC_PARSER_TEST(cpp_004);
SRC_PARSER_TEST(cpp_005);
SRC_PARSER_TEST(cpp_006);
SRC_PARSER_TEST(cpp_007);
SRC_PARSER_TEST(cpp_008);
