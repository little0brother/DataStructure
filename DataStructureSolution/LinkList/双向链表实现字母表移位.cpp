// 通过双向链表实现字母表的顺序的改变
// 正数正向移动 负数负向移动

#include <iostream>
using namespace std;

struct Node
{
	char data;
	Node* prior;
	Node* next;
};

Node* CreateLoopList()
{
	Node* head = new Node;
	head->data = 0;
	head->prior = NULL;
	head->next = NULL;

	Node* pCur = head;

	for (char ch = 'A'; ch <= 'Z'; ch++)
	{
		Node* pNew = new Node;
		pNew->data = ch;
		pNew->next = NULL;
		pNew->prior = NULL;

		pCur->next = pNew;
		pNew->prior = pCur;

		pCur = pNew;
	}

	head->next->prior = pCur;
	pCur->next = head->next;
	delete head;

	return pCur->next;
}

void PrintLoopList(Node* head)
{
	Node* pCur = head;

	do
	{
		cout << pCur->data << "->";
		pCur = pCur->next;
	} while (pCur != head);

	cout << endl;
}

void GressionByNumber(Node*& head)
{
	if (head == NULL)
	{
		cout << "循环链表为空表" << endl;
		return;
	}

	int n = 0;

	cout << "输入正数或负数移动输出字母表：";
	cin >> n;

	Node* pCur = head;

	if (n >= 0)
	{
		for (int i = 0; i < n; i++)
		{
			pCur = pCur->next;
		}

		PrintLoopList(pCur);
	}
	else if (n < 0)
	{
		for (int i = 0; i < abs(n); i++)
		{
			pCur = pCur->prior;
		}

		PrintLoopList(pCur);
	}
}

void CmdLine()
{
	int input = 0;

	Node* head = NULL;

	cout << "***************************" << endl;
	cout << "1.创建双向循环字母链表" << endl;
	cout << "2.输出循环链表" << endl;
	cout << "3.根据输入数字进行移位操作" << endl;
	cout << "0orOther.退出程序" << endl;
	cout << "***************************" << endl;

	while (true)
	{
		cout << "输入对应序号进行操作: ";
		cin >> input;

		switch (input)
		{
		case 1: head = CreateLoopList();   break;
		case 2: PrintLoopList(head);	   break;
		case 3: GressionByNumber(head);    break;
		case 0:
			default: exit(0);
		}
	}
}

int main()
{
	CmdLine();

	return 0;
}