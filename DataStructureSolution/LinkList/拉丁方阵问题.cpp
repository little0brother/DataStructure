/*
拉丁方阵是一种 n × n 的方阵，
\这种 n x n 的方阵里，恰有 n 种不同的元素，每一种不同的元素在同一行或同一列里只出现一次。

eg:
	1  2  3  4
	2  3  1  4
	3  4  1  2
	4  1  2  3

	规律：可以用循环链表进行解决
	第一行顺序输出循环链表
	第二行从第二个链表元素进行循环输出
	第四行从第三个链表元素循环输出
	........
*/

#include <iostream>
#include <math.h>
using namespace std;

struct Node
{
	int data;
	Node* next;
};

// 生成循环链表
Node* CreatLoopList(int n)
{
	Node* head = new Node;
	head->data = 0;
	head->next = NULL;

	Node* pCur = head;

	for (int i = 0; i < n; i++)
	{
		Node* pNew = new Node;
		pNew->data = i + 1;
		pNew->next = NULL;

		pCur->next = pNew;
		pCur = pNew;
	}

	pCur->next = head->next;
	delete head;

	return pCur->next;
}

// 根据循环链表输出拉丁矩阵
void PrintLatin(Node* head, int n)
{
	Node* pCur = head;

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << pCur->data << "\t";
			pCur = pCur->next;
		}
		cout << endl << endl;
		pCur = pCur->next;
	}
}

// 利用链表直接生成拉丁矩阵
Node* CreateLatin(int n)
{
	Node* head = new Node;
	head->data = 0;
	head->next = NULL;

	Node* pCur = head;

	for (int i = 0; i < n * n; i++)
	{
		Node* pNew = new Node;
		pNew->data = 0;
		pNew->next = NULL;

		//(未完成)
	}

	return 0;
}

void PrintList(Node* head, int n)
{
	Node* pCur = head;

	do
	{
		cout << pCur->data << "\t";
		pCur = pCur->next;
	} while (pCur != head);
}

int main()
{
	int n = 0;

	cout << "输入数字 生成n*n拉丁方阵：";
	cin >> n;

	Node* head = CreatLoopList(n);
	//PrintList(head, n);

	PrintLatin(head, n);

	return 0;
}