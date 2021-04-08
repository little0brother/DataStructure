/*
* 双亲孩子表示法
*	由数组和链表构成
*/

#define MAX_INIT_TREE 10

typedef char ElemeType;

// 孩子节点
struct CTNode
{
	int child;		 // 存放孩子节点的数组下标
	CTNode* next;	 // 指向下一个孩子节点
};

// 表头结构
struct CTBox
{
	ElemeType e;		// 存放树中节点的数据
	int parent;			// 存放双亲的下标

	CTNode* firstChild;	// 指向第一个孩子节点的指针
};

// 树结构
struct Tree
{
	CTBox tree[MAX_INIT_TREE];		// 表头节点数组
	int r;							// 树根的位置
	int n;							// 节点个数
};