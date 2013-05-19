// Author: petermao<petermaocom@gmail.com>
// Copyright (c) 2011-2021, petermao
// All rights reserved.

#ifndef SRC_PRIORITY_QUEUE_H_
#define SRC_PRIORITY_QUEUE_H_

#include "./array.h"

typedef int(cmp_func)(const void* val1, const void* val2);
typedef struct {
  cmp_func* cmp;
  array_t* arr;
}pq_queue_t;


#define pqSize(pq) (arraySize((pq)->arr))
#define pqSetFree(pq, free) (arraySetFree((pq)->arr, (free)))
#define pqSetCmp(pq, cmp) ((pq)->cmp = (cmp))

pq_queue_t* pqInit(size_t size);
void pqFree(pq_queue_t* pq);

/*
 * @ret  1  empty
 *       0  not empty
 */
int pqEmpty(pq_queue_t* pq);

/*
 * @ret  0  success
 *       -1 invalid param
 *       -2 push error
 */
int pqPush(pq_queue_t* pq, void* val);

/*
 * @ret  not NULL success
 *       NULL invalid param or empty
 */
void* pqPop(pq_queue_t* pq);

#endif  // SRC_PRIORITY_QUEUE_H_
