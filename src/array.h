// Author: petermao<petermaocom@gmail.com>
// Copyright (c) 2011-2021, petermao
// All rights reserved.

#ifndef SRC_ARRAY_H_
#define SRC_ARRAY_H_

typedef struct {
  size_t size;
  size_t capacity;
  void (*free)(void* val);
  void **a;
}array_t;

#define arraySize(arr) ((arr)->size)
#define arrayCapacity(arr) ((arr)->capacity)
#define arraySetFree(arr, free) ((arr)->free = (free))

array_t* arrayInit(size_t size);
void arrayFree(array_t* arr);

/*
 * @ret  not NULL  success
 *           NULL  fail
 */
void* arrayGet(array_t* arr, int index);

/*
 * @ret  orig val
 */
void* arraySet(array_t* arr, int index, void* val);

/*
 * @ret  0  success
 *       -1 invalid param
 */
int arrayPush(array_t* arr, void* val);

/*
 * @ret  not NULL  success
 *           NULL  fail
 */
void* arrayPop(array_t* arr);

void arrayClear(array_t* arr);

#endif  // SRC_ARRAY_H_
