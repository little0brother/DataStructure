/*
����������һ�� n �� n �ķ���
\���� n x n �ķ����ǡ�� n �ֲ�ͬ��Ԫ�أ�ÿһ�ֲ�ͬ��Ԫ����ͬһ�л�ͬһ����ֻ����һ�Ρ�

eg:
	1  2  3  4
	2  3  1  4
	3  4  1  2
	4  1  2  3

	���ɣ�������ѭ��������н��
	��һ��˳�����ѭ������
	�ڶ��дӵڶ�������Ԫ�ؽ���ѭ�����
	�����дӵ���������Ԫ��ѭ�����
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

// ����ѭ������
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

// ����ѭ�����������������
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

// ��������ֱ��������������
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

		//(δ���)
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

	cout << "�������� ����n*n��������";
	cin >> n;

	Node* head = CreatLoopList(n);
	//PrintList(head, n);

	PrintLatin(head, n);

	return 0;
}