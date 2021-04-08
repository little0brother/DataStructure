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

class HufmTreeCode
{
private:
	SqQueueLink* sq;				// ���� ���ڴ洢�����ַ���
	ElemType e;						// ��ӵ�Ԫ��
	BiTreeNode* hufmTree;			// 
	BiTreeNode* res;				// �洢������ȡ���Ľڵ�
	int deep;						// ��Կ���С
	EncTable encTable[ACSII_LEN];   // ��Կ��
	string cryptograph;				// �洢���ܺ������
	string str;						// �洢���ܺ������

public:
	HufmTreeCode()
	{
		InitQueue();
	}

	void InitQueue();
	void AddSqQueue(int weight);
	void GetHeadQueue();
	void CreateBiTree(BiTreeNode* plchild, BiTreeNode* prchild);
	void CreateHuffmanTree();
	void vist();
	int  CreateHuffmanCode(int i);
	void Encrypt();
	void Decode();
};

void HufmTreeCode::InitQueue()
{
	SqQueueNode* sqHead = new SqQueueNode;
	sqHead->btNode = new BiTreeNode;

	sqHead->btNode->lchild = NULL;
	sqHead->btNode->rchild = NULL;
	sqHead->next = NULL;
	sq->front = sq->rear = sqHead;
}

void HufmTreeCode::AddSqQueue(int weight)
{
	SqQueueNode* sqNew = new SqQueueNode;
	sqNew->btNode = new BiTreeNode;
	sqNew->btNode->lchild = NULL;
	sqNew->btNode->rchild = NULL;

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
		while (sqCur != NULL && sqCur->next != NULL)
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

void HufmTreeCode::GetHeadQueue()
{
	if (sq->front == sq->rear)
	{
		cout << "�ն���" << endl;
		return;
	}

	SqQueueNode* sqCur = sq->front->next;
	res = new BiTreeNode;
	res->lchild = NULL;
	res->rchild = NULL;

	res->data = sqCur->btNode->data;
	res->weight = sqCur->btNode->weight;
	sq->front = sqCur;
}

void HufmTreeCode::CreateBiTree(BiTreeNode* plchild, BiTreeNode* prchild)
{
	BiTreeNode* pNew = new BiTreeNode;
	pNew->data = '#';
	pNew->weight = plchild->weight + prchild->weight;
	pNew->lchild = plchild;
	pNew->rchild = prchild;

	hufmTree = pNew;
}

// �����õ�����������Ӳ��� �ڴӶ�ͷȡ����Ԫ�ؽ���huffman���Ĺ���
void HufmTreeCode::CreateHuffmanTree()
{
	
}

int HufmTreeCode::CreateHuffmanCode(int i)
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
		CreateHuffmanCode(i + 1);
		code[i] = '1';
		CreateHuffmanCode(i + 1);
	}

	return deep;
}

void HufmTreeCode::Encrypt()
{
	char* cryptographTmp = new char[256];
	char* pC = cryptographTmp;

	for (int i = 0; i < str.length(); i++)
	{
		for (int j = 0; j < deep; j++)
		{
			if (str[i] == encTable[j].ch)
			{
				strcpy(cryptographTmp, encTable[j].table);
				cryptographTmp += strlen(encTable[j].table);
			}
		}
	}
	cryptographTmp[strlen(cryptographTmp)] = '\0';

	cryptographTmp = pC;
	cryptograph = cryptographTmp;
}

void HufmTreeCode::Decode()
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
			for (int j = 0; j < strlen(encTable[z].table); j++)
			{
				if (encTable[z].table[j] == crytmp[j])
				{
					flag++;
				}
			}

			if (flag == strlen(encTable[z].table))
			{
				decodeStr[deocelen++] = encTable[z].ch;
				crytmp += strlen(encTable[z].table);

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
	//HufmTreeCode* hufmTreeCode = new HufmTreeCode();
	//hufmTreeCode->AddSqQueue();


}