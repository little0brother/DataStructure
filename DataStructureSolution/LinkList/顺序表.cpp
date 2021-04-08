#define _CRT_SECURE_NO_WARNINGS
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<iostream>
#define MaxSize 100
#define ElemType int
#define Status int
using namespace std;

//˳������ݽṹ
typedef struct
{
	ElemType data[MaxSize];//˳���Ԫ��
	int length;            //˳���ǰ����
}SqList;
//***************************������������*******************************//
//��ʼ��˳�����������һ���յ�˳��� 
Status InitList(SqList& L)
{
	memset(L.data, 0, sizeof(L));//��ʼ������Ϊ0
	L.length = 0;                //��ʼ������Ϊ0
	return 0;
}
//����˳����� ��ʼ��ǰn������
bool CreateList(SqList& L, int n)
{
	if (n<0 || n>MaxSize)false;//n�Ƿ�
	for (int i = 0; i < n; i++)
	{
		scanf("%d", &L.data[i]);
		L.length++;
	}
	return true;
}
//���뺯�� λ��i�������� i��֮��Ԫ�غ���  1=<i<=length+1 
bool InsertList(SqList& L, int i, ElemType e)
{
	if (i<1 || i>L.length + 1) //�ж�λ���Ƿ���Ч
	{
		printf("λ����Ч������\n");
		return false;
	}
	if (L.length >= MaxSize)//�жϴ洢�ռ��Ƿ�����
	{
		printf("��ǰ�洢�ռ�����������\n");
		return false;
	}
	for (int j = L.length; j >= i; j--)//λ��i��֮��Ԫ�غ���
	{
		L.data[j] = L.data[j - 1];
	}
	L.data[i - 1] = e;
	L.length++;
	return true;
}
//ɾ������ ɾ��λ��i��Ԫ�� i֮���Ԫ������ǰ��
bool  ListDelete(SqList& L, int i)
{
	if (i<1 || i>L.length)
	{
		printf("λ����Ч������\n");
		return false;
	}
	for (int j = i; j <= L.length - 1; j++)//λ��i֮��Ԫ������ǰ�Ƹ���
	{
		L.data[j - 1] = L.data[j];
	}
	L.length--;
	return true;
}
//���Һ��� ��λ�ô�С������ҵ�һ��ֵ����e��Ԫ�� ������λ��
int LocateElem(SqList L, ElemType e)
{
	for (int i = 0; i < L.length; i++)//�ӵ�λ�ò���
	{
		if (L.data[i] == e)
			return i + 1;
	}
	return 0;
}
//���ú��� ��ԭ˳���ֱ�ӵ���
void Reverse(SqList& L)
{
	if (L.length)
		for (int i = 0; i < L.length - 1 - i; i++)
		{
			int t = L.data[i];
			L.data[i] = L.data[L.length - 1 - i];
			L.data[L.length - 1 - i] = t;
		}
}
//��ż�ֿ�������
void SplitSort(SqList& L)
{
	int Even = 0;
	int Odd = L.length - 1;
	int i = 0;
	int j = L.length - 1;
	bool flag = false;
	if (L.length)
		for (; i < j; i++, j--)
		{
			while (L.data[i] % 2 != 0)i++;
			while (L.data[j] % 2 == 0)j--;
			if (L.data[i] % 2 == 0 && L.data[j] % 2 != 0 && i < j)
			{
				int temp = L.data[i];
				L.data[i] = L.data[j];
				L.data[j] = temp;
				flag = true;
			}
			if (!flag) //û�н���
			{
				Even = L.length - 1;//ȫ����
				Odd = 0; //ȫż��
			}
		}
	if (flag)
	{
		for (int i = 0; i < L.length; i++)
			if (L.data[i] % 2 == 0)
			{
				Odd = i;
				Even = i - 1;
				break;
			}
	}
	sort(L.data, L.data + Even + 1);
	sort(L.data + Odd, L.data + L.length);
}
//���˳���
void ClearList(SqList& L) {
	L.length = 0;
}
//********************************���ܺ���*****************************************//
//������ܺ��� ��λ�ô�С�������˳�������Ԫ��
void PrintList(SqList L)
{
	printf("��ǰ˳�������Ԫ��:");
	for (int i = 0; i < L.length; i++)
	{
		printf("%d ", L.data[i]);
	}
	printf("\n");
}
//����˳�����
void Create(SqList& L)
{
	int n; bool flag;
	L.length = 0;
	printf("������Ҫ������˳�����(>1):");
	scanf("%d", &n);
	printf("������%d�������ո������:", n);
	flag = CreateList(L, n);
	if (flag) {
		printf("�����ɹ���\n");
		PrintList(L);
	}
	else printf("���볤�ȷǷ���\n");

}
//���빦�ܺ��� ����InsertList���˳���Ԫ�ز��� ����PrintList������ʾ����ɹ���Ľ��
void Insert(SqList& L)
{
	int place; ElemType e; bool flag;
	printf("������Ҫ�����λ��(��1��ʼ)��Ԫ��:\n");
	scanf("%d%d", &place, &e);
	flag = InsertList(L, place, e);
	if (flag)
	{
		printf("����ɹ�������\n");
		PrintList(L);
	}
}
//ɾ�����ܺ��� ����ListDelete�������˳����ɾ�� ����PrintList������ʾ����ɹ���Ľ��
void Delete(SqList& L)
{
	int place; bool flag;
	printf("������Ҫɾ����λ��(��1��ʼ):\n");
	scanf("%d", &place);
	flag = ListDelete(L, place);
	if (flag)
	{
		printf("ɾ���ɹ�������\n");
		PrintList(L);
	}
}
//���ҹ��ܺ��� ����LocateElem����Ԫ��
void Search(SqList L)
{
	ElemType e; int flag;
	printf("������Ҫ���ҵ�ֵ:\n");
	scanf("%d", &e);
	flag = LocateElem(L, e);
	if (flag)
	{
		printf("��Ԫ��λ��Ϊ:%d\n", flag);
	}
	else
		printf("δ�ҵ���Ԫ�أ�\n");
}
//�˵�
void menu()
{
	printf("********1.����                        2.����*********\n");
	printf("********3.ɾ��                        4.����*********\n");
	printf("********5.����                        6.����ż����***\n");
	printf("********7.���                        8.���*********\n");
	printf("********9.�˳�                              *********\n");
}
int main()
{
	SqList L; int choice;
	InitList(L);
	while (1)
	{
		menu();
		printf("������˵���ţ�\n");
		scanf("%d", &choice);
		if (9 == choice) break;
		switch (choice)
		{
		case 1:Create(L); break;
		case 2:Insert(L); break;
		case 3:Delete(L); break;
		case 4:Search(L); break;
		case 5:Reverse(L); break;
		case 6:SplitSort(L); break;
		case 7:PrintList(L); break;
		case 8:ClearList(L); break;
		default:printf("������󣡣���\n");
		}
	}

	return 0;
}


#if 0

#include <iostream>
using namespace std;

#define LIST_INIT_SIZE	 100	// ���Ա�洢�ռ�ĳ�ʼ������
#define LIST_INCREMENT	 10	// ���Ա�洢�ռ�ķ���������

#define ElemType int

typedef struct {
    ElemType* elem;		// ���Ա�洢�ռ����ַ
    int		length;		// ���Ա�ǰ����
    int		listsize;	// ��ǰ����Ĵ洢��������ElemTypeΪ��λ��
} SqList;

void Error(string s) {
    // ������Ϣ�����������ڴ����쳣���
    cout << s << endl;
    exit(1);
} // Error

void InitList_Sq(SqList& L) {
    // ����һ���������ΪLIST_INIT_SIZE��˳���L
    L.elem = new ElemType[LIST_INIT_SIZE];

    if (!L.elem)  
        Error(" Overflow!");		// �洢����ʧ��

    L.length = 0;    
    L.listsize = LIST_INIT_SIZE;

    for (int i = 0; i < LIST_INIT_SIZE; i++)
    {
        *(L.elem) = i + 1;
        L.length++;
    }
} // InitList_Sq

void DestroyList_Sq(SqList& L) {
    // �ͷ�˳���L��Ԫ����ռ�õĴ洢�ռ�
    delete[]L.elem;
    L.length = 0;
    L.listsize = 0;
} // DestroyList_Sq

void ClearList_Sq(SqList& L) {
    // ����˳���LΪ�ձ�
    L.length = 0;
} // ClearList_Sq 

int ListLength_Sq(SqList L) {
    // ����˳���L�ĳ���
    return L.length;
} // ListLength_Sq

void GetElem_Sq(SqList L, int i, ElemType& e) {
    // ��e����˳���L�е�i��Ԫ��ֵ��1��i��L.length��
    // �������������������Ӧ��Ϣ���˳�����
    if ((i < 1) || (i > L.length))			// ȡԪ��ֵ�Ĳ���������
        Error(" Position Error!");
    e = L.elem[i - 1];
} // GetElem_Sq

int LocateElem_Sq(SqList L, ElemType e) {
    // ���Ҳ�����˳���L�е�1����e��ȵ�����Ԫ�ص�λ����δ�ҵ��򷵻�0
    int i = 1;			// ָʾλ�򣬳�ֵΪ1
    ElemType* p = L.elem;			// ָ��L��i��Ԫ�أ���ʼָ���׸�Ԫ��

    while ((i <= L.length) && (*p++ != e))  
        i++;

    if (i <= L.length)  
        return i;
    else  
        return 0;
} // LocateElem_Sq

void ListInsert_Sq(SqList& L, int i, ElemType e) {
    // ��˳���L�е�i��λ��ǰ����Ԫ��e��������λ�ò������������Ӧ��Ϣ���˳�����
    // i�ĺ���ֵΪ1��i��L.length+1
    if ((i < 1) || (i > L.length + 1))		// ����Ԫ�صĲ���������
        Error(" Position Error!");

    if (L.length >= LIST_INIT_SIZE)	// ����ǰ�洢�ռ������������ӿռ�
    {
        //Increment(L);
        Error("Insert Failed");
    }

    ElemType* q = &(L.elem[i - 1]);			// ��ָ��qָ�����λ��
    ElemType* p = NULL;

    for (p = &(L.elem[L.length - 1]); p >= q; --p)
        *(p + 1) = *p;			// ���κ���Ԫ��

    *q = e;				// ��L�ĵ�i��λ���в���e
    ++L.length;			// ����L�ĳ��ȣ�������1
} // ListInsert_Sq

void ListDelete_Sq(SqList& L, int i, ElemType& e) {
    // ɾ��˳���L�е�i��Ԫ�ز���e������ֵ��������λ�ò������������Ϣ���˳�����
    // i�ĺ���ֵΪ1��i��L.length
    if ((i < 1) || (i > L.length))		// ɾ��Ԫ�صĲ���������
        Error(" Position Error!");
    e = L.elem[i - 1];			// ����ɾ��Ԫ�ص�ֵ����e
    ElemType* p = &(L.elem[i - 1]);			// ָ��L�д�ɾ��Ԫ�ص�λ��
    ElemType* q = L.elem + L.length - 1;	   	// ָ��L�����һ��Ԫ�ص�λ��

    for (++p; p <= q; ++p)
        *(p - 1) = *p; 			// ����ǰ��Ԫ��

    --L.length;			// ����L�ĳ��ȣ������1
} // ListDelete_Sq

void TraverseList_Sq(SqList L) {
    // �������˳���L�е�ÿ������Ԫ��
    if (L.length != 0) {
        int i = 1;				// ָʾλ�򣬳�ֵΪ1
        ElemType* p = L.elem;			// ָ��L��i��Ԫ�أ���ʼָ����Ԫ��

        // �������L�е�Ԫ��
        while (i <= L.length) 
        {		
            cout << *p++ << " ";
            i++;
        }
    }
} // TraverseList_Sq

int main()
{
    SqList head;

    InitList_Sq(head);

    TraverseList_Sq(head);

    return 0;
}
#endif