#include <iostream>
using namespace std;

struct Node
{
	int data;
	Node* next;
};

Node* CreateList()
{
	Node* head = new Node;
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

	/**************/
	// �л�����
	pCur->next = head->next;
	delete head;

	return pCur->next;

	/**************/
	// �޻�����
	//return head;
}

// ����һ�����ݵ�ĳһ�ڵ�Ĳ����ж������Ƿ��л�
int JudgeIsLoopByStep(Node* head)
{
	Node* pCur1 = head;
	int step1 = 0;


	while (pCur1)
	{
		Node* pCur2 = head;
		int step2 = 0;

		while (pCur2)
		{
			if (pCur1 == pCur2)
			{
				if (step1 == step2)
				{
					break;
				}
				else
				{
					cout << "�л� λ��Ϊ��" << step1 << endl;
					return 1;
				}
			}

			pCur2 = pCur2->next;
			step2++;
		}

		pCur1 = pCur1->next;
		step1++;
	}

	return 0;
}

// �����������ݿ���ָ���ж��Ƿ��л� ����ָ�����ʱ �����л���
int JudgeIsLoopByFast2SlowPointer(Node* head)
{
	Node* pFast = head;
	Node* pSlow = head;

	while (pFast->next != NULL && pSlow != NULL)
	{
		pFast = pFast->next->next;
		pSlow = pSlow->next;

		if (pFast == pSlow)
		{
			return 1;
		}
	}

	return 0;
}

void PrintList(Node* head)
{
	Node* pCur = head;

	do 
	{
		cout << pCur->data << "->";
		pCur = pCur->next;
	} while (pCur != head && pCur != NULL);
}

int main()
{
	Node* head = CreateList();
	PrintList(head);

	int flag = JudgeIsLoopByStep(head);
	if (flag == 1)
	{
		cout << "�л�" << endl;
	}
	else
	{
		cout << "�޻�" << endl;
	}

	int flag2 = JudgeIsLoopByFast2SlowPointer(head);
	if (flag2 == 1)
	{
		cout << "�л�" << endl;
	}
	else
	{
		cout << "�޻�" << endl;
	}

	return 0;
}