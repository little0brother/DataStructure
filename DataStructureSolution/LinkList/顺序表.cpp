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

//顺序表数据结构
typedef struct
{
	ElemType data[MaxSize];//顺序表元素
	int length;            //顺序表当前长度
}SqList;
//***************************基本操作函数*******************************//
//初始化顺序表函数，构造一个空的顺序表 
Status InitList(SqList& L)
{
	memset(L.data, 0, sizeof(L));//初始化数据为0
	L.length = 0;                //初始化长度为0
	return 0;
}
//创建顺序表函数 初始化前n个数据
bool CreateList(SqList& L, int n)
{
	if (n<0 || n>MaxSize)false;//n非法
	for (int i = 0; i < n; i++)
	{
		scanf("%d", &L.data[i]);
		L.length++;
	}
	return true;
}
//插入函数 位置i插入数据 i及之后元素后移  1=<i<=length+1 
bool InsertList(SqList& L, int i, ElemType e)
{
	if (i<1 || i>L.length + 1) //判断位置是否有效
	{
		printf("位置无效！！！\n");
		return false;
	}
	if (L.length >= MaxSize)//判断存储空间是否已满
	{
		printf("当前存储空间已满！！！\n");
		return false;
	}
	for (int j = L.length; j >= i; j--)//位置i及之后元素后移
	{
		L.data[j] = L.data[j - 1];
	}
	L.data[i - 1] = e;
	L.length++;
	return true;
}
//删除函数 删除位置i的元素 i之后的元素依次前移
bool  ListDelete(SqList& L, int i)
{
	if (i<1 || i>L.length)
	{
		printf("位置无效！！！\n");
		return false;
	}
	for (int j = i; j <= L.length - 1; j++)//位置i之后元素依次前移覆盖
	{
		L.data[j - 1] = L.data[j];
	}
	L.length--;
	return true;
}
//查找函数 按位置从小到大查找第一个值等于e的元素 并返回位置
int LocateElem(SqList L, ElemType e)
{
	for (int i = 0; i < L.length; i++)//从低位置查找
	{
		if (L.data[i] == e)
			return i + 1;
	}
	return 0;
}
//倒置函数 将原顺序表直接倒置
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
//奇偶分开并排序
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
			if (!flag) //没有交换
			{
				Even = L.length - 1;//全奇数
				Odd = 0; //全偶数
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
//清空顺序表
void ClearList(SqList& L) {
	L.length = 0;
}
//********************************功能函数*****************************************//
//输出功能函数 按位置从小到大输出顺序表所有元素
void PrintList(SqList L)
{
	printf("当前顺序表所有元素:");
	for (int i = 0; i < L.length; i++)
	{
		printf("%d ", L.data[i]);
	}
	printf("\n");
}
//创建顺序表函数
void Create(SqList& L)
{
	int n; bool flag;
	L.length = 0;
	printf("请输入要创建的顺序表长度(>1):");
	scanf("%d", &n);
	printf("请输入%d个数（空格隔开）:", n);
	flag = CreateList(L, n);
	if (flag) {
		printf("创建成功！\n");
		PrintList(L);
	}
	else printf("输入长度非法！\n");

}
//插入功能函数 调用InsertList完成顺序表元素插入 调用PrintList函数显示插入成功后的结果
void Insert(SqList& L)
{
	int place; ElemType e; bool flag;
	printf("请输入要插入的位置(从1开始)及元素:\n");
	scanf("%d%d", &place, &e);
	flag = InsertList(L, place, e);
	if (flag)
	{
		printf("插入成功！！！\n");
		PrintList(L);
	}
}
//删除功能函数 调用ListDelete函数完成顺序表的删除 调用PrintList函数显示插入成功后的结果
void Delete(SqList& L)
{
	int place; bool flag;
	printf("请输入要删除的位置(从1开始):\n");
	scanf("%d", &place);
	flag = ListDelete(L, place);
	if (flag)
	{
		printf("删除成功！！！\n");
		PrintList(L);
	}
}
//查找功能函数 调用LocateElem查找元素
void Search(SqList L)
{
	ElemType e; int flag;
	printf("请输入要查找的值:\n");
	scanf("%d", &e);
	flag = LocateElem(L, e);
	if (flag)
	{
		printf("该元素位置为:%d\n", flag);
	}
	else
		printf("未找到该元素！\n");
}
//菜单
void menu()
{
	printf("********1.创建                        2.插入*********\n");
	printf("********3.删除                        4.查找*********\n");
	printf("********5.倒置                        6.分奇偶排序***\n");
	printf("********7.输出                        8.清空*********\n");
	printf("********9.退出                              *********\n");
}
int main()
{
	SqList L; int choice;
	InitList(L);
	while (1)
	{
		menu();
		printf("请输入菜单序号：\n");
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
		default:printf("输入错误！！！\n");
		}
	}

	return 0;
}


#if 0

#include <iostream>
using namespace std;

#define LIST_INIT_SIZE	 100	// 线性表存储空间的初始分配量
#define LIST_INCREMENT	 10	// 线性表存储空间的分配增补量

#define ElemType int

typedef struct {
    ElemType* elem;		// 线性表存储空间基地址
    int		length;		// 线性表当前长度
    int		listsize;	// 当前分配的存储容量（以ElemType为单位）
} SqList;

void Error(string s) {
    // 出错信息处理函数，用于处理异常情况
    cout << s << endl;
    exit(1);
} // Error

void InitList_Sq(SqList& L) {
    // 构造一个最大容量为LIST_INIT_SIZE的顺序表L
    L.elem = new ElemType[LIST_INIT_SIZE];

    if (!L.elem)  
        Error(" Overflow!");		// 存储分配失败

    L.length = 0;    
    L.listsize = LIST_INIT_SIZE;

    for (int i = 0; i < LIST_INIT_SIZE; i++)
    {
        *(L.elem) = i + 1;
        L.length++;
    }
} // InitList_Sq

void DestroyList_Sq(SqList& L) {
    // 释放顺序表L中元素所占用的存储空间
    delete[]L.elem;
    L.length = 0;
    L.listsize = 0;
} // DestroyList_Sq

void ClearList_Sq(SqList& L) {
    // 重置顺序表L为空表
    L.length = 0;
} // ClearList_Sq 

int ListLength_Sq(SqList L) {
    // 返回顺序表L的长度
    return L.length;
} // ListLength_Sq

void GetElem_Sq(SqList L, int i, ElemType& e) {
    // 用e返回顺序表L中第i个元素值（1≤i≤L.length）
    // 若参数不合理则给出相应信息并退出运行
    if ((i < 1) || (i > L.length))			// 取元素值的参数不合理
        Error(" Position Error!");
    e = L.elem[i - 1];
} // GetElem_Sq

int LocateElem_Sq(SqList L, ElemType e) {
    // 查找并返回顺序表L中第1个与e相等的数据元素的位序；若未找到则返回0
    int i = 1;			// 指示位序，初值为1
    ElemType* p = L.elem;			// 指向L第i个元素，初始指向首个元素

    while ((i <= L.length) && (*p++ != e))  
        i++;

    if (i <= L.length)  
        return i;
    else  
        return 0;
} // LocateElem_Sq

void ListInsert_Sq(SqList& L, int i, ElemType e) {
    // 在顺序表L中第i个位置前插入元素e；若插入位置不合理则给出相应信息并退出运行
    // i的合理值为1≤i≤L.length+1
    if ((i < 1) || (i > L.length + 1))		// 插入元素的参数不合理
        Error(" Position Error!");

    if (L.length >= LIST_INIT_SIZE)	// 若当前存储空间已满，则增加空间
    {
        //Increment(L);
        Error("Insert Failed");
    }

    ElemType* q = &(L.elem[i - 1]);			// 令指针q指向插入位置
    ElemType* p = NULL;

    for (p = &(L.elem[L.length - 1]); p >= q; --p)
        *(p + 1) = *p;			// 依次后移元素

    *q = e;				// 在L的第i个位置中插入e
    ++L.length;			// 修正L的长度，令其增1
} // ListInsert_Sq

void ListDelete_Sq(SqList& L, int i, ElemType& e) {
    // 删除顺序表L中第i个元素并用e返回其值；若插入位置不合理则给出信息并退出运行
    // i的合理值为1≤i≤L.length
    if ((i < 1) || (i > L.length))		// 删除元素的参数不合理
        Error(" Position Error!");
    e = L.elem[i - 1];			// 将待删除元素的值赋给e
    ElemType* p = &(L.elem[i - 1]);			// 指向L中待删除元素的位置
    ElemType* q = L.elem + L.length - 1;	   	// 指向L中最后一个元素的位置

    for (++p; p <= q; ++p)
        *(p - 1) = *p; 			// 依次前移元素

    --L.length;			// 修正L的长度，令其减1
} // ListDelete_Sq

void TraverseList_Sq(SqList L) {
    // 依次输出顺序表L中的每个数据元素
    if (L.length != 0) {
        int i = 1;				// 指示位序，初值为1
        ElemType* p = L.elem;			// 指向L第i个元素，初始指向首元素

        // 依次输出L中的元素
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