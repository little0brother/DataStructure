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


// 初始化队列操作
void InitQueue(SqQueueLink*& sq)
{
	SqQueueNode* sqHead = new SqQueueNode;
	sqHead->btNode = new BiTreeNode;
	sqHead->btNode->lchild = NULL;
	sqHead->btNode->rchild = NULL;
	sqHead->next = NULL;
	sq->front = sq->rear = sqHead;
}

// 入队操作 根据weight进行入队 从小到大进行排序
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

// 取队头元素
void GetHeadQueue(SqQueueLink*& sq, BiTreeNode*& res)
{
	if (sq->front == sq->rear)
	{
		cout << "空队列" << endl;
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

// 构造二叉树
void CreateBiTree(BiTreeNode*& hufmTree, BiTreeNode* plchild, BiTreeNode* prchild)
{
	BiTreeNode* pNew = new BiTreeNode;
	pNew->data = '#';
	pNew->weight = plchild->weight + prchild->weight;
	pNew->lchild = plchild;
	pNew->rchild = prchild;

	hufmTree = pNew;
}

// 通过入队来进行哈夫曼树的构造
void CreateHuffmanTreeBySq(BiTreeNode*& hufmTree, SqQueueLink*& sq)
{
	hufmTree = new BiTreeNode;

	BiTreeNode* bRes = new BiTreeNode;
	bRes->lchild = NULL;
	bRes->rchild = NULL;

	while (sq->front != sq->rear)
	{
		// 判断队列中元素是否只剩一个
		if (sq->front->next != sq->rear)
		{
			// 取出队头两个元素
			GetHeadQueue(sq, bRes->lchild);
			GetHeadQueue(sq, bRes->rchild);
			// 将取出的队头两个最小元素 构造树
			CreateBiTree(hufmTree, bRes->lchild, bRes->rchild);

			// 创建临时变量 构造哈夫曼树
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

// 树形不对为右斜树  应当将创建好的树继续放入队列中 通过取队列的方式创建哈夫曼树
// 队列节点嵌套树节点 利用嵌套的树节点进行构建  节点值小的放左边 大的放右边
void CreateHuffmanTree(BiTreeNode*& hufmTree, SqQueueLink*& sq)
{
	hufmTree = new BiTreeNode;

	BiTreeNode* bRes = new BiTreeNode;
	bRes->lchild = NULL;
	bRes->rchild = NULL;

	// 取出队头两个元素
	GetHeadQueue(sq, bRes->lchild);
	GetHeadQueue(sq, bRes->rchild);
	// 将取出的队头两个最小元素 构造树
	CreateBiTree(hufmTree, bRes->lchild, bRes->rchild);

	while (sq->front != sq->rear)
	{
		SqQueueNode* sqTmp = sq->front->next;

		// 判断当前队列中是否剩余一个元素
		if (sqTmp != sq->rear)
		{
			// 如果哈夫曼树当前的根节点与队列中最小的节点的权值小于从队头取出的两元素权值，则将lchild加入hufmTree
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
			else	// 如果不满足条件 则利用两节点构建新二叉树 并将新二叉树添加值hufmTree
			{
				BiTreeNode* btNew = new BiTreeNode;

				// 构建树
				GetHeadQueue(sq, bRes->lchild);
				GetHeadQueue(sq, bRes->rchild);
				CreateBiTree(btNew, bRes->lchild, bRes->rchild);

				// 判断该将子树添加值左子树或右子树
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
		else	// 剩余一个元素时 直接将队列中的节点加入哈夫曼树中
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

// 前序遍历二叉树
void PreOrderTraversal(BiTreeNode* bt)
{
	if (bt != NULL)
	{
		vist(bt->data);
		PreOrderTraversal(bt->lchild);
		PreOrderTraversal(bt->rchild);
	}
}

// 利用前序遍历二叉树进行遍历  如果遇到叶子节点 或者 该节点已定义 则将该节点添加至 存储结构中
// int i: 用于记录生成密文后的下标
int CreateHuffmanCode(BiTreeNode* hufmTree, int i, EncTable(&encTable)[ACSII_LEN])
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
		CreateHuffmanCode(hufmTree->lchild, i + 1, encTable);
		code[i] = '1';
		CreateHuffmanCode(hufmTree->rchild, i + 1, encTable);
	}

	return deep;
}

// 将输入字符串 匹配密钥表中字符串并将压缩后的编码替换进去
void Encrypt(string str, EncTable enctable[], int deep/*密钥表大小*/, string& cryptograph)
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

// 解密函数 根据密钥表 对 密文进行匹配 匹配到一位 存储一位 直到全部解密完成
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
	int priority[ACSII_LEN] = { 0 };		// 确定优先级，记录ACSII所有字符出现的次数 

	// 记录str中每个字符出现的次数（将字符转为acsII进行记录）
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

	//cout << "中序遍历哈夫曼树:" << endl;
	//InOrderInverseBiTree(hufmTree);

	//cout << "\n前序遍历哈夫曼树:" << endl;
	//PreOrderTraversal(hufmTree);

	// 密钥表
	EncTable encTable[ACSII_LEN] = { 0 };

	// 加密算法有问题
	int len = 0;
	int deep = CreateHuffmanCode(hufmTree, len, encTable);

	cout << "密钥表:" << endl;
	for (int i = 0; i < deep; i++)
	{
		cout << encTable[i].ch << " " << encTable[i].table << endl;
	}

	// 对字符串进行加密
	string cryptograph;
	Encrypt(str, encTable, deep, cryptograph);

	cout << "\n密文:\n" << cryptograph << endl;

	string decodeStr;
	Decode(cryptograph, encTable, deep, decodeStr);
	cout << "\n\n解密:\n" << decodeStr << endl;

	return 0;
}