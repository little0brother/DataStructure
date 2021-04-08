#include <iostream>
using namespace std;

typedef char ElemeType;

typedef enum { Link = 0, Thread } PointerTag;

struct ThreadBiTNode
{
	ElemeType data;
	ThreadBiTNode* lchild;		// 指向左子树
	ThreadBiTNode* rchild;		// 指向右子树
	PointerTag ltag;			// 当ltag=0 表明lchild指向左子树   ltag=1 表明lchild指向该节点的遍历前驱
	PointerTag rtag;			// 当rtag=0 表明rchild指向右子树   rtag=1 表明lchild指向该节点的遍历后继
};

ThreadBiTNode* pPre = NULL;		// 指向当前节点的前一个 用于二叉树建立联系

// 使用前序遍历的方法创建二叉树
void CreateBiTree(ThreadBiTNode*& bt)
{
	ElemeType e;
	cin >> noskipws >> e;

	if (e == ' ')
	{
		bt = NULL;
	}
	else
	{
		bt = new ThreadBiTNode;
		bt->data = e;

		// 初始化标签为0
		bt->ltag = Link;
		bt->rtag = Link;

		CreateBiTree(bt->lchild);
		CreateBiTree(bt->rchild);
	}
}

// 中序遍历二叉树 为节点创建联系
void InOrderTraversalCreateThread(ThreadBiTNode*& bt)
{
	if (bt)
	{
		InOrderTraversalCreateThread(bt->lchild);

		// 如果左子树为空 则将lchild节点指向前驱
		if (!bt->lchild)
		{
			bt->ltag = Thread;
			bt->lchild = pPre;
		}

		// 如果上一个节点右子树为空 则将rchild节点指向后继
		if (!pPre->rchild)
		{
			pPre->rtag = Thread;
			pPre->rchild = bt;
		}

		pPre = bt;

		InOrderTraversalCreateThread(bt->rchild);
	}
}

// 中序遍历线索化二叉树 (初始化pPre指针的指向)
void InOrderTraversal(ThreadBiTNode*& bt)
{
	// 创建头节点指向 二叉树根节点 线索化二叉树
	ThreadBiTNode* head = new ThreadBiTNode;
	head->ltag = Link;
	head->rtag = Thread;
	head->rchild = head;

	if (bt == NULL)
	{
		head->lchild = head;
	}
	else
	{
		head->lchild = bt;
		pPre = head;

		InOrderTraversalCreateThread(bt);

		pPre->rtag = Thread;
		pPre->rchild = head;	// 最后一个节点的后继线索指向head
		head->rchild = pPre;
	}
}

//通过迭代的方式中序遍历二叉树
void InOrderTraByItreat(ThreadBiTNode* bt)
{
	while (bt != pPre->rchild)
	{
		// 寻找最左节点
		while (bt->ltag == Link)
		{
			bt = bt->lchild;
		}

		cout << bt->data << " ";

		// 寻找前驱
		while (bt->rtag == Thread && bt != pPre)
		{
			bt = bt->rchild;
			cout << bt->data << " ";
		}

		// 当前节点没有前驱则指向当前节点的右子树  防止死循环
		bt = bt->rchild;
	}
}

int main()
{
	ThreadBiTNode* bt = NULL;

	CreateBiTree(bt);

	InOrderTraversal(bt);

	InOrderTraByItreat(bt);

	return 0;
}