#include <iostream>
using namespace std;

struct Node
{
	char data;		// ������
	Node* next;		// ָ����
};

// ��ʼ������
Node* InitLinkList()
{
	// ����ͷ�ڵ�
	Node* head = new Node;
	head->data = '0';
	head->next = NULL;

	return head;
}

// ��������(β�巨)
Node* CreateLinkLIst(Node* head)
{
	if (head == NULL)
	{
		return NULL;
	}

	Node* pCur = head;
	Node* pNew;

	while (true)
	{
		char ch;
		cin >> ch;

		if (ch == 's')
		{
			break;
		}

		// �����µĽڵ�
		pNew = new Node;

		// ���µĽڵ���и�ֵ����
		pNew->data = ch;
		pNew->next = NULL;

		// ���ӽڵ�
		pCur->next = pNew;

		// �ƶ���ǰ�ڵ�ָ��λ�� �����һ��Ԫ��
		pCur = pNew;
	}

	return head;
}

// ����������
int ListLength(Node* head)
{
	int len = 0;
	Node* pCur = head->next;

	while (pCur != NULL)
	{
		len++;
		pCur = pCur->next;
	}

	return len;
}

// ����Ԫ��ֵ��������Ԫ��
Node* SeekNodeByElement(Node* head, char ch)
{
	Node* pCur = head;
	Node* pRes = new Node;  // ��Ų��ҵ��Ľ��

	int i = 0;
	int len = ListLength(head);

	while (pCur != NULL && i <= len && pCur->data != ch)
	{
		i++;
		pCur = pCur->next;
	}

	// û���ҵ�Ԫ��ֵ ����NULL
	if (i > len)
	{
		return NULL;
	}

	pRes = pCur;
	cout << "place: " << i << endl;

	return pRes;
}

// ����λ�ò�������Ԫ��
Node* SeekNodeByLocation(Node* head, int location)
{
	// ��Ų�ѯ���
	Node* pRes = new Node;
	Node* pCur = head;
	Node* pTmp = pCur;

	int i = 0;

	while (pCur != NULL && i < location)
	{
		pTmp = pCur;
		pCur = pCur->next;
		i++;
	}

	// û�ҵ�
	if (i > location)
	{
		return NULL;
	}

	if (pCur == NULL)
	{
		return pTmp;
	}

	pRes = pCur;

	return pRes;
}

// �������в���ڵ�
int InsertNodeByLocation(Node* head, char ch, int location)
{
	if (head == NULL)
	{
		return -1;
	}

	Node* pCur = head;
	Node* pNext;
	Node* pNew = new Node;

	// ��ʼ���½ڵ�
	pNew->data = ch;
	pNew->next = NULL;

	// ���Ҳ���λ��
	pCur = SeekNodeByLocation(head, location);
	if (pCur == NULL)
	{
		pNext = NULL;
	}
	else
	{
		pNext = pCur->next;
	}

	// ���½ڵ���뵽������
	if (pCur != NULL)
	{
		pCur->next = pNew;
		pNew->next = pNext;
	}
	// û���ҵ��ڵ� ����ĩβ����
	else
	{
		while (pCur != NULL)
		{
			pCur = pCur->next;
		}
	}

	return 0;
}

// ɾ��ָ��λ�ýڵ�
int DeleteNodeByLocation(Node* head, int location)
{
	if (head == NULL)
	{
		cout << "[DeleteNodeByLocation] list empty" << endl;
		return -1;
	}

	Node* pPre = head;
	Node* pCur = pPre->next;
	Node* pNext = pCur->next;

	// ����ɾ��Ԫ�ص���һ��Ԫ��λ��
	pPre = SeekNodeByLocation(head, location - 1);
	if (pPre != NULL && pPre->next != NULL)
	{
		pCur = pPre->next;
		pNext = pCur->next;

		// ɾ��Ԫ��
		pPre->next = pNext;
		delete pCur;
	}
	else
	{
		cout << "[DeleteNodeByLocation] delete failed" << endl;;
		return -2;
	}

	return 0;
}

// ð������
int SortList(Node* head)
{
	if (head == NULL)
	{
		cout << "Empty" << endl;
		return -1;
	}

	Node* pCur = NULL;
	Node* pNext = NULL;
	Node* pTmp = new Node;

	int len = ListLength(head);

	for (pCur = head->next; pCur->next != NULL; pCur = pCur->next)
	{
		for (pNext = pCur->next; pNext->next != NULL; pNext = pNext->next)
		{
			if (pCur->data > pNext->data)
			{
				pTmp->data = pCur->data;
				pCur->data = pNext->data;
				pNext->data = pTmp->data;
			}
		}
	}

	return 0;
}

// ����ָ������м�Ԫ��
// ��ָ���ƶ��ٶ�Ϊ������ָ���ƶ��ٶ� ����ָ��ָ������ĩβ����ָ��ָ��λ��Ϊ�����м�Ԫ��
Node* F2SPionerSearchEle(Node* head)
{
	Node* pFast = head->next;
	Node* pSlow = head->next;
	Node* pRes = new Node;

	while (pFast->next != NULL)
	{
		if (pFast->next->next != NULL)
		{
			pFast = pFast->next->next;
			pSlow = pSlow->next;
		}
		else
		{
			pFast = pFast->next;
		}
	}

	pRes = pSlow;

	return pRes;
}

// ��������
int ListPrint(Node* head)
{
	if (head == NULL)
	{
		cout << "Empty" << endl;
		return -1;
	}

	Node* pCur = new Node;
	pCur = head->next;	// ����ͷ�ڵ�

	while (pCur != NULL)
	{
		cout << pCur->data << "->";

		pCur = pCur->next;
	}

	return 0;
}

// ɾ���������нڵ�
int ReleaseList(Node* head)
{
	Node* pCur = head;
	Node* pTmp = NULL;

	while (pCur)
	{
		// ��¼��һ���ڵ�
		pTmp = pCur->next;

		delete pCur;

		pCur = pTmp;
	}

	head->next = NULL;

	return 0;
}

int main()
{
	// ��ʼ������
	Node* head = InitLinkList();

	// ��ӽڵ�
	CreateLinkLIst(head);

	// ���������Ԫ��
	ListPrint(head);

	//������ 
	cout << "\nLinkList Length: " << ListLength(head) << endl;

	// ����Ԫ��ֵ����Ԫ��
	Node* seekNode = SeekNodeByElement(head, '2');
	if (seekNode != NULL)
	{
		cout << "seek node sucess\nresult: " << seekNode->data << endl;
	}
	else
	{
		cout << "seek location falied" << endl;
	}

	// ����λ�ò���Ԫ��
	Node* seekNode1 = SeekNodeByLocation(head, 3);
	if (seekNode1 != NULL)
	{
		cout << "seek node sucess\nresult: " << seekNode1->data << endl;
	}
	else
	{
		cout << "seek location falied" << endl;
	}

	// ����Ԫ��
	InsertNodeByLocation(head, '7', 1);
	ListPrint(head);
	cout << endl;

	// ɾ��Ԫ��
	DeleteNodeByLocation(head, 4);
	ListPrint(head);

	// ð������
	cout << "\nfinsh sort: ";
	SortList(head);
	ListPrint(head);

	// ���ÿ���ָ�� ���������м�Ԫ��
	Node* pMid = F2SPionerSearchEle(head);
	cout << "\nMid Element: " << pMid->data << endl;

	// �ͷ���������
	ReleaseList(head);
	ListPrint(head);

	return 0;
}