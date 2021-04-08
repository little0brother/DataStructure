// 利用递归实现斐波那契数列

#include <iostream>
using namespace std;

int fib(int i)
{
	if (i < 2)
		return (i == 0 ? 0 : 1);

	return fib(i - 1) + fib(i - 2);
}

int main()
{
	int i = 100;
	cout << "斐波那契数列第" << i << "项为：" << fib(i) << endl;

	return 0;
}