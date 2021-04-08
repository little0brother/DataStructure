
/***************************************************
*问题名称：魔术师发牌问题
*问题描述：魔术师手里一共有13张牌，全是黑桃，1~13.
*********魔术师需要实现一个魔术：这是十三张牌全部放在桌面上（正面向下），
********第一次摸出第一张，是1，翻过来放在桌面上。
******第二次摸出从上往下数第二张，是2，翻过来 放在桌面上，（第一张放在最下面去，等会儿再摸），
*****第三次摸出从上往下数第三张，是3，翻过来放在桌面上，（第一张和第二张 放在最下面去，等会儿再摸）
***  以此类推 最后一张就是13
*******************************************************/

#include <iostream>
using namespace std;

struct Node
{
	int data;
	Node* next;
};

Node* CreateLoopList()
{
	Node* head = new Node;
	head->data = 0;
	head->next = NULL;

	Node* pCur = head;

	for (int i = 0; i < 12; i++)
	{
		Node* pNew = new Node;
		pNew->data = 0;
		pNew->next = NULL;

		pCur->next = pNew;
		pCur = pNew;
	}

	pCur->next = head->next;
	delete head;

	return pCur->next;
}

// 计算发牌顺序
void Magician(Node* head)
{
	Node* pCur = head;
	pCur->data = 1;

	int countNumber = 2;

	while (true)
	{
		for (int i = 0; i < countNumber; i++)
		{
			pCur = pCur->next;

			// 该位置已有牌号 则跳过
			if (pCur->data != 0)
			{
				i--;
			}
		}

		if (pCur->data == 0)
		{
			pCur->data = countNumber;
			countNumber++;

			if (countNumber == 13)
			{
				break;
			}
		}

	}
}

void PrintList(Node* head)
{
	Node* pCur = head;

	do
	{
		cout << pCur->data << "->";
		pCur = pCur->next;
	} while (pCur != head);
}

int main()
{
	Node* head = CreateLoopList();
	PrintList(head);

	cout << "\n排序后\n" << endl;

	Magician(head);
	PrintList(head);

	return 0;
}