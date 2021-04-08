#include <iostream>
using namespace std;

struct Node
{
	int data;

	Node* prior;	// ǰ��ָ��
	Node* next;		// ���ָ��
};

// ��������Ϊn��ѭ��˫������
Node* CreateList(int n)
{
	Node* head  = new Node;
	head->data  = 0;
	head->prior = head;
	head->next  = head;

	Node* pCur = head;

	for (int i = 0; i < n; i++)
	{
		Node* pNew  = new Node;
		pNew->data  = i + 1;
		pNew->prior = NULL;
		pNew->next  = NULL;

		pNew->prior = pCur;
		pCur->next  = pNew;

		pCur = pNew;
	}

	pCur->next = head->next;
	head->next->prior = pCur;
	delete head;

	return pCur->next;
}

// ����λ�ò���Ԫ��
int InsertNode(Node* head, int data, int loc)
{
	Node* pCur = head;

	Node* pNew = new Node;
	pNew->data = data;
	pNew->prior = NULL;
	pNew->next = NULL;

	for (int i = 1; i < loc; i++)
	{
		pCur = pCur->next;
	}

	pNew->next = pCur;
	pNew->prior = pCur->prior;
	pCur->prior->next = pNew;
	pCur->prior = pNew;

	return 0;
}

// ����λ��ɾ��Ԫ��
int DeleteNode(Node* head, int loc)
{
	Node* pCur = head;

	for (int i = 1; i < loc; i++)
	{
		pCur = pCur->next;
	}

	pCur->prior->next = pCur->next;
	pCur->next->prior = pCur->prior;
	delete pCur;

	return 0;
}

// �������
void OrderPrintList(Node* head)
{
	Node* pCur = head;

	do 
	{
		cout << pCur->data << "->";
		pCur = pCur->next;
	} while (pCur != head);
}

// �������
void ReversePrintList(Node* head)
{
	Node* pCur = head->prior;

	do
	{
		cout << pCur->data << "->";
		pCur = pCur->prior;
	} while (pCur != head->prior);
}

int main()
{
	int n = 10;

	Node* head = CreateList(n);

	OrderPrintList(head);
	cout << endl;
	ReversePrintList(head);

	cout << "\n����Ԫ�أ�" << endl;
	InsertNode(head, 32, 3);
	OrderPrintList(head);
	cout << endl;
	ReversePrintList(head);

	cout << "\nɾ��Ԫ�أ�" << endl;
	DeleteNode(head, 3);
	OrderPrintList(head);
	cout << endl;
	ReversePrintList(head);

	return 0;
}