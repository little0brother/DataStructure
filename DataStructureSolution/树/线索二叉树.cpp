#include <iostream>
using namespace std;

typedef char ElemeType;

typedef enum { Link = 0, Thread } PointerTag;

struct ThreadBiTNode
{
	ElemeType data;
	ThreadBiTNode* lchild;		// ָ��������
	ThreadBiTNode* rchild;		// ָ��������
	PointerTag ltag;			// ��ltag=0 ����lchildָ��������   ltag=1 ����lchildָ��ýڵ�ı���ǰ��
	PointerTag rtag;			// ��rtag=0 ����rchildָ��������   rtag=1 ����lchildָ��ýڵ�ı������
};

ThreadBiTNode* pPre = NULL;		// ָ��ǰ�ڵ��ǰһ�� ���ڶ�����������ϵ

// ʹ��ǰ������ķ�������������
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

		// ��ʼ����ǩΪ0
		bt->ltag = Link;
		bt->rtag = Link;

		CreateBiTree(bt->lchild);
		CreateBiTree(bt->rchild);
	}
}

// ������������� Ϊ�ڵ㴴����ϵ
void InOrderTraversalCreateThread(ThreadBiTNode*& bt)
{
	if (bt)
	{
		InOrderTraversalCreateThread(bt->lchild);

		// ���������Ϊ�� ��lchild�ڵ�ָ��ǰ��
		if (!bt->lchild)
		{
			bt->ltag = Thread;
			bt->lchild = pPre;
		}

		// �����һ���ڵ�������Ϊ�� ��rchild�ڵ�ָ����
		if (!pPre->rchild)
		{
			pPre->rtag = Thread;
			pPre->rchild = bt;
		}

		pPre = bt;

		InOrderTraversalCreateThread(bt->rchild);
	}
}

// ������������������� (��ʼ��pPreָ���ָ��)
void InOrderTraversal(ThreadBiTNode*& bt)
{
	// ����ͷ�ڵ�ָ�� ���������ڵ� ������������
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
		pPre->rchild = head;	// ���һ���ڵ�ĺ������ָ��head
		head->rchild = pPre;
	}
}

//ͨ�������ķ�ʽ�������������
void InOrderTraByItreat(ThreadBiTNode* bt)
{
	while (bt != pPre->rchild)
	{
		// Ѱ������ڵ�
		while (bt->ltag == Link)
		{
			bt = bt->lchild;
		}

		cout << bt->data << " ";

		// Ѱ��ǰ��
		while (bt->rtag == Thread && bt != pPre)
		{
			bt = bt->rchild;
			cout << bt->data << " ";
		}

		// ��ǰ�ڵ�û��ǰ����ָ��ǰ�ڵ��������  ��ֹ��ѭ��
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