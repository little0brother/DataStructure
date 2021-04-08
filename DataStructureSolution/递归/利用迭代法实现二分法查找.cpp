#include <iostream>
using namespace std;

int DichotomySearch(int* arr, int key, int len)
{
	int low = 0;
	int mid = 0;
	int heigh = len;

	while (low < heigh)
	{
		mid = (heigh + low) / 2;

		if (arr[mid] > key)
		{
			heigh = mid;

			if (mid == 0)
			{
				return -1;
			}
		}

		if (arr[mid] < key)
		{
			low = mid;

			if (mid == len - 1)
			{
				return -1;
			}
		}

		if (arr[mid] == key)
		{
			return mid;
		}
	}

	if (low >= heigh)
	{
		return -1;
	}	
}

int main()
{
	int arr[12] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };
	int key = 0;
	
	cout << "输入查找值：";
	cin >> key;

	int flag = DichotomySearch(arr, key, 12);
	if (flag != -1)
	{
		cout << key << "位置为：" << flag + 1 << endl;
	}
	else
	{
		cout << "未找到" << key << endl;
	}

	return 0;
}