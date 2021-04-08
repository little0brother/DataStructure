/*
* KMP算法精髓为next数组 ，
*	next数组：当模式串与目标串进行比较时，当模式串元素与目标串元素不同时，用于进行回溯模式串的数组
*	eg:	位序j：    1 2 3 4 5 6 7 8 9
*		模式串     a b a b a a a b a
*		next数组   0 1 1 2 3 4 2 2 3
* 
*	next数组计算方法（如果最大前缀 = 最大后缀，那么next数组的对应位为 最大前缀个数+1）
*			  |  0    j = 1
*	next[j] = |  max{k|1<k<j, 且"t[1]t[2]...t[k-1](前缀) == t[j-k+1]t[j-k]...t[j-1](后缀)"}
*			  |	 1    其他情况
*/

#include <iostream>
using namespace std;

// 计算next数组
void getNextArr(string modelStr, int* next)
{
	int i = 0;
	int j = -1;
	next[0] = -1;

	int mLen = modelStr.length();

	// 自己写个字符串根据流程一座就懂
	while (i < mLen - 1)
	{
		if (j == -1 || modelStr[i] == modelStr[j])
		{
			i++;
			j++;

			// 如果字符相同
			if (modelStr[i] == modelStr[j])
			{
				next[i] = next[j];
			}
			else
			{
				next[i] = j;
			}
		}
		else
		{
			// 当没有匹配上 则进行回溯 回溯的位置为next数组的指向的下一个匹配项
			j = next[j];
		}
	}
}

// 如果查找成功返回位置
// 如果查找失败返回-1
int KMP(string dstStr, string modelStr)
{
	int i = 0;
	int j = 0;

	int dstlen = dstStr.length();
	int modellen = modelStr.length();

	int next[255] = { 0 };

	getNextArr(modelStr, next);

	while ((i < dstlen) && (j < modellen))
	{
		if (j == -1 || dstStr[i] == modelStr[j])
		{
			i++;
			j++;
		}
		else
		{
			j = next[j];
		}
	}

	if (j >= modellen)
	{
		return i - modellen;   // 匹配成功 返回子串位置
	}
	else
	{
		return -1;
	}
}

int main()
{
	string dstStr = "aacdgabadd";
	string modelStr = "ba";

	int flag = KMP(dstStr, modelStr);
	if (flag != -1)
	{
		cout << modelStr << "位置为：" << flag << endl;
	}
	else
	{
		cout << "未找到" << modelStr << endl;
	}
	
	return 0;
}