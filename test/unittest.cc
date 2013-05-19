// Author: petermao<petermaocom@gmail.com>
// Copyright (c) 2011-2021, petermao
// All rights reserved.

#include "gtest/gtest.h"
#include "config_unittest.cc"
#include "skip_list_unittest.cc"
#include "array_unittest.cc"
#include "priority_queue_unittest.cc"

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  testing::FLAGS_gtest_death_test_style = "threadsafe";
  return RUN_ALL_TESTS();
}
