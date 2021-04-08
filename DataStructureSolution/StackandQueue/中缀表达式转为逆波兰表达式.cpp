/*
	中缀表达式： （1 - 2) * (4 + 5) = -9

	逆波兰表达式 或 后缀表达式： 1 2 - 4 5 + *

	此程序用来将中缀表达式转换为后缀表达式
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
	
	string str;
	char ch;

	cout << "输入中缀表达式，#结束：";
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
		// 当插入 + - 时 需要判断当前是否为空栈 如果是空栈则直接将元素入栈
		else if (str[i] == '+' || str[i] == '-')
		{
			// 如果栈内无数据 则将 + - 直接入栈
			if (!StackLen(sq))
			{
				StackPush(sq, str[i]);
			}
			// 如果不是空栈 则取出栈的当前元素判断是否是 '('  如果不是 则一定是 '*' 或 '/' 则将该符号从栈中取出 进行输出
			// 如果是 '(' 则代表一定有对应的另半边
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
				cout << "数据有误" << endl;
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