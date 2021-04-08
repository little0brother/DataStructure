// 通过改变队头队尾指针 实现循环队列
/*
* 队列长度：QueueLength = (rear - front + QueueSize) % QueueSize;
* 修改队尾指针：rear = (rear + 1) % QueueSize;
* 修改队头指针：front = (front + 1) % QueueSize;
* 判断队列是否满：（rear + 1) % QueueSize = front;
*/

#include <iostream>
using namespace std;

#define MAXSIZE 10

typedef int ElemeType;

struct SeQueue
{
	ElemeType data[MAXSIZE];
	int front;
	int rear;
};

void InitQueue(SeQueue*& sq)
{
	sq->front = sq->rear = 0;
}

bool IsEmpty(SeQueue* sq)
{
	if (sq->rear == sq->front)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void AddQueue(SeQueue*& sq, ElemeType e)
{
	if ((sq->rear + 1) & MAXSIZE == sq->front)
	{
		cout << "队列已满 无法入队" << endl;
		return;
	}

	sq->rear = (sq->rear + 1) % MAXSIZE;
	sq->data[sq->rear] = e;
}

void DelQueue(SeQueue*& sq, ElemeType& e)
{
	if (IsEmpty(sq))
	{
		cout << "队列空 无法出队" << endl;
		return;
	}

	sq->front = (sq->front + 1) % MAXSIZE;
	e = sq->data[sq->front];
}

void GetHeadQueue(SeQueue* sq, ElemeType& e)
{
	if (IsEmpty(sq))
	{
		cout << "队列空" << endl;
		return;
	}

	e = sq->data[(sq->front + 1) % MAXSIZE];
}

void ClearQueue(SeQueue*& sq)
{
	sq->front = sq->rear = 0;
}

int QueueLength(SeQueue* sq)
{
	return ((sq->rear - sq->front + MAXSIZE) % MAXSIZE);
}

int main()
{
	SeQueue* sq = new SeQueue;

	InitQueue(sq);

	cout << "入队" << endl;
	for (int i = 0; i < 15; i++)
	{
		AddQueue(sq, i + 1);
	}

	ElemeType e;
	GetHeadQueue(sq, e);
	cout << "\n队头：" << e << endl;

	cout << "\n队列长度：" << QueueLength(sq) << endl;

	cout << "\n出队" << endl;
	for (int i = 0; i < 15; i++)
	{
		DelQueue(sq, e);
		cout << e << "出队" << endl;
	} 

	return 0;
}