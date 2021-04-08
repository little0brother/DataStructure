// 利用迭代法实现 斐波那契数列
#include <iostream>
using namespace std;

int main()
{
	int a[40] = { 0 };

	a[0] = 0;
	a[1] = 1;
	cout << a[0] << "\n" << a[1] << endl;

	for (int i = 2; i < 40; i++)
	{
		a[i] = a[i - 1] + a[i - 2];

		cout << a[i] << endl;
	}

	return 0;
}