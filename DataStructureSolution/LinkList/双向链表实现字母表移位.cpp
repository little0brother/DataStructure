// ͨ��˫������ʵ����ĸ���˳��ĸı�
// ���������ƶ� ���������ƶ�

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
		cout << "ѭ������Ϊ�ձ�" << endl;
		return;
	}

	int n = 0;

	cout << "�������������ƶ������ĸ��";
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
	cout << "1.����˫��ѭ����ĸ����" << endl;
	cout << "2.���ѭ������" << endl;
	cout << "3.�����������ֽ�����λ����" << endl;
	cout << "0orOther.�˳�����" << endl;
	cout << "***************************" << endl;

	while (true)
	{
		cout << "�����Ӧ��Ž��в���: ";
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