// Author: petermao<petermaocom@gmail.com>
// Copyright (c) 2011-2021, petermao
// All rights reserved.

#include "gtest/gtest.h"
#include "./priority_queue.h"

static int cmp(const void* val1, const void* val2) {
  int int1 = *(int *)val1;
  int int2 = *(int *)val2;

  if (int1 == int2)
    return 0;
  if (int1 < int2)
    return -1;
  return 1;
}

static void free_int(void* val) {
  free(val);
}

TEST(Test_pqInit, Test_Init) {
  pq_queue_t* pq = NULL;

  pq = pqInit(4);
  EXPECT_NE((pq_queue_t *)(NULL), pq);

  pqSetCmp(pq, cmp);
  pqSetFree(pq, free_int);
  EXPECT_EQ(0, pqSize(pq));
  pqFree(pq);
}

TEST(Test_pqEmpty, Test_ParamInvalid) {
  EXPECT_EQ(1, pqEmpty(NULL));
}

TEST(Test_pqEmpty, Test_Empty) {
  pq_queue_t* pq = NULL;

  pq = pqInit(4);
  EXPECT_EQ(1, pqEmpty(pq));
  pqFree(pq);
}

TEST(Test_pqEmpty, Test_NotEmpty) {
  int* val = NULL;
  pq_queue_t* pq = NULL;

  pq = pqInit(4);
  val = (int *)malloc(sizeof(int));
  pqPush(pq, val);
  EXPECT_EQ(0, pqEmpty(pq));
  pqFree(pq);
}

TEST(Test_pqPush, Test_ParamInvalid) {
  EXPECT_EQ(-1, pqPush(NULL, NULL));
}

TEST(Test_pqPush, Test_Success) {
  int* val = NULL;
  pq_queue_t* pq = NULL;

  pq = pqInit(4);
  val = (int *)malloc(sizeof(int));
  EXPECT_EQ(0, pqPush(pq, val));
  pqFree(pq);
}

TEST(Test_pqPop, Test_ParamInvalid) {
  EXPECT_EQ((int *)NULL, pqPop(NULL));
}

TEST(Test_pqPop, Test_Empty) {
  pq_queue_t* pq = NULL;

  pq = pqInit(4);
  EXPECT_EQ((int *)NULL, pqPop(pq));
  pqFree(pq);
}

TEST(Test_pqPop, Test_Success) {
  int* val = NULL;
  int* top_val = NULL;
  pq_queue_t* pq = NULL;

  pq = pqInit(4);
  val = (int *)malloc(sizeof(int));
  *val = 200;
  pqPush(pq, val);
  top_val = (int *)pqPop(pq);
  EXPECT_NE((int *)NULL, top_val);
  EXPECT_EQ(200, *top_val);
  free(top_val);
  pqFree(pq);
}

TEST(Test_pqPushPop, Test_Empty) {
  int* val = NULL;
  int* top_val = NULL;
  pq_queue_t* pq = NULL;

  pq = pqInit(4);
  pqSetCmp(pq, cmp);
  pqSetFree(pq, free_int);
  val = (int *)malloc(sizeof(int));
  *val = 200;
  pqPush(pq, val);
  val = (int *)malloc(sizeof(int));
  *val = 100;
  pqPush(pq, val);
  val = (int *)malloc(sizeof(int));
  *val = 400;
  pqPush(pq, val);
  top_val = (int *)pqPop(pq);
  EXPECT_NE((int *)NULL, top_val);
  EXPECT_EQ(400, *top_val);
  free(top_val);
  top_val = (int *)pqPop(pq);
  EXPECT_NE((int *)NULL, top_val);
  EXPECT_EQ(200, *top_val);
  free(top_val);
  top_val = (int *)pqPop(pq);
  EXPECT_NE((int *)NULL, top_val);
  EXPECT_EQ(100, *top_val);
  free(top_val);
  pqFree(pq);
}
