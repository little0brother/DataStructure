/*
	��׺���ʽ�� ��1 - 2) * (4 + 5) = -9

	�沨�����ʽ �� ��׺���ʽ�� 1 2 - 4 5 + *

	�˳�����������׺���ʽת��Ϊ��׺���ʽ
*/

#include <iostream>
using namespace std;

#include <ctype.h>
#include <stdlib.h>

typedef char ElemType;

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
	
	string str;
	char ch;

	cout << "������׺���ʽ��#������";
	cin >> noskipws >> str;

	for (int i = 0; i < str.length(); i++)
	{
		while (str[i] >= '0' && str[i] <= '9')
		{
			cout << str[i++];

			if (str[i] < '0' || str[i] > '9')
			{
				cout << " ";
			}
		}
		if (str[i] == ')')
		{
			StackPop(sq, ch);
			while (ch != '(')
			{
				cout << ch << " ";
				StackPop(sq, ch);
			}
		}
		// ������ + - ʱ ��Ҫ�жϵ�ǰ�Ƿ�Ϊ��ջ ����ǿ�ջ��ֱ�ӽ�Ԫ����ջ
		else if (str[i] == '+' || str[i] == '-')
		{
			// ���ջ�������� �� + - ֱ����ջ
			if (!StackLen(sq))
			{
				StackPush(sq, str[i]);
			}
			// ������ǿ�ջ ��ȡ��ջ�ĵ�ǰԪ���ж��Ƿ��� '('  ������� ��һ���� '*' �� '/' �򽫸÷��Ŵ�ջ��ȡ�� �������
			// ����� '(' �����һ���ж�Ӧ������
			else
			{
				do
				{
					StackPop(sq, ch);

					if (ch == '(')
					{
						StackPush(sq, ch);
					}
					else
					{
						cout << ch << " ";
					}
				} while (StackLen(sq) && ch != '(');

				StackPush(sq, str[i]);
			}
		}
		else if (str[i] == '*' || str[i] == '/' || str[i] == '(')
		{
			StackPush(sq, str[i]);
		}
		else if (str[i] == '#')
		{
			break;
		}
		else
		{
			if (i >= 14)
			{
				break;
			}
			else 
			{
				cout << "��������" << endl;
			}
		}
	}

	while (StackLen(sq))
	{
		StackPop(sq, ch);
		cout << ch << " ";
	}

	return 0;
}

// 1+(2-3)*4+10/5