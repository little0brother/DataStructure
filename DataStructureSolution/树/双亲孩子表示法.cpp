/*
* ˫�׺��ӱ�ʾ��
*	�������������
*/

#define MAX_INIT_TREE 10

typedef char ElemeType;

// ���ӽڵ�
struct CTNode
{
	int child;		 // ��ź��ӽڵ�������±�
	CTNode* next;	 // ָ����һ�����ӽڵ�
};

// ��ͷ�ṹ
struct CTBox
{
	ElemeType e;		// ������нڵ������
	int parent;			// ���˫�׵��±�

	CTNode* firstChild;	// ָ���һ�����ӽڵ��ָ��
};

// ���ṹ
struct Tree
{
	CTBox tree[MAX_INIT_TREE];		// ��ͷ�ڵ�����
	int r;							// ������λ��
	int n;							// �ڵ����
};