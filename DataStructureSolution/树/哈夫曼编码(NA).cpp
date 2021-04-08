#include <iostream>
using namespace std;

typedef  char ElemType;

// ���нڵ�
struct SqQueueNode
{
	ElemType data;
	int weight;
	SqQueueNode* next;
};
// ���Ӷ���
struct SqQueueLink
{
	SqQueueNode* front;
	SqQueueNode* rear;
};

// ������������
struct BiTreeNode
{
	SqQueueNode* sqnode;
	BiTreeNode* lchild;
	BiTreeNode* rchild;
};

// ��ʼ�����в���
void InitQueue(SqQueueLink*& sq)
{
	SqQueueNode* sqHead = new SqQueueNode;
	sqHead->next = NULL;
	sq->front = sq->rear = sqHead;
}

// ��Ӳ���
void AddSqQueue(SqQueueLink*& sq, ElemType e, int weight)
{
	SqQueueNode* sqNew = new SqQueueNode;
	sqNew->data = e;
	sqNew->weight = weight;
	sqNew->next = NULL;

	sq->rear->next = sqNew;
	sq->rear = sqNew;
}

void GetHeadQueue(SqQueueLink*& sq, SqQueueNode*& res)
{
	SqQueueNode* sqCur = sq->front->next;

	res->data = sqCur->data;
	res->weight = sqCur->weight;
	sq->front = sqCur;
}

// �������ڵ�Ƕ�׶��нڵ㲻����
// ���ö��нڵ�Ƕ�׶������ڵ㣬��������������ʱ�������нڵ�ȡ���Ͽ�nextָ�����ӣ�����������������������ɵĹ����������մ�С������м������͹���
void CreateHuffmanCode(SqQueueLink*& sq)
{
	// ȡ��������С�ڵ� ���������Ĵ���
	SqQueueNode* head1;
	SqQueueNode* head2;
	GetHeadQueue(sq, head1);
	GetHeadQueue(sq, head2);

	BiTreeNode* btNew = new BiTreeNode;
	btNew->sqnode = head1;
	btNew->lchild = NULL;
	btNew->rchild = NULL;

	BiTreeNode* btNew2 = new BiTreeNode;
	btNew2->sqnode = head2;
	btNew2->lchild = NULL;
	btNew2->rchild = NULL;

	BiTreeNode* btNew3 = new BiTreeNode;
	btNew3->sqnode->data = ' ';
	btNew3->sqnode->weight = btNew->sqnode->weight + btNew2->sqnode->weight;
	btNew3->lchild = btNew;
	btNew3->rchild = btNew2;

	AddSqQueue(sq, );
}

int main()
{
	SqQueueLink* sq = new SqQueueLink;

	InitQueue(sq);

	ElemType e;
	int weight;

	cout << "���ڴ����ַ�Ƶ�ʱ� ��ʽΪ:data weight (# #��������) �����ַ�ʹ��Ƶ����С��������" << endl;
	cin >> e >> weight;
	while (e != '#')
	{
		AddSqQueue(sq, e, weight);
		cin >> e >> weight;
	}

	return 0;
}