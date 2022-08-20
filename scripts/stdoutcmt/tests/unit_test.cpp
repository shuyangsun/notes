#include <gtest/gtest.h>

#include <memory>

#include <nlohmann/json.hpp>

#include "stdoutcmt/output_parser/parser.h"
#include "stdoutcmt/src_parser/factory.h"
#include "stdoutcmt/cmt_modifier/factory.h"

using namespace outcmt;
using json = nlohmann::json;

static const output::OutputParser OUTPUT_PARSER_CPP{};
static const src::CmtModifier CMT_MODIFIER_CPP{src::CmtModifierFactory{}.BuildModifier(src::FileType::Cpp)};

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
