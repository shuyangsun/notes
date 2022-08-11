#include <gtest/gtest.h>

#include <string>
#include <string_view>

#include "stdoutcmt/util/util.h"

using namespace outcmt;

TEST(Utility, TrimWS_0) {
  const std::string str{" Hello"};
  const std::string res{util::TrimWS(str)};
  EXPECT_STREQ(res.c_str(), "Hello");
}

TEST(Utility, TrimWS_1) {
  const std::string str{"Hello "};
  const std::string res{util::TrimWS(str)};
  EXPECT_STREQ(res.c_str(), "Hello");
}
