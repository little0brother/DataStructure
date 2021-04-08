#include <iostream>
using namespace std;

int DichotomySearch(int* arr, int key, int len)
{
	int low = 0;
	int heigh = len;
	int mid = (heigh + low) / 2;
	int m;

	if (arr[mid] < key)
	{
		low = mid;
		m = DichotomySearch(&arr[low], key, heigh - low + 1);
	}

	if (arr[mid] > key)
	{
		heigh = mid;
		m = DichotomySearch(&arr[low], key, heigh - low + 1);
	}

	if (arr[mid] == key)
	{
		return mid;
	}

	if (arr[low] >= arr[heigh])
	{
		return -1;
	}

	if (m != -1)
	{
		m += low;
	}

	return m;
}

int main()
{
	int arr[12] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };
	int key = 0;

	cout << "�������ֵ��";
	cin >> key;

	int flag = DichotomySearch(arr, key, 12);
	if (flag != -1)
	{
		cout << key << "λ��Ϊ��" << flag + 1 << endl;
	}
	else
	{
		cout << "δ�ҵ�" << key << endl;
	}


	return 0;
}