/*
	��׺���ʽ�� ��1 - 2) * (4 + 5) = -9

	�沨�����ʽ �� ��׺���ʽ�� 1 2 - 4 5 + *  

	�˳������������沨�����ʽ
*/

#include <iostream>
#include <ctype.h>
#include <stdlib.h>
using namespace std;

typedef double ElemType;

#define STACK_INIT_SIZE 10
#define STACKINCREAMENT 5
#define MAXBUFFER		10

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

void StackPush(sqStack*& sq, ElemType e)
{
	if (sq->top - sq->base >= sq->stackSize)
	{
		sq->base = (ElemType*)realloc(sq->base, (sq->stackSize + STACKINCREAMENT) * sizeof(ElemType));
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

void StackPop(sqStack*& sq, ElemType& e)
{
	if (sq->top == sq->base)
	{
		return;
	}

	e = *--(sq->top);
}

int StackLen(sqStack* sq)
{
	return (sq->top - sq->base);
}

int main()
{
	sqStack* sq = new sqStack;
	InitStack(sq);

	char ch;
	char str[MAXBUFFER];
	int i = 0;
	double num1, num2;

	cout << "�������׺���ʽ���Կո�ָ������������:";
	std::cin >> noskipws >> ch;   // ����cin �������ո�

	while (ch != '#')
	{
		while (isdigit(ch) || ch == '.')  // ��������
		{
			str[i++] = ch;
			str[i] = '\0';

			if (i >= MAXBUFFER)
			{
				cout << "���ݹ���";
				return -1;
			}

			std::cin >> noskipws >> ch;

			if (ch == ' ')
			{
				num1 = atof(str);
				StackPush(sq, num1);
				i = 0;
				break;
			}
		}

		switch (ch)
		{
		case '+': 
			StackPop(sq, num1);
			StackPop(sq, num2);
			StackPush(sq, num1 + num2);
			break;

		case '-':
			StackPop(sq, num1);
			StackPop(sq, num2);
			StackPush(sq, num2 - num1);
			break;

		case '*':
			StackPop(sq, num1);
			StackPop(sq, num2);
			StackPush(sq, num2 * num1);
			break;

		case '/':
			StackPop(sq, num1);
			StackPop(sq, num2);
			if (num1 != 0)
			{
				StackPush(sq, num2 / num1);
			}
			else
			{
				cout << "error div = 0" << endl;
				return -1;
			}
			
			break;
		}

		std::cin >> noskipws >> ch;
	}

	StackPop(sq, num1);
	cout << "���Ϊ��" << num1 << endl;

	return 0;
}