// 建立二叉树(使用递归的方法) 并输出(递归)每个字符所在的层数

#include <iostream>
using namespace std;

typedef char ElemeType;

struct BTNode
{
	ElemeType data;		// 数据域
	BTNode* lchild;		// 左子树
	BTNode* rchild;		// 右子树
};

// 按照前序遍历的方式创建二叉树
void CreateBTree(BTNode *&bt)
{
	ElemeType e;
	cin >> noskipws >> e;

	if (e == ' ')
	{
		bt = NULL;
	}
	else
	{
		bt = new BTNode;
		bt->data = e;

		CreateBTree(bt->lchild);
		CreateBTree(bt->rchild);
	}
}

// 访问节点
void Vist(ElemeType e, int level)
{
	cout << e << " 在" << level << "层" << endl;
}

// 前序遍历二叉树
void PreOrderTraversal(BTNode* bt, int level)
{
	if (bt != NULL)
	{
		Vist(bt->data, level);
		PreOrderTraversal(bt->lchild, level + 1);
		PreOrderTraversal(bt->rchild, level + 1);
	}
}

// 中序遍历
void InOrderTraversal(BTNode* bt, int level)
{
	if (bt != NULL)
	{
		InOrderTraversal(bt->lchild, level + 1);
		Vist(bt->data, level);
		InOrderTraversal(bt->rchild, level + 1);
	}
}

// 后序遍历
void PostOrderTraversal(BTNode* bt, int level)
{
	if (bt != NULL)
	{
		PostOrderTraversal(bt->lchild, level + 1);
		PostOrderTraversal(bt->rchild, level + 1);
		Vist(bt->data, level);
	}
}

int main()
{
	BTNode* bt = NULL;

	cout << "按照前序遍历的方式创建二叉树，遇到叶子节点用空格代替" << endl;
	CreateBTree(bt);

	int level = 1;
	cout << "前序遍历" << endl;
	PreOrderTraversal(bt, level);

	cout << "中序遍历" << endl;
	InOrderTraversal(bt, level);

	cout << "后序遍历" << endl;
	PostOrderTraversal(bt, level);

	return 0;
}