// Author: petermao<petermaocom@gmail.com>
// Copyright (c) 2011-2021, petermao
// All rights reserved.

#include <stdio.h>
#include <stdlib.h>
#include "./priority_queue.h"

static inline int _cmp(const void* val1, const void* val2);
static void heapAdjustDown(array_t* arr, int start, cmp_func* cmp);
static void heapAdjustUp(array_t* arr, int start, cmp_func* cmp);

pq_queue_t* pqInit(size_t size) {
  pq_queue_t* pq = NULL;

  pq = (pq_queue_t *)malloc(sizeof(pq_queue_t));
  if (NULL == pq)
    return NULL;

  pq->arr = arrayInit(size);
  if (NULL == pq->arr) {
    free(pq);
    return NULL;
  }

  pq->cmp = _cmp;
  return pq;
}

void pqFree(pq_queue_t* pq) {
  if (NULL == pq)
    return;

  arrayFree(pq->arr);
  pq->arr = NULL;
  pq->cmp = NULL;
  free(pq);
}

/*
 * @ret  1  empty
 *       0  not empty
 */
int pqEmpty(pq_queue_t* pq) {
  if (NULL == pq || 0 == arraySize(pq->arr))
    return 1;
  return 0;
}

/*
 * @ret  0  success
 *       -1 invalid param
 *       -2 push error
 */
int pqPush(pq_queue_t* pq, void* val) {
  int iRet = 0;
  if (NULL == pq)
    return -1;

  iRet = arrayPush(pq->arr, val);
  if (0 != iRet)
    return -2;

  heapAdjustUp(pq->arr, arraySize(pq->arr) - 1, pq->cmp);
  return 0;
}

/*
 * @ret  not NULL success
 *       NULL invalid param or empty
 */
void* pqPop(pq_queue_t* pq) {
  void* tmp = NULL;

  if (NULL == pq)
    return NULL;

  tmp = arrayPop(pq->arr);
  if (arraySize(pq->arr) > 0) {
    tmp = arraySet(pq->arr, 0, tmp);
    heapAdjustDown(pq->arr, 0, pq->cmp);
  }

  return tmp;
}

static inline int _cmp(const void* val1, const void* val2) {
  return -1;
}

static void heapAdjustDown(array_t* arr, int start, cmp_func* cmp) {
  int size = 0;
  int left = 0;
  int largest = 0;
  void* tmp = NULL;

  size = arraySize(arr);
  largest = start;
  while (largest < size/2) {
    left = start * 2 + 1;
    if (left < size && cmp &&
        -1 == cmp(arrayGet(arr, largest), arrayGet(arr, left)))
      largest = left;

    if (left + 1 < size && cmp &&
        -1 == cmp(arrayGet(arr, largest), arrayGet(arr, left + 1)))
      largest = left + 1;

    if (largest == start)
      break;

    tmp = arrayGet(arr, largest);
    arraySet(arr, largest, arrayGet(arr, start));
    arraySet(arr, start, tmp);

    // swap(&a[largest], &a[start], );
    start = largest;
  }
}

static void heapAdjustUp(array_t* arr, int start, cmp_func* cmp) {
  int parent = 0;
  void* tmp = NULL;

  while (1) {
    parent = (start - 1)/2;
    if (start > 0 && cmp &&
        -1 == cmp(arrayGet(arr, parent) , arrayGet(arr, start))) {
      tmp = arrayGet(arr, parent);
      arraySet(arr, parent, arrayGet(arr, start));
      arraySet(arr, start, tmp);
      start = parent;
    } else {
      break;
    }
  }
}
