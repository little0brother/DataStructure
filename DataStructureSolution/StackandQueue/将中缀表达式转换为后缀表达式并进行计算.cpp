/*
* 此程序 将中缀表达式 转换为 后缀表达式 并 利用后缀表达式进行计算
* 
* 	中缀表达式： （1 - 2) * (4 + 5) = -9

	逆波兰表达式 或 后缀表达式： 1 2 - 4 5 + *
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

// 重载为 double类型的  适用于ReversePolishCal()函数
void StackPush(sqStack*& sq, double e)
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

// 重载为 double类型的参数  适用于ReversePolishCal()函数
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

// 将中缀表达式转换为后缀表达式
string Infix2SuffixExperisson(sqStack*& sq, string str)
{
	char ch;
	string dst;

	for (int i = 0; i < str.length(); i++)
	{
		// 处理连续出现的数字 如果是连续数字 则不加空格进行分隔 eg 10  100  1
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
		// 当插入 + - 时 需要判断当前是否为空栈 如果是空栈则直接将元素入栈
		// 在此分支中 对运算符的优先级进行了判断
		else if (str[i] == '+' || str[i] == '-')
		{
			// 如果栈内无数据 则将 + - 直接入栈
			if (!StackLen(sq))
			{
				StackPush(sq, str[i]);
			}
			// 如果不是空栈 则取出栈的当前元素判断是否是 '('  如果不是 则一定是 '*' 或 '/' 则将该符号从栈中取出 进行输出(根据（*优先级进行取出)
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
				cout << "数据有误" << endl;
			}
		}
	}

	// 取出栈最后的运算符
	while (StackLen(sq))
	{
		StackPop(sq, ch);

		dst += ch;
		dst += " ";
	}

	return dst;
}

// 利用后缀表达式进行计算
double ReversePolishCal(sqStack*& sq, string suffix)
{
	char ch;
	int j = 0;
	char str[MAXBUFFER];
	double num1, num2;

	for(int i = 0; i < suffix.length() - 1; i++)
	{
		// 处理数字信息， 在字符串型 转换为 双精度
		while (isdigit(suffix[i]) || suffix[i] == '.')  // 过滤数字
		{
			str[j++] = suffix[i++];
			str[j] = '\0';

			if (j >= MAXBUFFER)
			{
				cout << "数据过大";
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

	// 栈顶存放数据为计算结果
	StackPop(sq, num1);

	return num1;
}

int main()
{
	sqStack* sq = new sqStack;
	InitStack(sq);

	string str;

	cout << "输入中缀表达式：";
	cin >> noskipws >> str;

	string SuffixExp = Infix2SuffixExperisson(sq, str);

	double res = ReversePolishCal(sq, SuffixExp);

	cout << "计算结果为:" << res << endl;

	return 0;
}