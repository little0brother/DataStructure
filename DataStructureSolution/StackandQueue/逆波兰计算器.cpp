/*
	中缀表达式： （1 - 2) * (4 + 5) = -9

	逆波兰表达式 或 后缀表达式： 1 2 - 4 5 + *  

	此程序用来计算逆波兰表达式
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
	int stackSize;		// 当前栈的最大容量
};

void InitStack(sqStack*& sq)
{
	sq->base = new ElemType[STACK_INIT_SIZE];

	if (sq->base == NULL)
	{
		cout << "未分配内存空间" << endl;
		return;
	}

	sq->top = sq->base;   // 空栈状态
	sq->stackSize = STACK_INIT_SIZE;
}

void StackPush(sqStack*& sq, ElemType e)
{
	if (sq->top - sq->base >= sq->stackSize)
	{
		sq->base = (ElemType*)realloc(sq->base, (sq->stackSize + STACKINCREAMENT) * sizeof(ElemType));
		if (!sq->base)
		{
			cout << "增加分配空间失败" << endl;
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

	cout << "请输入后缀表达式，以空格分隔数据与运算符:";
	std::cin >> noskipws >> ch;   // 设置cin 不跳过空格

	while (ch != '#')
	{
		while (isdigit(ch) || ch == '.')  // 过滤数字
		{
			str[i++] = ch;
			str[i] = '\0';

			if (i >= MAXBUFFER)
			{
				cout << "数据过大";
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
	cout << "结果为：" << num1 << endl;

	return 0;
}