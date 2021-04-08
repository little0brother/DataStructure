/*
* KMP�㷨����Ϊnext���� ��
*	next���飺��ģʽ����Ŀ�괮���бȽ�ʱ����ģʽ��Ԫ����Ŀ�괮Ԫ�ز�ͬʱ�����ڽ��л���ģʽ��������
*	eg:	λ��j��    1 2 3 4 5 6 7 8 9
*		ģʽ��     a b a b a a a b a
*		next����   0 1 1 2 3 4 2 2 3
* 
*	next������㷽����������ǰ׺ = ����׺����ônext����Ķ�ӦλΪ ���ǰ׺����+1��
*			  |  0    j = 1
*	next[j] = |  max{k|1<k<j, ��"t[1]t[2]...t[k-1](ǰ׺) == t[j-k+1]t[j-k]...t[j-1](��׺)"}
*			  |	 1    �������
*/

#include <iostream>
using namespace std;

// ����next����
void getNextArr(string modelStr, int* next)
{
	int i = 0;
	int j = -1;
	next[0] = -1;

	int mLen = modelStr.length();

	// �Լ�д���ַ�����������һ���Ͷ�
	while (i < mLen - 1)
	{
		if (j == -1 || modelStr[i] == modelStr[j])
		{
			i++;
			j++;

			// ����ַ���ͬ
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
			// ��û��ƥ���� ����л��� ���ݵ�λ��Ϊnext�����ָ�����һ��ƥ����
			j = next[j];
		}
	}
}

// ������ҳɹ�����λ��
// �������ʧ�ܷ���-1
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
		return i - modellen;   // ƥ��ɹ� �����Ӵ�λ��
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
		cout << modelStr << "λ��Ϊ��" << flag << endl;
	}
	else
	{
		cout << "δ�ҵ�" << modelStr << endl;
	}
	
	return 0;
}