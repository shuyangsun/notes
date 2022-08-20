#include <gtest/gtest.h>

#include <memory>
#include <cstdint>
#include <string_view>
#include <filesystem>
#include <fstream>

#include <nlohmann/json.hpp>

#include "stdoutcmt/output_parser/parser.h"
#include "stdoutcmt/src_parser/factory.h"
#include "stdoutcmt/cmt_modifier/factory.h"
#include "stdoutcmt/util/util.h"

using namespace outcmt;
using json = nlohmann::json;

static const std::unique_ptr<src::SrcParserCpp> SRC_PARSER_CPP{};
static const output::OutputParser OUTPUT_PARSER_CPP{};
static const src::CmtModifier CMT_MODIFIER_CPP{src::CmtModifierFactory{}.BuildModifier(src::FileType::Cpp)};

std::filesystem::path GetDataPath(const std::filesystem::path& path) {
  const std::filesystem::path data_path{"tests/data/unit_test"};
  return data_path/path;
}

TEST(Utility, TrimWS_1) {
  const std::string str{};
  const std::string res{util::TrimWS(str)};
  EXPECT_TRUE(res.empty());
  EXPECT_STREQ(res.c_str(), "");
}

TEST(Utility, TrimWS_2) {
  const std::string str{" "};
  const std::string res{util::TrimWS(str)};
  EXPECT_TRUE(res.empty());
  EXPECT_STREQ(res.c_str(), "");
}

TEST(Utility, TrimWS_3) {
  const std::string str{"\t"};
  const std::string res{util::TrimWS(str)};
  EXPECT_TRUE(res.empty());
  EXPECT_STREQ(res.c_str(), "");
}

TEST(Utility, TrimWS_4) {
  const std::string str{"\n"};
  const std::string res{util::TrimWS(str)};
  EXPECT_TRUE(res.empty());
  EXPECT_STREQ(res.c_str(), "");
}

TEST(Utility, TrimWS_5) {
  const std::string str{"\r\n"};
  const std::string res{util::TrimWS(str)};
  EXPECT_TRUE(res.empty());
  EXPECT_STREQ(res.c_str(), "");
}

TEST(Utility, TrimWS_6) {
  const std::string str{" Hello"};
  const std::string res{util::TrimWS(str)};
  EXPECT_STREQ(res.c_str(), "Hello");
}

TEST(Utility, TrimWS_7) {
  const std::string str{"Hello "};
  const std::string res{util::TrimWS(str)};
  EXPECT_STREQ(res.c_str(), "Hello");
}

TEST(Utility, CommentRemoval_1) {
  const std::string str{"// f_byval({1, 2, 3}); // *** COMPILE ERROR ***"};
  const std::string res{std::get<0>(util::LineToCodeCmt(str, "//"))};
  EXPECT_STREQ(res.c_str(), "");
}

TEST(Utility, CommentRemoval_2) {
  const std::string str{"  // f_byval({1, 2, 3}); // *** COMPILE ERROR ***"};
  const std::string res{std::get<0>(util::LineToCodeCmt(str, "//"))};
  EXPECT_STREQ(res.c_str(), "  ");
}

#define SRC_PARSER_TEST(TEST_NAME); \
TEST(SrcParser, TEST_NAME) {        \
  const std::string test_name{#TEST_NAME}; \
  const std::string input{util::Read(GetDataPath("src_parsing/" + test_name + "_input.txt"))}; \
  std::ifstream out_file(GetDataPath("src_parsing/" + test_name + "_output.json")); \
  json data = json::parse(out_file); \
  const src::LineOffsetMap res{SRC_PARSER_CPP->GetCmtLineOffset(util::ToLines(input))}; \
  EXPECT_EQ(res.size(), data["cmt_offset"].size()); \
  for (auto&& [line, offset]: data["cmt_offset"].items()) { \
    const uint64_t line_num{util::FromStr<uint64_t>(line).value()}; \
    const int64_t offset_num{offset.get<int64_t>()}; \
    const std::string err_msg{"Expecting line " + std::to_string(line_num) + " to have offset " + std::to_string(offset_num) + "."}; \
    EXPECT_TRUE(res.find(line_num) != res.end()) << err_msg; \
    EXPECT_EQ(res.at(line_num), offset_num) << err_msg; \
  } \
}

SRC_PARSER_TEST(cpp_001);
SRC_PARSER_TEST(cpp_002);
SRC_PARSER_TEST(cpp_003);

TEST(SrcParser, Cpp_4) {
  const std::vector<std::string_view> lines{
      "#include <iostream>",
      "",
      "int main(int argc, char** argv) {",
      "  #pragma cmt beg -1",
      "  const int x{0};",
      "  std::cout << x << std::endl;",
      "  #pragma cmt end",
      "  return 0;",
      "}",
  };

  const src::LineOffsetMap res{SRC_PARSER_CPP->GetCmtLineOffset(lines)};
  EXPECT_EQ(res.size(), 2);
  EXPECT_EQ(res.at(4), -1);
  EXPECT_EQ(res.at(5), -1);
}

TEST(SrcParser, Cpp_5) {
  const std::vector<std::string_view> lines{
      "#include <iostream>",
      "",
      "int main(int argc, char** argv) {",
      "  #pragma cmt beg -1",
      "  const int x{0};",
      "  std::cout  // Only this line should print line number.",
      "    << x",
      "    << std::e\\",
      "ndl;",
      "  #pragma cmt end",
      "  return 0;",
      "}",
  };

  const src::LineOffsetMap res{SRC_PARSER_CPP->GetCmtLineOffset(lines)};
  EXPECT_EQ(res.size(), 2);
  EXPECT_EQ(res.at(4), -1);
  EXPECT_EQ(res.at(5), -1);
}

TEST(SrcParser, Cpp_6) {
  const std::vector<std::string_view> lines{
      /*  0 */ "#include <iostream>",
      /*  1 */ "",
      /*  2 */ "int main(int argc, char** argv) {",
      /*  3 */ "  #pragma cmt beg -1",
      /*  4 */ "  const int x{0};",                // <--
      /*  5 */ "  std::cout  // Random comment.",  // <--
      /*  6 */ "    << x",
      /*  7 */ "    << std::e\\",
      /*  8 */ "ndl;",
      /*  9 */ "  const int y{0}; // Comment test",  // <--
      /* 10 */ "  #pragma cmt ignore_once",
      /* 11 */ "  std::cout << y << std::endl;",
      /* 12 */ "",
      /* 13 */ "  const int _dymmy{};",  // <--
      /* 14 */ "  #pragma cmt end",
      /* 15 */ "  return 0;",
      /* 16 */ "}",
  };

  const src::LineOffsetMap res{SRC_PARSER_CPP->GetCmtLineOffset(lines)};
  EXPECT_EQ(res.size(), 4);
  EXPECT_EQ(res.at(4), -1);
  EXPECT_EQ(res.at(5), -1);
  EXPECT_EQ(res.at(9), -1);
  EXPECT_EQ(res.at(13), -1);
}

TEST(SrcParser, Cpp_7) {
  const std::vector<std::string_view> lines{
      /*  0 */ "#include <iostream>",
      /*  1 */ "",
      /*  2 */ "int main(int argc, char** argv) {",
      /*  3 */ "  #pragma cmt beg",
      /*  4 */ "  const int x{0};",                // <--
      /*  5 */ "  std::cout  // Random comment.",  // <--
      /*  6 */ "    << x",
      /*  7 */ "    << std::e\\",
      /*  8 */ "ndl;",
      /*  9 */ "  const int y{0};",  // <--
      /* 10 */ "  #pragma cmt ignore_once",
      /* 11 */ "  std::cout << y << std::endl;",
      /* 12 */ "",
      /* 13 */ "  const int _dymmy{};",  // <--
      /* 14 */ "  #pragma cmt end",
      /* 15 */ "  return 0;",
      /* 16 */ "}",
  };

  const src::LineOffsetMap res{SRC_PARSER_CPP->GetCmtLineOffset(lines)};
  EXPECT_EQ(res.size(), 4);
  EXPECT_EQ(res.at(4), 0);
  EXPECT_EQ(res.at(5), 3);
  EXPECT_EQ(res.at(9), 0);
  EXPECT_EQ(res.at(13), 0);
}

TEST(SrcParser, Cpp_8) {
  const std::vector<std::string_view> lines{
      /*  0 */ "#include <iostream>",
      /*  1 */ "",
      /*  2 */ "int main(int argc, char** argv) {",
      /*  3 */ "  #pragma cmt beg",
      /*  4 */ "  const int x{0};",  // <--
      /*  5 */ "  #pragma cmt ignore_once",
      /*  6 */ "  std::cout  // Random comment.",
      /*  7 */ "    << x",
      /*  8 */ "    << std::e\\",
      /*  9 */ "ndl;",
      /* 10 */ "  const int y{0};",               // <--
      /* 11 */ "  std::cout << y << std::endl;",  // <--
      /* 12 */ "",
      /* 13 */ "  const int _dymmy{};",  // <--
      /* 14 */ "  #pragma cmt end",
      /* 15 */ "  return 0;",
      /* 16 */ "}",
  };

  const src::LineOffsetMap res{SRC_PARSER_CPP->GetCmtLineOffset(lines)};
  EXPECT_EQ(res.size(), 4);
  EXPECT_EQ(res.at(4), 0);
  EXPECT_EQ(res.at(10), 0);
  EXPECT_EQ(res.at(11), 0);
  EXPECT_EQ(res.at(13), 0);
}

TEST(OutputParser, Cpp_1) {
  const output::CommentMap result{OUTPUT_PARSER_CPP.Parse(
      "int const&, T: int const&\n"
      "Value of T{}: 0\n"
      "[/tmp/src_code/items/item_1/item_1.cpp:137]:\n"
      "[/tmp/src_code/items/item_1/item_1.cpp:138]:Case 3:\n"
      "[/tmp/src_code/items/item_1/item_1.cpp:140]:ParamType: int, T: int")};
  EXPECT_EQ(result.size(), 1);
  const auto& item_1{result.at("/tmp/src_code/items/item_1/item_1.cpp")};
  EXPECT_EQ(item_1.size(), 2);
}

TEST(OutputParser, Cpp_Unix_1) {
  const output::OutputParser parser{"/private/var/src_code"};
  const output::CommentMap result{OUTPUT_PARSER_CPP.Parse("")};
  // TODO
}

TEST(OutputParser, Cpp_Windows_1) {
  const output::OutputParser parser{R"(C:\Windows\Program Files\SourceCode)"};
  const output::CommentMap result{OUTPUT_PARSER_CPP.Parse("")};
  // TODO
}

TEST(CmtModifier, Cpp_1) {
  const std::string content{
      "#include <iostream>\n"
      "\n"
      "int main(int argc, char** argv) {\n"
      "  #pragma cmt beg\n"
      "  const int x{0}; std::cout << x << std::endl;\n"
      "  #pragma cmt end\n"
      "  return 0;\n"
      "}\n"
  };
  const std::string result{CMT_MODIFIER_CPP.ParseAndReplaceComments(content, {
      {4, "example comment"}
  }, true)};
  const std::string expected{
      "#include <iostream>\n"
      "\n"
      "int main(int argc, char** argv) {\n"
      "  #pragma cmt beg\n"
      "  const int x{0}; std::cout << x << std::endl; //> example comment\n"
      "  #pragma cmt end\n"
      "  return 0;\n"
      "}\n"
  };
  EXPECT_STREQ(result.c_str(), expected.c_str());
}

TEST(CmtModifier, Cpp_2) {
  const std::string content{
      "#include <iostream>\n"
      "\n"
      "int main(int argc, char** argv) {\n"
      "  #pragma cmt beg\n"
      "  const int x{0}; std::cout << x << std::endl; // old comment\n"
      "  #pragma cmt end\n"
      "  return 0;\n"
      "}\n"
  };
  const std::string result{CMT_MODIFIER_CPP.ParseAndReplaceComments(content, {
      {4, "example comment"}
  }, true)};
  const std::string expected{
      "#include <iostream>\n"
      "\n"
      "int main(int argc, char** argv) {\n"
      "  #pragma cmt beg\n"
      "  const int x{0}; std::cout << x << std::endl; //> example comment\n"
      "  #pragma cmt end\n"
      "  return 0;\n"
      "}\n"
  };
  EXPECT_STREQ(result.c_str(), expected.c_str());
}
