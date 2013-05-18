// Author: petermao<petermaocom@gmail.com>
// Copyright (c) 2011-2021, petermao
// All rights reserved.

#include "gtest/gtest.h"
#include "./array.h"

TEST(Test_arrayInit, Test_Init) {
  array_t* arr = NULL;

  arr = arrayInit(4);
  EXPECT_NE((array_t *)(NULL), arr);

  EXPECT_EQ(0, arraySize(arr));
  EXPECT_EQ(8, arrayCapacity(arr));
  arrayFree(arr);
}

TEST(Test_arrayGet, Test_ParamInvalid) {
  array_t* arr = NULL;

  EXPECT_EQ((void *)(NULL), arrayGet(NULL, 0));
  EXPECT_EQ((void *)(NULL), arrayGet(arr, 0));
  arr = arrayInit(8);
  EXPECT_EQ((void *)(NULL), arrayGet(arr, -10));
  EXPECT_EQ((void *)(NULL), arrayGet(arr, 10));
  arrayFree(arr);
}

TEST(Test_arrayGet, Test_Success) {
  int* val = NULL;
  array_t* arr = NULL;

  val = (int *)malloc(sizeof(int));
  *val = 100;
  arr = arrayInit(8);
  arrayPush(arr, val);
  val = (int *)arrayGet(arr, 0);
  EXPECT_NE((int *)(NULL), val);
  EXPECT_EQ(100, *val);
  free(val);
  arrayFree(arr);
}

TEST(Test_arraySet, Test_ParamInvalid) {
  int* val = NULL;
  array_t* arr = NULL;

  val = (int *)malloc(sizeof(int));
  *val = 100;
  EXPECT_EQ((void *)(NULL), arraySet(NULL, 0, val));
  EXPECT_EQ((void *)(NULL), arraySet(arr, 0, val));
  arr = arrayInit(8);
  arrayPush(arr, val);
  EXPECT_EQ((void *)(NULL), arraySet(arr, -10, val));
  EXPECT_EQ((void *)(NULL), arraySet(arr, 10, val));
  free(val);
  arrayFree(arr);
}

TEST(Test_arraySet, Test_Success) {
  int* val = NULL;
  int* orig_val = NULL;
  array_t* arr = NULL;

  val = (int *)malloc(sizeof(int));
  *val = 100;
  arr = arrayInit(8);
  arrayPush(arr, val);
  orig_val = (int *)arraySet(arr, 0, val);
  EXPECT_NE((int *)(NULL), orig_val);
  free(val);
  arrayFree(arr);
}

TEST(Test_arrayPush, Test_ParamInvalid) {
  int* val = NULL;

  EXPECT_EQ(-1, arrayPush(NULL, val));
}

TEST(Test_arrayPush, Test_Success) {
  int* val = NULL;
  array_t* arr = NULL;

  val = (int *)malloc(sizeof(int));
  *val = 100;
  arr = arrayInit(8);
  EXPECT_EQ(0, arrayPush(arr, val));
}

TEST(Test_arrayPop, Test_ParamInvalid) {
  EXPECT_EQ((void *)NULL, arrayPop(NULL));
}

TEST(Test_arrayPop, Test_Success) {
  int* val = NULL;
  int* orig_val = NULL;
  array_t* arr = NULL;

  val = (int *)malloc(sizeof(int));
  *val = 100;
  arr = arrayInit(8);
  EXPECT_EQ(0, arrayPush(arr, val));
  val = (int *)arrayPop(arr);
  EXPECT_NE((int *)NULL, val);
  EXPECT_EQ(100, *val);
}

TEST(Test_arrayClear, Test_ParamInvalid) {
  arrayClear(NULL);
}

TEST(Test_arrayClear, Test_Success) {
  int* val = NULL;
  array_t* arr = NULL;

  val = (int *)malloc(sizeof(int));
  *val = 100;
  arr = arrayInit(8);
  EXPECT_EQ(0, arrayPush(arr, val));
  EXPECT_EQ(1, arraySize(arr));
  arrayClear(arr);
  EXPECT_EQ(0, arraySize(arr));
}
