/** 
 * @file SkipList.c
 *
 * @author petermao
 *
 * @date 2011.11
 * 
 * @desc: 
 *		实现跳表
 *
 *		Skip List是在有序List（链表）数据结构的基础上的扩展，解决了有序链表结构查找特定值困难的问题，
 		使用Skip List，可以使得在一个有序链表里查找特定值的时间复杂度为O(logn)，
		是一种可以代替平衡树的数据结构。
		Skip lists应用概率保证平衡，平衡树采用严格的旋转（比如平衡二叉树有左旋右旋）来保证平衡，
		因此Skip list比较容易实现，而且相比平衡树有着较高的运行效率。 
		其实现原理是链表中每一个元素都有N层(N为随机数，并且1<=N )
		
		redis.c
		Skip lists: a probabilistic alternative to balanced trees
		跳表SkipList:http://www.cnblogs.com/xuqiang/archive/2011/05/22/2053516.html
 */

#ifndef MINI_SKIPLIST
#define MINI_SKIPLIST

#define MAXLEVEL 16
#define SKIPLIST_P 0.25

typedef int key_t;
typedef int val_t;

typedef struct node_t
{
	key_t 		key;
	val_t 		val;
	struct node_t *forward[];
}node_t;

typedef struct
{
	int		level; // 层数
	node_t 	*head;
}list_t;

// 初始化skiplist
list_t* slCreate();

// 释放skiplist
void slDestroy(list_t *list);

// 查找
int slSearch(list_t *list, key_t key, val_t *pVal);

// 插入：返回值>=0，插入成功
int slInsert(list_t *list, key_t key, val_t val);

// 删除
int slDelete(list_t *list, key_t key);


// 创建一个节点(释放时用free即可)
static node_t *slCreateNode(key_t key, val_t val, int level);

// 返回介于1至MAXLEVEL之间的整数
static int randomLevel();

#endif

