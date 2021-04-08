#include <iostream>
using namespace std;

typedef  char ElemType;

// 队列节点
struct SqQueueNode
{
	ElemType data;
	int weight;
	SqQueueNode* next;
};
// 连接队列
struct SqQueueLink
{
	SqQueueNode* front;
	SqQueueNode* rear;
};

// 哈夫曼树构建
struct BiTreeNode
{
	SqQueueNode* sqnode;
	BiTreeNode* lchild;
	BiTreeNode* rchild;
};

// 初始化队列操作
void InitQueue(SqQueueLink*& sq)
{
	SqQueueNode* sqHead = new SqQueueNode;
	sqHead->next = NULL;
	sq->front = sq->rear = sqHead;
}

// 入队操作
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

// 二叉树节点嵌套队列节点不可行
// 改用队列节点嵌套二叉树节点，当构建哈夫曼树时，将队列节点取出断开next指针连接，构建哈夫曼树，将构建完成的哈夫曼树按照大小放入队列继续机型构建
void CreateHuffmanCode(SqQueueLink*& sq)
{
	// 取出两个最小节点 进行子树的创建
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

	cout << "正在创建字符频率表 格式为:data weight (# #结束创建) 按照字符使用频率由小到大输入" << endl;
	cin >> e >> weight;
	while (e != '#')
	{
		AddSqQueue(sq, e, weight);
		cin >> e >> weight;
	}

	return 0;
}