// Author: petermao<petermaocom@gmail.com>
// Copyright (c) 2011-2021, petermao
// All rights reserved.

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "./skip_list.h"

static int randomLevel();
static sl_node_t* slCreateNode(sl_key_t key, sl_val_t val, int level);

sl_list_t* slInit() {
  sl_list_t* list = NULL;

  list = (sl_list_t *)malloc(sizeof(sl_list_t));
  if (NULL == list)
    return NULL;

  list->level = 0;
  list->head  = slCreateNode(SL_MIN_KEY, NULL, SL_MAXLEVEL);
  if (NULL == list->head) {
    free(list);
    list = NULL;
  }

  return list;
}

// free all node
void slFree(sl_list_t* list) {
  sl_node_t* node = NULL;
  sl_node_t* next = NULL;

  if (NULL == list)
    return;

  node  = list->head;
  while (node) {
    next = node->forward[0];
    free(node->val);
    free(node);
    node = next;
  }

  free(list);
  list = NULL;
}

/*
 * @ret  0   success
 *       -1  param invalid
 *       -2  not find
 */
int slFind(sl_list_t* list, sl_key_t key, sl_val_t* val) {
  int level = 0;
  sl_node_t* node = NULL;

  if (NULL == list)
    return -1;

  level = list->level - 1;
  node = list->head;
  while (0 <= level) {
    while (node->forward[level] &&
           node->forward[level]->key <= key)
      node = node->forward[level];

    if (node->key == key) {
      *val = node->val;
      return 0;
    }

    level--;
  }

  return -2;
}

/*
 * @ret  0   success and new key
 *       1   success and update exist key(free old)
 *       -1  param invalid
 *       -2  malloc fail
 */
int slAdd(sl_list_t* list, sl_key_t key, sl_val_t val) {
  int i = 0;
  int level = 0;
  sl_node_t* pre  = NULL;
  sl_node_t* node = NULL;
  sl_node_t* update[SL_MAXLEVEL];

  if (NULL == list)
    return -1;

  level = list->level - 1;
  pre = list->head;
  while (0 <= level) {
    node = pre->forward[level];
    while (node && node->key < key) {
      pre  = node;
      node = node->forward[level];
    }

    update[level] = pre;
    level--;
  }

  if (node && node->key == key) {
    free(node->val);
    node->val = val;
    return 1;
  }

  level = randomLevel();
  if (level > list->level) {
    for (i = list->level; i < level; i++)
      update[i] = list->head;

    list->level = level;
  }

  node = slCreateNode(key, val, level);
  if (NULL == node)
    return -2;

  for (i = 0; i < level; i++) {
    node->forward[i] = update[i]->forward[i];
    update[i]->forward[i] = node;
  }

  return 0;
}

/*
 * @ret  0   success and del exist key(free old)
 *       1   success and del not exist key
 *       -1  param invalid
 */
int slDel(sl_list_t* list, sl_key_t key) {
  int i = 0;
  int level = 0;
  sl_node_t* pre  = NULL;
  sl_node_t* node = NULL;
  sl_node_t* update[SL_MAXLEVEL];

  if (NULL == list)
    return -1;

  level = list->level - 1;
  pre = list->head;
  while (0 <= level) {
    node = pre->forward[level];
    while (node && node->key < key) {
      pre  = node;
      node = node->forward[level];
    }

    update[level] = pre;
    level--;
  }

  if (node && node->key == key) {
    for (i = 0; i < list->level; i++) {
      if (update[i]->forward[i] == node) {
        update[i]->forward[i] = node->forward[i];
      }
    }

    free(node->val);
    free(node);
    for (i = list->level - 1; i >= 0; i--) {
      if (NULL == list->head->forward[i])
        list->level--;
    }

    return 0;
  }

  return 1;
}

void slPrint(sl_list_t* list) {
  sl_node_t* node = NULL;

  node = list->head;
  node = node->forward[0];
  while (node) {
    printf("key:%d    ", node->key);
    printf("val:%d\n", *(int *)node->val);
    node = node->forward[0];
  }
}

static sl_node_t* slCreateNode(sl_key_t key, sl_val_t val, int level) {
  int i = 0;
  sl_node_t* node = NULL;

  node = (sl_node_t*)malloc(sizeof(sl_node_t) + level * sizeof(sl_node_t *));
  if (NULL == node)
    return NULL;

  node->key = key;
  node->val = val;
  for (i = 0; i < level; i++)
    node->forward[i] = NULL;

  return node;
}

static int randomLevel() {
  int level = 1;

  while ((rand() & 0xffff) < (SL_P * 0xffff))
    level = level + 1;

  if (level > SL_MAXLEVEL)
    level = SL_MAXLEVEL;

  return level;
}
