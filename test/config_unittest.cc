// Author: petermao<petermaocom@gmail.com>
// Copyright (c) 2011-2021, petermao
// All rights reserved.

#include "gtest/gtest.h"
#include "./config.h"

TEST(Test_Config_Init, Test_Input_Empty) {
  Config config;
  EXPECT_EQ(-1, config.Init(""));
}

TEST(Test_Config_Init, Test_Input_NotExist) {
  Config config;
  EXPECT_EQ(-2, config.Init("abcdefg"));
}

TEST(Test_Config_Init, Test_Input_LineTooLong) {
  Config config;
  EXPECT_EQ(-3, config.Init("../test/data/config.0"));
}

TEST(Test_Config_Init, Test_Input_Success) {
  Config config;
  EXPECT_EQ(0, config.Init("../test/data/config.1"));
}

TEST(Test_Config_Get, Test_Input_Invalid) {
  std::string val;
  Config config;
  EXPECT_EQ(0, config.Init("../test/data/config.1"));
  EXPECT_EQ(-1, config.Get("", "host", &val));
  EXPECT_EQ(-1, config.Get("Process", "", &val));
  EXPECT_EQ(-1, config.Get("Process", "host", NULL));
}

TEST(Test_Config_Get, Test_Input_InitFail) {
  std::string val;
  Config config;
  EXPECT_EQ(-2, config.Get("Process", "host", &val));
}

TEST(Test_Config_Get, Test_Input_BadSection) {
  std::string val;
  Config config;
  EXPECT_EQ(0, config.Init("../test/data/config.1"));
  EXPECT_EQ(-3, config.Get("PROCESS", "host", &val));
}

TEST(Test_Config_Get, Test_Input_BadKey) {
  std::string val;
  Config config;
  EXPECT_EQ(0, config.Init("../test/data/config.1"));
  EXPECT_EQ(-4, config.Get("Process", "Host", &val));
}

TEST(Test_Config_Get, Test_Input_Success) {
  std::string val;
  Config config;
  EXPECT_EQ(0, config.Init("../test/data/config.1"));
  EXPECT_EQ(0, config.Get("Process", "host", &val));
  EXPECT_EQ("10.10.0.0", val);
  EXPECT_EQ(0, config.Get("Log", "host", &val));
  EXPECT_EQ("127.0.0.1", val);
}
