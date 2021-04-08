// ����������(ʹ�õݹ�ķ���) �����(�ݹ�)ÿ���ַ����ڵĲ���

#include <iostream>
using namespace std;

typedef char ElemeType;

struct BTNode
{
	ElemeType data;		// ������
	BTNode* lchild;		// ������
	BTNode* rchild;		// ������
};

// ����ǰ������ķ�ʽ����������
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

// ���ʽڵ�
void Vist(ElemeType e, int level)
{
	cout << e << " ��" << level << "��" << endl;
}

// ǰ�����������
void PreOrderTraversal(BTNode* bt, int level)
{
	if (bt != NULL)
	{
		Vist(bt->data, level);
		PreOrderTraversal(bt->lchild, level + 1);
		PreOrderTraversal(bt->rchild, level + 1);
	}
}

// �������
void InOrderTraversal(BTNode* bt, int level)
{
	if (bt != NULL)
	{
		InOrderTraversal(bt->lchild, level + 1);
		Vist(bt->data, level);
		InOrderTraversal(bt->rchild, level + 1);
	}
}

// �������
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

	cout << "����ǰ������ķ�ʽ����������������Ҷ�ӽڵ��ÿո����" << endl;
	CreateBTree(bt);

	int level = 1;
	cout << "ǰ�����" << endl;
	PreOrderTraversal(bt, level);

	cout << "�������" << endl;
	InOrderTraversal(bt, level);

	cout << "�������" << endl;
	PostOrderTraversal(bt, level);

	return 0;
}