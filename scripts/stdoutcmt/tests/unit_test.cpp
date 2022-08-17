#include <gtest/gtest.h>

#include <memory>
#include <string_view>

#include "stdoutcmt/util/util.h"
#include "stdoutcmt/src_parser/factory.h"
#include "stdoutcmt/output_parser/parser.h"

using namespace outcmt;

const std::unique_ptr<src::SrcParserCpp> SRC_PARSER_CPP{};
const output::OutputParser OUTPUT_PARSER_CPP{};

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
  const std::string res{util::LineWithoutTrailingComment(str, "//")};
  EXPECT_STREQ(res.c_str(), "");
}

TEST(Utility, CommentRemoval_2) {
  const std::string str{"  // f_byval({1, 2, 3}); // *** COMPILE ERROR ***"};
  const std::string res{util::LineWithoutTrailingComment(str, "//")};
  EXPECT_STREQ(res.c_str(), "  ");
}

TEST(SrcParser, Cpp_1) {
  const std::vector<std::string_view> lines{
      "int main(int argc, char** argv) {",
      "  #pragma cmt beg",
      "  const int x{0};",
      "  #pragma cmt end",
      "  return 0;",
      "}",
  };

  const src::LineOffsetMap res {SRC_PARSER_CPP->GetCmtLineOffset(lines)};
  EXPECT_EQ(res.size(), 1);
  EXPECT_EQ(res.at(2), 0);
}

TEST(SrcParser, Cpp_3) {
  const std::vector<std::string_view> lines{
      "#include <iostream>",
      "",
      "int main(int argc, char** argv) {",
      "  #pragma cmt beg",
      "  const int x{0}; std::cout << x << std::endl;",
      "  #pragma cmt end",
      "  return 0;",
      "}",
  };

  const src::LineOffsetMap res {SRC_PARSER_CPP->GetCmtLineOffset(lines)};
  EXPECT_EQ(res.size(), 1);
  EXPECT_EQ(res.at(4), 0);
}


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

  const src::LineOffsetMap res {SRC_PARSER_CPP->GetCmtLineOffset(lines)};
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

  const src::LineOffsetMap res {SRC_PARSER_CPP->GetCmtLineOffset(lines)};
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
      /*  4 */ "  const int x{0};",  // <--
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

  const src::LineOffsetMap res {SRC_PARSER_CPP->GetCmtLineOffset(lines)};
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
      /*  4 */ "  const int x{0};",  // <--
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

  const src::LineOffsetMap res {SRC_PARSER_CPP->GetCmtLineOffset(lines)};
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
      /* 10 */ "  const int y{0};",  // <--
      /* 11 */ "  std::cout << y << std::endl;",  // <--
      /* 12 */ "",
      /* 13 */ "  const int _dymmy{};",  // <--
      /* 14 */ "  #pragma cmt end",
      /* 15 */ "  return 0;",
      /* 16 */ "}",
  };

  const src::LineOffsetMap res {SRC_PARSER_CPP->GetCmtLineOffset(lines)};
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
      "[/tmp/src_code/items/item_1/item_1.cpp:140]:ParamType: int, T: int"
  )};
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
  const output::OutputParser parser{"C:\\Windows\\Program Files\\SourceCode"};
  const output::CommentMap result{OUTPUT_PARSER_CPP.Parse("")};
  // TODO
}