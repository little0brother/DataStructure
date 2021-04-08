/*
* �˳��� ����׺���ʽ ת��Ϊ ��׺���ʽ �� ���ú�׺���ʽ���м���
* 
* 	��׺���ʽ�� ��1 - 2) * (4 + 5) = -9

	�沨�����ʽ �� ��׺���ʽ�� 1 2 - 4 5 + *
*/
#define _CRT_SECURE_NO_WARNINGS

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

// ����Ϊ double���͵�  ������ReversePolishCal()����
void StackPush(sqStack*& sq, double e)
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

// ����Ϊ double���͵Ĳ���  ������ReversePolishCal()����
void StackPop(sqStack*& sq, double& e)
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

// ����׺���ʽת��Ϊ��׺���ʽ
string Infix2SuffixExperisson(sqStack*& sq, string str)
{
	char ch;
	string dst;

	for (int i = 0; i < str.length(); i++)
	{
		// �����������ֵ����� ������������� �򲻼ӿո���зָ� eg 10  100  1
		while (str[i] >= '0' && str[i] <= '9')
		{
			dst += str[i++];

			if (str[i] < '0' || str[i] > '9')
			{
				dst += " ";
			}
		}
		if (str[i] == ')')
		{
			StackPop(sq, ch);
			while (ch != '(')
			{
				dst += ch;
				dst += " ";

				StackPop(sq, ch);
			}
		}
		// ������ + - ʱ ��Ҫ�жϵ�ǰ�Ƿ�Ϊ��ջ ����ǿ�ջ��ֱ�ӽ�Ԫ����ջ
		// �ڴ˷�֧�� ������������ȼ��������ж�
		else if (str[i] == '+' || str[i] == '-')
		{
			// ���ջ�������� �� + - ֱ����ջ
			if (!StackLen(sq))
			{
				StackPush(sq, str[i]);
			}
			// ������ǿ�ջ ��ȡ��ջ�ĵ�ǰԪ���ж��Ƿ��� '('  ������� ��һ���� '*' �� '/' �򽫸÷��Ŵ�ջ��ȡ�� �������(���ݣ�*���ȼ�����ȡ��)
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
						dst += ch;
						dst += " ";
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
			if (i >= str.length())
			{
				break;
			}
			else
			{
				cout << "��������" << endl;
			}
		}
	}

	// ȡ��ջ���������
	while (StackLen(sq))
	{
		StackPop(sq, ch);

		dst += ch;
		dst += " ";
	}

	return dst;
}

// ���ú�׺���ʽ���м���
double ReversePolishCal(sqStack*& sq, string suffix)
{
	char ch;
	int j = 0;
	char str[MAXBUFFER];
	double num1, num2;

	for(int i = 0; i < suffix.length() - 1; i++)
	{
		// ����������Ϣ�� ���ַ����� ת��Ϊ ˫����
		while (isdigit(suffix[i]) || suffix[i] == '.')  // ��������
		{
			str[j++] = suffix[i++];
			str[j] = '\0';

			if (j >= MAXBUFFER)
			{
				cout << "���ݹ���";
				return -1;
			}

			if (suffix[i] == ' ')
			{
				num1 = atof(str);
				StackPush(sq, num1);
				j = 0;
				break;
			}
		}

		switch (suffix[i])
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
	}

	// ջ���������Ϊ������
	StackPop(sq, num1);

	return num1;
}

int main()
{
	sqStack* sq = new sqStack;
	InitStack(sq);

	string str;

	cout << "������׺���ʽ��";
	cin >> noskipws >> str;

	string SuffixExp = Infix2SuffixExperisson(sq, str);

	double res = ReversePolishCal(sq, SuffixExp);

	cout << "������Ϊ:" << res << endl;

	return 0;
}