
/***************************************************
*�������ƣ�ħ��ʦ��������
*����������ħ��ʦ����һ����13���ƣ�ȫ�Ǻ��ң�1~13.
*********ħ��ʦ��Ҫʵ��һ��ħ��������ʮ������ȫ�����������ϣ��������£���
********��һ��������һ�ţ���1�����������������ϡ�
******�ڶ������������������ڶ��ţ���2�������� ���������ϣ�����һ�ŷ���������ȥ���Ȼ����������
*****�������������������������ţ���3�����������������ϣ�����һ�ź͵ڶ��� ����������ȥ���Ȼ��������
***  �Դ����� ���һ�ž���13
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

// ���㷢��˳��
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

			// ��λ�������ƺ� ������
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

	cout << "\n�����\n" << endl;

	Magician(head);
	PrintList(head);

	return 0;
}