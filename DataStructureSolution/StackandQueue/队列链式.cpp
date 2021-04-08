#include <iostream>
using namespace std;

typedef char ElemeType;

// 队列节点
struct QNode
{
	ElemeType data;
	QNode* next;
};

// 存放队头 队尾指针
struct LinkQueue
{
	QNode* front;
	QNode* rear;
};

void InitQueue(LinkQueue*& lq)
{
	QNode* pHead = new QNode;
	pHead->next = NULL;

	lq->front = lq->rear = pHead;
	
	lq->front->next = NULL;
}

bool IsEmpty(LinkQueue* lq)
{
	if (lq->front == lq->rear)
	{
		return true;
	}
	else
	{
		return false;
	}
}

// 入队操作
void AddQueue(LinkQueue*& lq, ElemeType e)
{
	QNode* pNew = new QNode;
	pNew->next = NULL;
	pNew->data = e;

	lq->rear->next = pNew;
	lq->rear = pNew;
}

// 出队操作
ElemeType DelQueue(LinkQueue*& lq)
{
	if (IsEmpty(lq))
	{
		cout << "队列为空 无法删除" << endl;
		return -1;
	}

	QNode* pTmp;
	ElemeType e;

	pTmp = lq->front->next;
	e = pTmp->data;
	lq->front->next = pTmp->next;
	if (pTmp->next == NULL)
	{
		lq->rear = lq->front;
	}

	delete lq->front;
	lq->front = pTmp;

	return e;
}

ElemeType GetHeadQueue(LinkQueue* lq)
{
	if (IsEmpty(lq))
	{
		cout << "队列为空" << endl;
		return -1;
	}

	ElemeType e;
	e = lq->front->data;

	return e;
}

int main()
{
	LinkQueue* lq = new LinkQueue;
	InitQueue(lq);

	for (char i = '1'; i <= '9'; i++)
	{
		AddQueue(lq, i);
	}

	ElemeType x = GetHeadQueue(lq);
	cout << "队列头为:" << x << endl;

	cout << "\n出队：" << endl;
	for (char i = '1'; i <= '9'; i++)
	{
		ElemeType e = DelQueue(lq);
		cout << e << endl;
	}

	return 0;
}