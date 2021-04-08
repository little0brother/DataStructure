#include <iostream>
using namespace std;

// �ַ����ִ�����¼����󳤶�
#define ACSII_LEN 128

typedef  char ElemType;

// ������������
struct BiTreeNode
{
	ElemType data;
	int weight;
	BiTreeNode* lchild;
	BiTreeNode* rchild;
};

// ���нڵ�
struct SqQueueNode
{
	BiTreeNode* btNode;
	SqQueueNode* next;
};
// ���Ӷ���
struct SqQueueLink
{
	SqQueueNode* front;
	SqQueueNode* rear;
};

// ��Կ��ṹ
struct EncTable
{
	char ch;
	char table[256];
};


// ��ʼ�����в���
void InitQueue(SqQueueLink*& sq)
{
	SqQueueNode* sqHead = new SqQueueNode;
	sqHead->btNode = new BiTreeNode;
	sqHead->btNode->lchild = NULL;
	sqHead->btNode->rchild = NULL;
	sqHead->next = NULL;
	sq->front = sq->rear = sqHead;
}

// ��Ӳ��� ����weight������� ��С�����������
void AddSqQueue(SqQueueLink*& sq, BiTreeNode* bi,ElemType e, int weight)
{
	SqQueueNode* sqNew = new SqQueueNode;
	sqNew->btNode = new BiTreeNode;
	sqNew->btNode->lchild = NULL;
	sqNew->btNode->rchild = NULL;
	sqNew->btNode = bi;

	sqNew->btNode->data = e;
	sqNew->btNode->weight = weight;
	sqNew->next = NULL;

	SqQueueNode* sqCur = new SqQueueNode;
	sqCur->btNode = new BiTreeNode;
	sqCur = sq->front->next;

	// ����Ϊ��ʱ ֱ����ջ
	if (sq->front == sq->rear)
	{
		sq->rear->next = sqNew;
		sq->rear = sqNew;
	}	
	// ���Ȩ��С ���ڶ�ͷֱ�Ӽ���
	else if (sqNew->btNode->weight <= sqCur->btNode->weight)
	{
		sqNew->next = sqCur;
		sq->front->next = sqNew;
	}
	else
	{
		// ����ȨС-��Ѱ��λ�ý��в���
		while(sqCur != NULL && sqCur->next != NULL)
		{
			if (sqNew->btNode->weight <= sqCur->next->btNode->weight)
			{
				break;
			}

			sqCur = sqCur->next;
		}

		if (sqCur->next == NULL)
		{
			sqCur->next = sqNew;
			sqNew->next = NULL;
			sq->rear = sqNew;
		}
		else
		{
			sqNew->next = sqCur->next;
			sqCur->next = sqNew;
		}
	}
}

// ȡ��ͷԪ��
void GetHeadQueue(SqQueueLink*& sq, BiTreeNode*& res)
{
	if (sq->front == sq->rear)
	{
		cout << "�ն���" << endl;
		return;
	}

	SqQueueNode* sqCur = sq->front->next;
	res = new BiTreeNode;
	res->lchild = sqCur->btNode->lchild;
	res->rchild = sqCur->btNode->rchild;

	res->data = sqCur->btNode->data;
	res->weight = sqCur->btNode->weight;
	sq->front = sqCur;
}

// ���������
void CreateBiTree(BiTreeNode*& hufmTree, BiTreeNode* plchild, BiTreeNode* prchild)
{
	BiTreeNode* pNew = new BiTreeNode;
	pNew->data = '#';
	pNew->weight = plchild->weight + prchild->weight;
	pNew->lchild = plchild;
	pNew->rchild = prchild;

	hufmTree = pNew;
}

// ͨ����������й��������Ĺ���
void CreateHuffmanTreeBySq(BiTreeNode*& hufmTree, SqQueueLink*& sq)
{
	hufmTree = new BiTreeNode;

	BiTreeNode* bRes = new BiTreeNode;
	bRes->lchild = NULL;
	bRes->rchild = NULL;

	while (sq->front != sq->rear)
	{
		// �ж϶�����Ԫ���Ƿ�ֻʣһ��
		if (sq->front->next != sq->rear)
		{
			// ȡ����ͷ����Ԫ��
			GetHeadQueue(sq, bRes->lchild);
			GetHeadQueue(sq, bRes->rchild);
			// ��ȡ���Ķ�ͷ������СԪ�� ������
			CreateBiTree(hufmTree, bRes->lchild, bRes->rchild);

			// ������ʱ���� �����������
			SqQueueNode* sqTmp = new SqQueueNode;
			sqTmp->btNode = hufmTree;

			AddSqQueue(sq, sqTmp->btNode, sqTmp->btNode->data, sqTmp->btNode->weight);
		}
		else
		{
			GetHeadQueue(sq, bRes->lchild);

			hufmTree = bRes->lchild;
		}
	}
}

// ���β���Ϊ��б��  Ӧ���������õ���������������� ͨ��ȡ���еķ�ʽ������������
// ���нڵ�Ƕ�����ڵ� ����Ƕ�׵����ڵ���й���  �ڵ�ֵС�ķ���� ��ķ��ұ�
void CreateHuffmanTree(BiTreeNode*& hufmTree, SqQueueLink*& sq)
{
	hufmTree = new BiTreeNode;

	BiTreeNode* bRes = new BiTreeNode;
	bRes->lchild = NULL;
	bRes->rchild = NULL;

	// ȡ����ͷ����Ԫ��
	GetHeadQueue(sq, bRes->lchild);
	GetHeadQueue(sq, bRes->rchild);
	// ��ȡ���Ķ�ͷ������СԪ�� ������
	CreateBiTree(hufmTree, bRes->lchild, bRes->rchild);

	while (sq->front != sq->rear)
	{
		SqQueueNode* sqTmp = sq->front->next;

		// �жϵ�ǰ�������Ƿ�ʣ��һ��Ԫ��
		if (sqTmp != sq->rear)
		{
			// �������������ǰ�ĸ��ڵ����������С�Ľڵ��ȨֵС�ڴӶ�ͷȡ������Ԫ��Ȩֵ����lchild����hufmTree
			if ((hufmTree->weight + sqTmp->btNode->weight) < (sqTmp->btNode->weight + sqTmp->next->btNode->weight))
			{
				GetHeadQueue(sq, bRes->lchild);

				if (hufmTree->weight < bRes->lchild->weight)
				{
					CreateBiTree(hufmTree, hufmTree, bRes->lchild);
				}
				else
				{
					CreateBiTree(hufmTree, bRes->lchild, hufmTree);
				}
			}
			else	// ������������� ���������ڵ㹹���¶����� �����¶��������ֵhufmTree
			{
				BiTreeNode* btNew = new BiTreeNode;

				// ������
				GetHeadQueue(sq, bRes->lchild);
				GetHeadQueue(sq, bRes->rchild);
				CreateBiTree(btNew, bRes->lchild, bRes->rchild);

				// �жϸý��������ֵ��������������
				if (btNew->weight < hufmTree->weight)
				{
					CreateBiTree(hufmTree, btNew, hufmTree);
				}
				else
				{
					CreateBiTree(hufmTree, hufmTree, btNew);
				}
			}
		}
		else	// ʣ��һ��Ԫ��ʱ ֱ�ӽ������еĽڵ�������������
		{
			GetHeadQueue(sq, bRes->lchild);

			if (hufmTree->weight < bRes->lchild->weight)
			{
				CreateBiTree(hufmTree, hufmTree, bRes->lchild);
			}
			else
			{
				CreateBiTree(hufmTree, bRes->lchild, hufmTree);
			}
		}
	}
}

void vist(ElemType e)
{
	cout << e << ' ';
}

// ǰ�����������
void PreOrderTraversal(BiTreeNode* bt)
{
	if (bt != NULL)
	{
		vist(bt->data);
		PreOrderTraversal(bt->lchild);
		PreOrderTraversal(bt->rchild);
	}
}

// ����ǰ��������������б���  �������Ҷ�ӽڵ� ���� �ýڵ��Ѷ��� �򽫸ýڵ������ �洢�ṹ��
// int i: ���ڼ�¼�������ĺ���±�
int CreateHuffmanCode(BiTreeNode* hufmTree, int i, EncTable(&encTable)[ACSII_LEN])
{
	static char* code = new char[128];
	static int deep = 0;

	if (hufmTree != NULL)
	{
		// �����ǰ�ڵ������� ����ΪҶ�ӽڵ� �򽫱��� �� �ڵ����� ���� ��Կ����
		if ((hufmTree->data != '#' && hufmTree != NULL) || (hufmTree->lchild == NULL && hufmTree->rchild == NULL))
		{
			encTable[deep].ch = hufmTree->data;
			strcpy(encTable[deep].table, code);
			encTable[deep].table[i] = '\0';
			deep += 1;
		}

		code[i] = '0';
		CreateHuffmanCode(hufmTree->lchild, i + 1, encTable);
		code[i] = '1';
		CreateHuffmanCode(hufmTree->rchild, i + 1, encTable);
	}

	return deep;
}

// �������ַ��� ƥ����Կ�����ַ�������ѹ����ı����滻��ȥ
void Encrypt(string str, EncTable enctable[], int deep/*��Կ���С*/, string& cryptograph)
{
	char* cryptographTmp = new char[256];
	char* pC = cryptographTmp;

	for (int i = 0; i < str.length(); i++)
	{
		for (int j = 0; j < deep; j++)
		{
			if (str[i] == enctable[j].ch)
			{
				strcpy(cryptographTmp, enctable[j].table);
				cryptographTmp += strlen(enctable[j].table);
			}
		}
	}
	cryptographTmp[strlen(cryptographTmp)] = '\0';

	cryptographTmp = pC;
	cryptograph = cryptographTmp;
}

// ���ܺ��� ������Կ�� �� ���Ľ���ƥ�� ƥ�䵽һλ �洢һλ ֱ��ȫ���������
void Decode(string cryptograph, EncTable enctable[], int deep, string& str)
{
	char* decodeStr = new char[256];
	int deocelen = 0;

	char* crytmp = new char[cryptograph.length() + 1];
	strcpy(crytmp, cryptograph.c_str());

	int crytmplen = strlen(crytmp);
	for (int i = 0; i < crytmplen; i++)
	{
		for (int z = 0; z < deep; z++)
		{
			int flag = 0;
			for (int j = 0; j < strlen(enctable[z].table); j++)
			{
				if (enctable[z].table[j] == crytmp[j])
				{
					flag++;
				}
			}

			if (flag == strlen(enctable[z].table))
			{
				decodeStr[deocelen++] = enctable[z].ch;
				crytmp += strlen(enctable[z].table);

				crytmplen = strlen(crytmp);
				i = 0;
			}
		}
	}
	decodeStr[deocelen] = '\0';

	str = decodeStr;
}

int main()
{
	SqQueueLink* sq = new SqQueueLink;

	InitQueue(sq);

	ElemType e;
	int weight;

	string str = "This is a test string!!";
	int priority[ACSII_LEN] = { 0 };		// ȷ�����ȼ�����¼ACSII�����ַ����ֵĴ��� 

	// ��¼str��ÿ���ַ����ֵĴ��������ַ�תΪacsII���м�¼��
	for (int i = 0; i < str.length(); i++)
	{
		priority[(unsigned char)(str[i])]++;
	}

	for (int i = 0; i < ACSII_LEN; i++)
	{
		BiTreeNode* bi = new BiTreeNode;
		bi->lchild = NULL;
		bi->rchild = NULL;
		if (priority[i] != 0)
		{
			AddSqQueue(sq, bi, i, priority[i]);
		}
	}

	BiTreeNode* hufmTree = NULL;
	CreateHuffmanTreeBySq(hufmTree, sq);

	//cout << "���������������:" << endl;
	//InOrderInverseBiTree(hufmTree);

	//cout << "\nǰ�������������:" << endl;
	//PreOrderTraversal(hufmTree);

	// ��Կ��
	EncTable encTable[ACSII_LEN] = { 0 };

	// �����㷨������
	int len = 0;
	int deep = CreateHuffmanCode(hufmTree, len, encTable);

	cout << "��Կ��:" << endl;
	for (int i = 0; i < deep; i++)
	{
		cout << encTable[i].ch << " " << encTable[i].table << endl;
	}

	// ���ַ������м���
	string cryptograph;
	Encrypt(str, encTable, deep, cryptograph);

	cout << "\n����:\n" << cryptograph << endl;

	string decodeStr;
	Decode(cryptograph, encTable, deep, decodeStr);
	cout << "\n\n����:\n" << decodeStr << endl;

	return 0;
}