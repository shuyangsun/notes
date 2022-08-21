#include <gtest/gtest.h>
#include <nlohmann/json.hpp>

#include <sstream>

#include "stdoutcmt/output_parser/parser.h"

static const outcmt::output::OutputParser DEFAULT_PARSER{};

std::filesystem::path GetDataPath(const std::filesystem::path& path) {
  const std::filesystem::path data_path{"tests/data/unit_test"};
  return data_path/path;
}

TEST(OutputParser, unix_1) {
  const outcmt::output::OutputParser parser{"/private/var/src_code"};
  const outcmt::output::CommentMap result{parser.Parse("")};
  // TODO
}

TEST(OutputParser, windows_1) {
  const outcmt::output::OutputParser parser{R"(C:\Windows\Program Files\SourceCode)"};
  const outcmt::output::CommentMap result{parser.Parse("")};
  // TODO
}

#define OUTPUT_PARSER_TEST(TEST_NAME) \
TEST(OutputParser, TEST_NAME) {\
  const std::string test_name{#TEST_NAME};\
  const std::string input{outcmt::util::Read(GetDataPath("output_parsing/" + test_name + "_input.txt"))};\
  std::ifstream out_file(GetDataPath("output_parsing/" + test_name + "_output.json"));\
  nlohmann::json data = nlohmann::json::parse(out_file);\
  const outcmt::output::CommentMap res{DEFAULT_PARSER.Parse(input)};\
  EXPECT_EQ(res.size(), data["parsed_comments"].size());\
  for (auto&& [file, line_map]: data["parsed_comments"].items()) {\
    std::stringstream err_msg{};\
    err_msg << "Expecting file " << file << " to have " << line_map.size() << " parsed comments:" << std::endl;\
    EXPECT_TRUE(res.find(file) != res.end()) << err_msg.str();\
    const std::map<std::size_t, std::string_view>& cur_map{res.at(file)};\
    err_msg << "Got the following instead:" << std::endl;\
    for (const auto& [line, comment]: cur_map) {\
      err_msg << "  " << line  << ": " << comment << std::endl;\
    }\
    EXPECT_EQ(cur_map.size(), line_map.size()) << err_msg.str();\
    for (auto&& [line, comment]: line_map.items()) {\
      const uint64_t line_num{outcmt::util::FromStr<uint64_t>(line).value()};\
      const std::string comment_str{comment.get<std::string>()};\
      EXPECT_TRUE(cur_map.find(line_num) != cur_map.end()) << err_msg.str();\
      EXPECT_STREQ(std::string{cur_map.at(line_num)}.c_str(), comment_str.c_str()) << err_msg.str();\
    }\
  }\
}

OUTPUT_PARSER_TEST(unix_001);
