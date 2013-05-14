// Author: petermao<petermaocom@gmail.com>
// Copyright (c) 2011-2021, petermao
// All rights reserved.

#ifndef SRC_SKIP_LIST_H_
#define SRC_SKIP_LIST_H_

#define SL_MAXLEVEL 16
#define SL_P 0.25
#define SL_MIN_KEY (-2147483648)

typedef int sl_key_t;
typedef void* sl_val_t;

typedef struct sl_node_t {
  sl_key_t key;
  sl_val_t val;
  struct sl_node_t* forward[];
}sl_node_t;

typedef struct {
  int level;
  sl_node_t* head;
}sl_list_t;

sl_list_t* slInit();
// free all node
void slFree(sl_list_t* list);

/*
 * @ret  0   success
 *       -1  param invalid
 *       -2  not find
 */
int slFind(sl_list_t* list, sl_key_t key, sl_val_t* val);

/*
 * @ret  0   success and new key
 *       1   success and update exist key(free old)
 *       -1  param invalid
 *       -2  malloc fail
 */
int slAdd(sl_list_t* list, sl_key_t key, sl_val_t val);

/*
 * @ret  0   success and del exist key(free old)
 *       1   success and del not exist key
 *       -1  param invalid
 */
int slDel(sl_list_t* list, sl_key_t key);

void slPrint(sl_list_t* list);

#endif  // SRC_SKIP_LIST_H_
