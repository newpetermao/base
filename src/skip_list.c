/** 
 * @file SkipList.c
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "SkipList.h"

// 创建一个节点(释放时用free即可)
static node_t *slCreateNode(key_t key, val_t val, int level)
{
	int i;
	node_t *node;
	
	node = (node_t*)malloc(sizeof(node_t) + level * sizeof(node_t *));
	if (NULL == node)
		return NULL;
	
	node->key = key;
	node->val = val;
	for (i = 0; i < level; i++)
		node->forward[i] = NULL;
	
	return node;
}

// 返回介于1至MAXLEVEL之间的整数
static int randomLevel()
{
	int level = 1;
	while ((rand() & 0xffff) < (SKIPLIST_P * 0xffff))
		level = level + 1;
	
	if (level > MAXLEVEL)
		level = MAXLEVEL;
	
	return level;
}

// 初始化skiplist
list_t* slCreate()
{
	list_t *list = (list_t *)malloc(sizeof(list_t));
	if (NULL == list)
		return NULL;
	
	list->level = 0;
	list->head  = slCreateNode(0, 0, MAXLEVEL);
	if (NULL == list->head)
	{
		free(list);
		list = NULL;
	}
	
	return list;
}

// 释放skiplist
void slDestroy(list_t *list)
{
	int level ;
	node_t *node = NULL;
	node_t *next = NULL;
	
	if (NULL == list)
		return;
	
	node  = list->head;
	while (node)
	{
		next = node->forward[0];
		free(node);
		node = next;
	}
	
	free(list);
	list = NULL;
}

// 查找
int slSearch(list_t *list, key_t key, val_t *pVal)
{
	int level = list->level - 1;
	node_t *node = NULL;
	
	//assert(pVal != NULL);
	
	// 一直查到最底层
	node = list->head;
	while (level >= 0)
	{
		while (node->forward[level] && node->forward[level]->key <= key) // 此处是<=
		{
			node = node->forward[level];
		}
		
		if (node->key == key)
		{
			if (pVal)
			{
				*pVal = node->val; //根据实际情况可改用其他的复制操作
			}
			
			return 1;
		}
		
		level--;
	}

	return 0;
}

// 插入：返回值>=0，插入成功
int slInsert(list_t *list, key_t key, val_t val)
{
	int i;
	int level = list->level - 1;
	node_t *update[MAXLEVEL];
	node_t *pri  = NULL;
	node_t *node = NULL;
	
	// 一直查到最底层
	pri = list->head;
	while (level >= 0)
	{
		node = pri->forward[level];
		while (node && node->key < key)
		{
			pri	 = node;
			node = node->forward[level];
		}
		
		update[level] = pri; //记下每一层的位置
		level--;
	}
	
	// key相同，直接更新
	if (node && node->key == key)
	{
		node->val = val;
		return 1;
	}
	
	// 更新level
	level = randomLevel();
	printf("level:%d\n", level);
	if (level > list->level)
	{
		for (i = list->level; i < level; i++)
		{
			update[i] = list->head;
		}
		
		list->level = level;
	}

	// 插入节点
	node = slCreateNode(key, val, level);
	for (i = 0; i < level; i++)
	{
		node->forward[i] = update[i]->forward[i];
		update[i]->forward[i] = node;
	}

	return 0;
}

// 删除
int slDelete(list_t *list, key_t key)
{
	int i;
	int level = list->level - 1;
	node_t *update[MAXLEVEL];
	node_t *pri  = NULL;
	node_t *node = NULL;
	
	// 一直查到最底层
	pri = list->head;
	while (level >= 0)
	{
		node = pri->forward[level];
		while (node && node->key < key)
		{
			pri	 = node;
			node = node->forward[level];
		}
		
		update[level] = pri; //记下每一层的位置
		level--;
	}
	
	if (node && node->key == key)
	{
		for (i = 0; i < list->level; i++)
		{
			if (update[i]->forward[i] == node)
			{
				update[i]->forward[i] = node->forward[i];
			}
		}
		
		free(node);
		
		for (i = list->level - 1; i >= 0; i--)
		{
			if (NULL == list->head->forward[i]) // 此处
				list->level--;
		}
		
		return 0;
	}
	
	return -1;
}

#ifdef TEST
int main()
{
	list_t *list;
	int ret;
	val_t val;
	
	// test 0:对空链表进行操作
	printf("test0\n");
	list = slCreate();
	slDestroy(list);
	
	list = slCreate();
	ret = slSearch(list, 3, &val);
	printf("search:%d %d\n", ret, val);
	slDestroy(list);
	
	list = slCreate();
	ret = slInsert(list, 3, -1);
	printf("insert:%d\n", ret);
	slDestroy(list);
	
	list = slCreate();
	ret = slDelete(list, 3);
	printf("delete:%d\n", ret);
	slDestroy(list);
	
	// test 1:插入更新查找
	printf("test1\n");
	list = slCreate();
	ret = slInsert(list, 3, -1);
	printf("insert:%d\n", ret);
	
	ret = slInsert(list, 20, 200);
	printf("insert:%d\n", ret);
	
	ret = slInsert(list, 3, 100);
	printf("insert:%d\n", ret);
	
	ret = slSearch(list, 3, &val);
	printf("search:%d %d\n", ret, val);
	
	ret = slSearch(list, 20, &val);
	printf("search:%d %d\n", ret, val);
	
	ret = slSearch(list, 50, &val);
	printf("search:%d %d\n", ret, val);
	
	ret = slDelete(list, 3);
	printf("delete:%d\n", ret);
	
	ret = slSearch(list, 3, &val);
	printf("search:%d %d\n", ret, val);
	
	return 0;
}
#endif
