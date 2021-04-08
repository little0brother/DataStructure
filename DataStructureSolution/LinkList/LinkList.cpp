#include <iostream>
using namespace std;

struct Node
{
	char data;		// 数据域
	Node* next;		// 指针域
};

// 初始化链表
Node* InitLinkList()
{
	// 创建头节点
	Node* head = new Node;
	head->data = '0';
	head->next = NULL;

	return head;
}

// 创建链表(尾插法)
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

		// 申请新的节点
		pNew = new Node;

		// 对新的节点进行赋值操作
		pNew->data = ch;
		pNew->next = NULL;

		// 连接节点
		pCur->next = pNew;

		// 移动当前节点指针位置 至最后一个元素
		pCur = pNew;
	}

	return head;
}

// 计算链表长度
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

// 根据元素值查找链表元素
Node* SeekNodeByElement(Node* head, char ch)
{
	Node* pCur = head;
	Node* pRes = new Node;  // 存放查找到的结果

	int i = 0;
	int len = ListLength(head);

	while (pCur != NULL && i <= len && pCur->data != ch)
	{
		i++;
		pCur = pCur->next;
	}

	// 没有找到元素值 返回NULL
	if (i > len)
	{
		return NULL;
	}

	pRes = pCur;
	cout << "place: " << i << endl;

	return pRes;
}

// 根据位置查找链表元素
Node* SeekNodeByLocation(Node* head, int location)
{
	// 存放查询结果
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

	// 没找到
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

// 在链表中插入节点
int InsertNodeByLocation(Node* head, char ch, int location)
{
	if (head == NULL)
	{
		return -1;
	}

	Node* pCur = head;
	Node* pNext;
	Node* pNew = new Node;

	// 初始化新节点
	pNew->data = ch;
	pNew->next = NULL;

	// 查找插入位置
	pCur = SeekNodeByLocation(head, location);
	if (pCur == NULL)
	{
		pNext = NULL;
	}
	else
	{
		pNext = pCur->next;
	}

	// 将新节点插入到链表中
	if (pCur != NULL)
	{
		pCur->next = pNew;
		pNew->next = pNext;
	}
	// 没有找到节点 则在末尾插入
	else
	{
		while (pCur != NULL)
		{
			pCur = pCur->next;
		}
	}

	return 0;
}

// 删除指定位置节点
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

	// 查找删除元素的上一个元素位置
	pPre = SeekNodeByLocation(head, location - 1);
	if (pPre != NULL && pPre->next != NULL)
	{
		pCur = pPre->next;
		pNext = pCur->next;

		// 删除元素
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

// 冒泡排序
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

// 快慢指针查找中间元素
// 快指针移动速度为两倍慢指针移动速度 当快指针指向链表末尾，慢指针指向位置为链表中间元素
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

// 遍历链表
int ListPrint(Node* head)
{
	if (head == NULL)
	{
		cout << "Empty" << endl;
		return -1;
	}

	Node* pCur = new Node;
	pCur = head->next;	// 跳过头节点

	while (pCur != NULL)
	{
		cout << pCur->data << "->";

		pCur = pCur->next;
	}

	return 0;
}

// 删除链表所有节点
int ReleaseList(Node* head)
{
	Node* pCur = head;
	Node* pTmp = NULL;

	while (pCur)
	{
		// 记录下一个节点
		pTmp = pCur->next;

		delete pCur;

		pCur = pTmp;
	}

	head->next = NULL;

	return 0;
}

int main()
{
	// 初始化链表
	Node* head = InitLinkList();

	// 添加节点
	CreateLinkLIst(head);

	// 输出链表中元素
	ListPrint(head);

	//链表长度 
	cout << "\nLinkList Length: " << ListLength(head) << endl;

	// 根据元素值查找元素
	Node* seekNode = SeekNodeByElement(head, '2');
	if (seekNode != NULL)
	{
		cout << "seek node sucess\nresult: " << seekNode->data << endl;
	}
	else
	{
		cout << "seek location falied" << endl;
	}

	// 根据位置查找元素
	Node* seekNode1 = SeekNodeByLocation(head, 3);
	if (seekNode1 != NULL)
	{
		cout << "seek node sucess\nresult: " << seekNode1->data << endl;
	}
	else
	{
		cout << "seek location falied" << endl;
	}

	// 插入元素
	InsertNodeByLocation(head, '7', 1);
	ListPrint(head);
	cout << endl;

	// 删除元素
	DeleteNodeByLocation(head, 4);
	ListPrint(head);

	// 冒泡排序
	cout << "\nfinsh sort: ";
	SortList(head);
	ListPrint(head);

	// 利用快慢指针 查找链表中间元素
	Node* pMid = F2SPionerSearchEle(head);
	cout << "\nMid Element: " << pMid->data << endl;

	// 释放所有链表
	ReleaseList(head);
	ListPrint(head);

	return 0;
}