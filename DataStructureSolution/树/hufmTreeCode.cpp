#include <iostream>
using namespace std;

// 字符出现次数记录的最大长度
#define ACSII_LEN 128

typedef  char ElemType;

// 哈夫曼树构建
struct BiTreeNode
{
	ElemType data;
	int weight;
	BiTreeNode* lchild;
	BiTreeNode* rchild;
};

// 队列节点
struct SqQueueNode
{
	BiTreeNode* btNode;
	SqQueueNode* next;
};
// 连接队列
struct SqQueueLink
{
	SqQueueNode* front;
	SqQueueNode* rear;
};

// 密钥表结构
struct EncTable
{
	char ch;
	char table[256];
};

class HufmTreeCode
{
private:
	SqQueueLink* sq;				// 队列 用于存储输入字符串
	ElemType e;						// 入队的元素
	BiTreeNode* hufmTree;			// 
	BiTreeNode* res;				// 存储队列中取出的节点
	int deep;						// 密钥表大小
	EncTable encTable[ACSII_LEN];   // 密钥表
	string cryptograph;				// 存储加密后的密文
	string str;						// 存储解密后的明文

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

	// 队列为空时 直接入栈
	if (sq->front == sq->rear)
	{
		sq->rear->next = sqNew;
		sq->rear = sqNew;
	}
	// 如果权最小 则在队头直接加入
	else if (sqNew->btNode->weight <= sqCur->btNode->weight)
	{
		sqNew->next = sqCur;
		sq->front->next = sqNew;
	}
	else
	{
		// 按照权小-大寻找位置进行插入
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
		cout << "空队列" << endl;
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

// 构建好的子树利用入队操作 在从队头取出两元素进行huffman树的构造
void HufmTreeCode::CreateHuffmanTree()
{
	
}

int HufmTreeCode::CreateHuffmanCode(int i)
{
	static char* code = new char[128];
	static int deep = 0;

	if (hufmTree != NULL)
	{
		// 如果当前节点有数据 或者为叶子节点 则将编码 和 节点数据 存至 密钥表中
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