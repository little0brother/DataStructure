#include <iostream>
using namespace std;

struct Node
{
	int data;
	Node* next;
};

// 创建循环链表
Node* CreateList(int n)
{
	Node* head = new Node;
	head->data = 0;
	head->next = NULL;

	Node* pCur = head;

	for (int i = 1; i <= n; i++)
	{
		Node* pNew = new Node;
		pNew->data = i;
		pNew->next = NULL;

		pCur->next = pNew;
		pCur = pNew;
	}

	pCur->next = head->next;
	delete head;

	return pCur->next;
}

/**********************************************/
// 利用约瑟夫环的算法进行节点销毁
void DeleteByJoseph2(Node* head, int n, int m)
{
	Node* pCur = head;
	Node* pTmp = NULL;

	int x = n % m;

	while (pCur != pCur->next)
	{
		for (int i = 1; i < x; i++)
		{
			pCur = pCur->next;
		}

		cout << pCur->next->data << "->";

		pTmp = pCur->next;
		pCur->next = pTmp->next;
		delete pTmp;

		pCur = pCur->next;
	}

}
/**********************************************/

// 利用约瑟夫环的算法进行节点销毁(垃圾方法)
void DeleteByJoseph(Node* head)
{
	Node* pCur = head;
	Node* pPre = head;
	Node* pTmp = head;

	while (pCur != pCur->next)
	{
		for (int i = 0; i < 2; i++)
		{
			pTmp = pTmp->next;
		}
		for (int i = 0; i < 1; i++)
		{
			pPre = pPre->next;
		}

		cout << pTmp->data << "->";

		pCur = pTmp->next;
		delete pTmp;
		pPre->next = pCur;
		pPre = pCur;

		pTmp = pCur;
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
	int n = 41;
	int m = 3;

	Node* head = CreateList(n);

	//DeleteByJoseph(head);
	DeleteByJoseph2(head, n, m);

	//PrintList(head);

	return 0;
}