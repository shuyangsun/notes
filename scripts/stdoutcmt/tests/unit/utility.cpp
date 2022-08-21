#include <gtest/gtest.h>

#include <string_view>

#include "stdoutcmt/util/util.h"

TEST(Utility, TrimWS_1) {
  const std::string str{};
  const std::string res{outcmt::util::TrimWS(str)};
  EXPECT_TRUE(res.empty());
  EXPECT_STREQ(res.c_str(), "");
}

TEST(Utility, TrimWS_2) {
  const std::string str{" "};
  const std::string res{outcmt::util::TrimWS(str)};
  EXPECT_TRUE(res.empty());
  EXPECT_STREQ(res.c_str(), "");
}

TEST(Utility, TrimWS_3) {
  const std::string str{"\t"};
  const std::string res{outcmt::util::TrimWS(str)};
  EXPECT_TRUE(res.empty());
  EXPECT_STREQ(res.c_str(), "");
}

TEST(Utility, TrimWS_4) {
  const std::string str{"\n"};
  const std::string res{outcmt::util::TrimWS(str)};
  EXPECT_TRUE(res.empty());
  EXPECT_STREQ(res.c_str(), "");
}

TEST(Utility, TrimWS_5) {
  const std::string str{"\r\n"};
  const std::string res{outcmt::util::TrimWS(str)};
  EXPECT_TRUE(res.empty());
  EXPECT_STREQ(res.c_str(), "");
}

TEST(Utility, TrimWS_6) {
  const std::string str{" Hello"};
  const std::string res{outcmt::util::TrimWS(str)};
  EXPECT_STREQ(res.c_str(), "Hello");
}

TEST(Utility, TrimWS_7) {
  const std::string str{"Hello "};
  const std::string res{outcmt::util::TrimWS(str)};
  EXPECT_STREQ(res.c_str(), "Hello");
}

TEST(Utility, CmtParse_1) {
  const std::string str{"// f_byval({1, 2, 3}); // *** COMPILE ERROR ***"};
  const std::pair<std::string_view, std::string_view> parsed{outcmt::util::LineToCodeCmt(str, "//")};
  const std::string code{std::get<0>(parsed)};
  const std::string cmt{std::get<1>(parsed)};
  EXPECT_TRUE(code.empty());
  EXPECT_STREQ(str.c_str(), cmt.c_str());
}

TEST(Utility, CmtParse_2) {
  const std::string str{"  // f_byval({1, 2, 3}); // *** COMPILE ERROR ***"};
  const std::pair<std::string_view, std::string_view> parsed{outcmt::util::LineToCodeCmt(str, "//")};
  const std::string code{std::get<0>(parsed)};
  const std::string cmt{std::get<1>(parsed)};
  EXPECT_STREQ(code.c_str(), "  ");
  EXPECT_STREQ(cmt.c_str(), "// f_byval({1, 2, 3}); // *** COMPILE ERROR ***");
}
