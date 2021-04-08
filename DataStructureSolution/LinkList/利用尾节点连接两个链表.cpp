#include <iostream>
using namespace std;

struct Node
{
	int data;
	Node* next;
};

Node* CreateA(Node* head)
{
	head->data = 0;
	head->next = NULL;

	Node* pCur = head;

	for (int i = 0; i < 10; i++)
	{
		Node* pNew = new Node;
		pNew->data = i + 1;
		pNew->next = NULL;

		pCur->next = pNew;
		pCur = pNew;
	}

	pCur->next = head;

	return pCur;
}

Node* CreateB()
{
	Node* head = new Node;
	head->data = 0;
	head->next = NULL;

	Node* pCur = head;

	for (int i = 10; i < 20; i++)
	{
		Node* pNew = new Node;
		pNew->data = i + 1;
		pNew->next = NULL;

		pCur->next = pNew;
		pCur = pNew;
	}

	pCur->next = head;

	return pCur;
}

Node* ConnectionA2B(Node*& tail1, Node*& tail2)
{
	Node* pTmp = tail1->next;

	tail1->next = tail2->next->next;

	delete tail2->next;

	tail2->next = pTmp;

	return pTmp;
}

void PrintList(Node* head)
{
	Node* pCur = head->next;

	do
	{
		cout << pCur->data << endl;

		pCur = pCur->next;
	} while (pCur != NULL && pCur != head);
}

int main()
{
	Node* head = new Node;
	Node* a = CreateA(head);
	Node* b = CreateB();

	ConnectionA2B(a, b);

	PrintList(head);

	return 0;
}