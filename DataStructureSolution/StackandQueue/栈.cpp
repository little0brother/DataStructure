// ��ջ ��ջʱ �����ݴ���
// ��ջ�ռ䲻��ʱ �����µ��ڴ�ռ� ��������ת�Ƴ����������

#include <iostream>
using namespace std;

typedef int ElemType;

#define STACK_INIT_SIZE 10
#define STACKINCREAMENT 5

struct sqStack
{
	ElemType* base;
	ElemType* top;
	int stackSize;		// ��ǰջ���������
};

void InitStack(sqStack*& sq)
{
	sq->base = new ElemType[STACK_INIT_SIZE];
	
	if (sq->base == NULL)
	{
		cout << "δ�����ڴ�ռ�" << endl;
		return;
	}

	sq->top = sq->base;   // ��ջ״̬
	sq->stackSize = STACK_INIT_SIZE;
}

void Push(sqStack*& sq, ElemType x)
{
	ElemType* pTmp = sq->base;
	ElemType* pBase = NULL;

	// �ж�ջ�ռ��Ƿ����� ���������׷�ӿռ�
	if (sq->top - sq->base >= sq->stackSize)
	{
		ElemType* pNew = new ElemType[sq->stackSize + STACKINCREAMENT];
		pBase = pNew;
		if (pNew == NULL)
		{
			cout << "Push error" << endl;
			return;
		}

		// ��ԭ���ռ������ȫ�����Ƶ��¿ռ���
		while (pTmp <= sq->top)
		{
			*pBase++ = *pTmp++;
		}
		// �ͷžɿռ�
		delete[sq->stackSize] sq->base;

		// �ı䵱ǰ��ջ����ջ��ָ��
		sq->base = pNew;
		sq->top = pBase;
		sq->stackSize += STACKINCREAMENT;
	}

	// ��ջ
	*(sq->top) = x;
	sq->top++;
}

ElemType Pop(sqStack*& sq)
{
	if (sq->top == sq->base)
	{
		cout << "ջ��" << endl;
		return 0;
	}

	ElemType ele = *--(sq->top);

	return ele;
}

// �ж�ջ�Ƿ�Ϊ��
int StackEmpty(sqStack* sq)
{
	if (sq->top != sq->base)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

// �ÿ�ջ
void ClearStack(sqStack*& sq)
{
	sq->top = sq->base;
}

void DestoryStack(sqStack*& sq)
{
	int len = sq->stackSize;

	for (int i = 0; i < len; i++)
	{
		delete(sq->base);
		sq->base++;
	}

	sq->base = sq->top = NULL;
	sq->stackSize = 0;
}

// ��ȡջ��Ԫ��
ElemType GetTopEle(sqStack* sq)
{
	if (sq->top == sq->base)
	{
		cout << "kongzhan" << endl;
		return -1;
	}

	return *(sq->top);
}

int main()
{
	sqStack* sq = new sqStack;
	InitStack(sq);

	for (int i = 0; i < 10; i++)
	{
		Push(sq, i + 1);
	}

	for (int i = 0; i < 10; i++)
	{
		ElemType x = Pop(sq);
		cout << x << "��ջ" << endl;
	}

	int flag = StackEmpty(sq);
	if (flag == 1)
	{
		cout << "��Ϊ��" << endl;
	}
	else
	{
		cout << "��" << endl;
	}

	//DestoryStack(sq);

	return 0;
}