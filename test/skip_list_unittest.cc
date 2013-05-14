// Author: petermao<petermaocom@gmail.com>
// Copyright (c) 2011-2021, petermao
// All rights reserved.

#include "gtest/gtest.h"
#include "./skip_list.h"

TEST(Test_slInit, Test_Init) {
  sl_list_t* list = NULL;

  list = slInit();
  // EXPECT_NE(NULL, list);
  slFree(list);
}

TEST(Test_slFind, Test_ParamInvalid) {
  sl_key_t key;
  sl_val_t val;
  sl_list_t* list = NULL;

  key = 3;
  val = malloc(sizeof(int));
  EXPECT_EQ(-1, slFind(list, key, &val));
}

TEST(Test_slFind, Test_NotFind) {
  sl_key_t key;
  sl_val_t val;
  sl_list_t* list = NULL;

  list = slInit();
  key = 3;
  val = malloc(sizeof(int));
  *((int *)val) = 20;
  EXPECT_EQ(-2, slFind(list, key, &val));
  slFree(list);
}

TEST(Test_slFind, Test_Success) {
  sl_key_t key;
  sl_val_t val;
  sl_val_t new_val;
  sl_list_t* list = NULL;

  list = slInit();
  key = 3;
  val = malloc(sizeof(int));
  *((int *)val) = 20;
  slAdd(list, key, val);
  EXPECT_EQ(0, slFind(list, key, &new_val));
  EXPECT_EQ(20, *((int *)new_val));
  slFree(list);
}

TEST(Test_slAdd, Test_ParamInvalid) {
  sl_key_t key;
  sl_val_t val;
  sl_list_t* list = NULL;

  key = 3;
  val = malloc(sizeof(int));
  EXPECT_EQ(-1, slAdd(list, key, val));
}

TEST(Test_slAdd, Test_NewKey) {
  sl_key_t key;
  sl_val_t val;
  sl_val_t new_val;
  sl_list_t* list = NULL;

  list = slInit();
  key = 3;
  val = malloc(sizeof(int));
  *((int *)val) = 20;
  EXPECT_EQ(0, slAdd(list, key, val));
  slFind(list, key, &new_val);
  EXPECT_EQ(20, *((int *)new_val));
  slFree(list);
}

TEST(Test_slAdd, Test_UpdateExistKey) {
  sl_key_t key;
  sl_val_t val;
  sl_val_t new_val;
  sl_list_t* list = NULL;

  list = slInit();
  key = 3;
  val = malloc(sizeof(int));
  new_val = malloc(sizeof(int));
  *((int *)val) = 20;
  EXPECT_EQ(0, slAdd(list, key, val));
  slFind(list, key, &val);
  EXPECT_EQ(20, *((int *)val));
  *((int *)new_val) = 200;
  EXPECT_EQ(1, slAdd(list, key, new_val));
  slFind(list, key, &val);
  EXPECT_EQ(200, *((int *)val));
  slFree(list);
}

TEST(Test_slDel, Test_ParamInvalid) {
  sl_key_t key;
  sl_list_t* list = NULL;

  key = 3;
  EXPECT_EQ(-1, slDel(list, key));
}

TEST(Test_slDel, Test_DelNotExistKey) {
  sl_key_t key;
  sl_val_t val;
  sl_list_t* list = NULL;

  list = slInit();
  key = 3;
  val = malloc(sizeof(int));
  *((int *)val) = 20;
  EXPECT_EQ(1, slDel(list, key));
  slFree(list);
}

TEST(Test_slDel, Test_DelExistKey) {
  sl_key_t key;
  sl_val_t val;
  sl_list_t* list = NULL;

  list = slInit();
  key = 3;
  val = malloc(sizeof(int));
  *((int *)val) = 20;
  slAdd(list, key, val);
  EXPECT_EQ(0, slDel(list, key));
  slFree(list);
}
