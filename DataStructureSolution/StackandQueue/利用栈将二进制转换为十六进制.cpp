/* ������������ջ��ɴ˳��� */

#include <iostream> 
#include <math.h>
using namespace std;

#define STACK_INIT_SIZE 10
#define STACKINCREAMENT 5

typedef char ElemeType;

struct sqStack
{
	ElemeType* base;
	ElemeType* top;
	int stackSize;		// ��ǰջ���������
};

void CreateStack(sqStack*& sq)
{
	sq->base = new ElemeType[STACK_INIT_SIZE];
	if (!sq->base)
	{
		cout << "����ռ�ʧ��" << endl;
		return;
	}

	sq->top = sq->base;
	sq->stackSize = STACK_INIT_SIZE;
}

void StackPush(sqStack*& sq, ElemeType e)
{
	if (sq->top - sq->base >= sq->stackSize)
	{
		sq->base = (ElemeType*)realloc(sq->base, (sq->stackSize + STACKINCREAMENT) * sizeof(ElemeType));
		if (!sq->base)
		{
			cout << "���ӷ���ռ�ʧ��" << endl;
			return;
		}

		sq->stackSize += STACKINCREAMENT;
	}

	*sq->top = e;
	sq->top++;
}

int StackPop(sqStack*& sq, ElemeType& e)
{
	if (sq->top == sq->base)
	{
		cout << " ջ��" << endl;
		return 0;
	}

	e = *--(sq->top);
	return 1;
}

void PrintOct(sqStack* sq)
{
	for (int i = 0; i <= sq->top - sq->base; i++)
	{
		ElemeType e;
		StackPop(sq, e);

		cout << e;
	}
}

void Bin2Oct(sqStack*& sq)
{
	// ������ջ �����洢ת����Ľ��
	sqStack* sqOct = new sqStack;

	CreateStack(sqOct);

	// ȡ����Ŷ�����ջ��Ԫ�� ����ת��Ϊ8���ƵĽ��

	for (int j = 0; j < sq->top - sq->base; j++)
	{
		ElemeType octNum = 0;

		for (int i = 0; i < 4; i++)
		{
			ElemeType e;

			if (!StackPop(sq, e))
			{
				continue;
			}

			int binNum = abs(48 - e);

			octNum += binNum * pow(2, i);
		}

		octNum += 48;

		// �������10��ת��Ϊ��ĸ
		if (octNum > 57)
		{
			octNum += 7;
		}

		// ������õ�16����������ջ
		StackPush(sqOct, octNum);
	}


	cout << "ת������Ϊ:";
	PrintOct(sqOct);
}

int main()
{
	sqStack* sq = new sqStack;
	CreateStack(sq);

	string binStr;

	cout << "������һ����������: ";
	cin >> binStr;

	for (int i = 0; i < binStr.length(); i++)
	{
		StackPush(sq, binStr[i]);
	}

	Bin2Oct(sq);

	return 0;
}