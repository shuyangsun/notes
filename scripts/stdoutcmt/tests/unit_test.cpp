#include <gtest/gtest.h>

#include <memory>
#include <string_view>

#include "stdoutcmt/util/util.h"
#include "stdoutcmt/src_parser/factory.h"

using namespace outcmt;

const std::unique_ptr<src::SrcParserCpp> PARSER_CPP{};

TEST(Utility, TrimWS_1) {
  const std::string str{" Hello"};
  const std::string res{util::TrimWS(str)};
  EXPECT_STREQ(res.c_str(), "Hello");
}

TEST(Utility, TrimWS_2) {
  const std::string str{"Hello "};
  const std::string res{util::TrimWS(str)};
  EXPECT_STREQ(res.c_str(), "Hello");
}

TEST(Parser, Cpp_1) {
  const std::vector<std::string_view> lines{
      "int main(int argc, char** argv) {",
      "  #pragma notes cmtbeg",
      "  const int x{0};",
      "  #pragma notes cmtend",
      "  return 0;",
      "}",
  };

  const src::LineOffsetMap res {PARSER_CPP->GetCmtLineOffset(lines)};
  EXPECT_EQ(res.size(), 1);
  EXPECT_EQ(res.at(2), 0);
}

TEST(Parser, Cpp_3) {
  const std::vector<std::string_view> lines{
      "#include <iostream>",
      "",
      "int main(int argc, char** argv) {",
      "  #pragma notes cmtbeg",
      "  const int x{0}; std::cout << x << std::endl;",
      "  #pragma notes cmtend",
      "  return 0;",
      "}",
  };

  const src::LineOffsetMap res {PARSER_CPP->GetCmtLineOffset(lines)};
  EXPECT_EQ(res.size(), 1);
  EXPECT_EQ(res.at(4), 0);
}


TEST(Parser, Cpp_4) {
  const std::vector<std::string_view> lines{
      "#include <iostream>",
      "",
      "int main(int argc, char** argv) {",
      "  #pragma notes cmtbeg -1",
      "  const int x{0};",
      "  std::cout << x << std::endl;",
      "  #pragma notes cmtend",
      "  return 0;",
      "}",
  };

  const src::LineOffsetMap res {PARSER_CPP->GetCmtLineOffset(lines)};
  EXPECT_EQ(res.size(), 2);
  EXPECT_EQ(res.at(4), -1);
  EXPECT_EQ(res.at(5), -1);
}

TEST(Parser, Cpp_5) {
  const std::vector<std::string_view> lines{
      "#include <iostream>",
      "",
      "int main(int argc, char** argv) {",
      "  #pragma notes cmtbeg -1",
      "  const int x{0};",
      "  std::cout  // Only this line should print line number.",
      "    << x",
      "    << std::e\\",
      "ndl;",
      "  #pragma notes cmtend",
      "  return 0;",
      "}",
  };

  const src::LineOffsetMap res {PARSER_CPP->GetCmtLineOffset(lines)};
  EXPECT_EQ(res.size(), 2);
  EXPECT_EQ(res.at(4), -1);
  EXPECT_EQ(res.at(5), 2);
}
