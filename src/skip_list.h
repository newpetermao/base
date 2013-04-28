/** 
 * @file SkipList.c
 *
 * @author petermao
 *
 * @date 2011.11
 * 
 * @desc: 
 *		ʵ������
 *
 *		Skip List��������List���������ݽṹ�Ļ����ϵ���չ���������������ṹ�����ض�ֵ���ѵ����⣬
 		ʹ��Skip List������ʹ����һ����������������ض�ֵ��ʱ�临�Ӷ�ΪO(logn)��
		��һ�ֿ��Դ���ƽ���������ݽṹ��
		Skip listsӦ�ø��ʱ�֤ƽ�⣬ƽ���������ϸ����ת������ƽ�����������������������֤ƽ�⣬
		���Skip list�Ƚ�����ʵ�֣��������ƽ�������Žϸߵ�����Ч�ʡ� 
		��ʵ��ԭ����������ÿһ��Ԫ�ض���N��(NΪ�����������1<=N )
		
		redis.c
		Skip lists: a probabilistic alternative to balanced trees
		����SkipList:http://www.cnblogs.com/xuqiang/archive/2011/05/22/2053516.html
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
	int		level; // ����
	node_t 	*head;
}list_t;

// ��ʼ��skiplist
list_t* slCreate();

// �ͷ�skiplist
void slDestroy(list_t *list);

// ����
int slSearch(list_t *list, key_t key, val_t *pVal);

// ���룺����ֵ>=0������ɹ�
int slInsert(list_t *list, key_t key, val_t val);

// ɾ��
int slDelete(list_t *list, key_t key);


// ����һ���ڵ�(�ͷ�ʱ��free����)
static node_t *slCreateNode(key_t key, val_t val, int level);

// ���ؽ���1��MAXLEVEL֮�������
static int randomLevel();

#endif

