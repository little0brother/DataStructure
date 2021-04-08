// 出栈 入栈时 有数据错误
// 当栈空间不足时 申请新的内存空间 进行数据转移出现输出错误

#include <iostream>
using namespace std;

typedef int ElemType;

#define STACK_INIT_SIZE 10
#define STACKINCREAMENT 5

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

void Push(sqStack*& sq, ElemType x)
{
	ElemType* pTmp = sq->base;
	ElemType* pBase = NULL;

	// 判断栈空间是否已满 如果已满则追加空间
	if (sq->top - sq->base >= sq->stackSize)
	{
		ElemType* pNew = new ElemType[sq->stackSize + STACKINCREAMENT];
		pBase = pNew;
		if (pNew == NULL)
		{
			cout << "Push error" << endl;
			return;
		}

		// 将原来空间的内容全部复制到新空间中
		while (pTmp <= sq->top)
		{
			*pBase++ = *pTmp++;
		}
		// 释放旧空间
		delete[sq->stackSize] sq->base;

		// 改变当前的栈顶和栈底指针
		sq->base = pNew;
		sq->top = pBase;
		sq->stackSize += STACKINCREAMENT;
	}

	// 入栈
	*(sq->top) = x;
	sq->top++;
}

ElemType Pop(sqStack*& sq)
{
	if (sq->top == sq->base)
	{
		cout << "栈空" << endl;
		return 0;
	}

	ElemType ele = *--(sq->top);

	return ele;
}

// 判断栈是否为空
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

// 置空栈
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

// 读取栈顶元素
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
		cout << x << "出栈" << endl;
	}

	int flag = StackEmpty(sq);
	if (flag == 1)
	{
		cout << "不为空" << endl;
	}
	else
	{
		cout << "空" << endl;
	}

	//DestoryStack(sq);

	return 0;
}