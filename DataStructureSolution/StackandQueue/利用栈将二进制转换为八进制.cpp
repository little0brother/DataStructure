/* 可以利用两个栈完成此程序 */

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
	int stackSize;		// 当前栈的最大容量
};

void CreateStack(sqStack*& sq)
{
	sq->base = new ElemeType[STACK_INIT_SIZE];
	if (!sq->base)
	{
		cout << "分配空间失败" << endl;
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
			cout << "增加分配空间失败" << endl;
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
		cout << " 栈空" << endl;
		return 0;
	}

	e = *--(sq->top);
	return 1;
}

void PrintOct(sqStack* sq)
{
	// 取出8进制栈中的数据
	for (int i = 0; i <= sq->top - sq->base; i++)
	{
		ElemeType e;
		StackPop(sq, e);

		cout << e;
	}
}

void Bin2Oct(sqStack*& sq)
{
	// 创建新栈 用来存储转换后的结果
	sqStack* sqOct = new sqStack;

	CreateStack(sqOct);

	// 取出存放二进制栈的元素 计算转换为8进制的结果
	
	for (int j = 0; j < sq->top - sq->base; j++)
	{
		ElemeType octNum = 0;

		for (int i = 0; i < 3; i++)
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
		// 将计算好的8进制数 入栈
		StackPush(sqOct, octNum);
	}


	cout << "转换后结果为:";
	PrintOct(sqOct);
}

int main()
{
	sqStack* sq = new sqStack;
	CreateStack(sq);

	string binStr;

	cout << "请输入一串二进制数: ";
	cin >> binStr;

	for (int i = 0; i < binStr.length(); i++)
	{
		StackPush(sq, binStr[i]);
	}

	Bin2Oct(sq);

	return 0;
}