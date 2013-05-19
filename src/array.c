// Author: petermao<petermaocom@gmail.com>
// Copyright (c) 2011-2021, petermao
// All rights reserved.

#include <stdio.h>
#include <stdlib.h>
#include "./array.h"

static inline void _free(void* val) {
  free(val);
}

array_t* arrayInit(size_t size) {
  array_t* arr = NULL;

  arr = (array_t *)malloc(sizeof(array_t));
  if (NULL == arr)
    return NULL;

  if (8 > size)
    size = 8;

  arr->size = 0;
  arr->capacity = size;
  arr->free = _free;
  arr->a = (void **)malloc(arr->capacity * sizeof(void *));
  if (NULL == arr->a) {
    free(arr);
    return NULL;
  }

  return arr;
}

void arrayFree(array_t* arr) {
  size_t i = 0;

  if (NULL == arr || NULL == arr->a)
    return;

  if (arr->free) {
    for (i = 0; i < arr->size; i++) {
      if (NULL == arr->a[i])
        continue;
      arr->free(arr->a[i]);
      arr->a[i] = NULL;
    }
  }

  arr->size = 0;
  arr->capacity = 0;
  arr->free = NULL;
  if (arr->a) {
    free(arr->a);
    arr->a = NULL;
  }

  free(arr);
}

/*
 * @ret  not NULL  success
 *           NULL  fail
 */
void* arrayGet(array_t* arr, int index) {
  if (NULL == arr || NULL == arr->a)
    return NULL;
  if (index < 0 || index >= (int)arr->size)
    return NULL;

  return arr->a[index];
}

/*
 * @ret  orig val
 */
void* arraySet(array_t* arr, int index, void* val) {
  void* orig = NULL;
  if (NULL == arr || NULL == arr->a)
    return NULL;

  if (index < 0 || index >= (int)arr->size)
    return NULL;

  orig = arr->a[index];
  arr->a[index] = val;
  return orig;
}

/*
 * @ret  0  success
 *       -1 invalid param
 *       -2 mem exceed
 */
int arrayPush(array_t* arr, void* val) {
  void** tmp = NULL;

  if (NULL == arr || NULL == arr->a)
    return -1;

  if (arr->size >= arr->capacity) {
    arr->capacity <<= 1;
    tmp = (void **)realloc(arr->a, arr->capacity * sizeof(void *));
    if (NULL == tmp)
      return -2;

    arr->a = tmp;
  }

  arr->a[arr->size] = val;
  arr->size++;
  return 0;
}

/*
 * @ret  not NULL  success
 *           NULL  fail
 */
void* arrayPop(array_t* arr) {
  if (NULL == arr || NULL == arr->a || arr->size <= 0)
    return NULL;

  arr->size--;
  return arr->a[arr->size];
}

void arrayClear(array_t* arr) {
  size_t i = 0;

  if (NULL == arr || NULL == arr->a)
    return;

  if (arr->free) {
    for (i = 0; i < arr->size; i++) {
      if (NULL == arr->a[i])
        continue;
      arr->free(arr->a[i]);
      arr->a[i] = NULL;
    }
  }

  arr->size = 0;
}
