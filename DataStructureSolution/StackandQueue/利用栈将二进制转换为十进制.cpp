#include <iostream>
#include <string>
#include <math.h>
using namespace std;

#define STACK_INIT_SIZE 10
#define STACKINCREAMENT 5

typedef char ElemeType;

struct sqStack
{
	ElemeType* base;
	ElemeType* top;
	int stackSize;
};

void InitStack(sqStack*& sq)
{
	sq->base = new ElemeType[STACK_INIT_SIZE];

	if (!sq->base)
	{
		cout << "Init Failed" << endl;
		return;
	}

	sq->top = sq->base;

	sq->stackSize = STACK_INIT_SIZE;
}

void PushStack(sqStack*& sq, ElemeType e)
{
	if (sq->top - sq->base >= sq->stackSize)
	{
		sq->base = (ElemeType*)realloc(sq->base, (sq->stackSize + STACKINCREAMENT) * sizeof(ElemeType));

		if (!sq->base)
		{
			cout << "分配空间失败" << endl;
			return;
		}

		sq->stackSize += STACKINCREAMENT;
	}

	*(sq->top++) = e;
}

void PopStack(sqStack*& sq, ElemeType& e)
{
	if (sq->base == sq->top)
	{
		cout << "空栈" << endl;
		return;
	}

	e = *--(sq->top);
}

int StackLen(sqStack sq)
{
	return (sq.top - sq.base);
}

int Bin2Dec(sqStack*& sq)
{
	int sum = 0;
	ElemeType e;
	int len = StackLen(*sq);

	for (int i = 0; i < len; i++)
	{
		PopStack(sq, e);
		int num = abs(48 - e);

		sum += num * pow(2, i);
	}

	return sum;
}

int main()
{
	sqStack* sq = new sqStack;
	
	InitStack(sq);

	string str;
	cout << "请输入一串二进制数:";
	cin >> str;

	for (int i = 0; i < str.length(); i++)
	{
		PushStack(sq, str[i]);
	}

	int sum = Bin2Dec(sq);

	cout << str << ":转为10进制为:" << sum << endl;

	return 0;
}