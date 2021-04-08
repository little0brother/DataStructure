// ͨ���ı��ͷ��βָ�� ʵ��ѭ������
/*
* ���г��ȣ�QueueLength = (rear - front + QueueSize) % QueueSize;
* �޸Ķ�βָ�룺rear = (rear + 1) % QueueSize;
* �޸Ķ�ͷָ�룺front = (front + 1) % QueueSize;
* �ж϶����Ƿ�������rear + 1) % QueueSize = front;
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
		cout << "�������� �޷����" << endl;
		return;
	}

	sq->rear = (sq->rear + 1) % MAXSIZE;
	sq->data[sq->rear] = e;
}

void DelQueue(SeQueue*& sq, ElemeType& e)
{
	if (IsEmpty(sq))
	{
		cout << "���п� �޷�����" << endl;
		return;
	}

	sq->front = (sq->front + 1) % MAXSIZE;
	e = sq->data[sq->front];
}

void GetHeadQueue(SeQueue* sq, ElemeType& e)
{
	if (IsEmpty(sq))
	{
		cout << "���п�" << endl;
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

	cout << "���" << endl;
	for (int i = 0; i < 15; i++)
	{
		AddQueue(sq, i + 1);
	}

	ElemeType e;
	GetHeadQueue(sq, e);
	cout << "\n��ͷ��" << e << endl;

	cout << "\n���г��ȣ�" << QueueLength(sq) << endl;

	cout << "\n����" << endl;
	for (int i = 0; i < 15; i++)
	{
		DelQueue(sq, e);
		cout << e << "����" << endl;
	} 

	return 0;
}