// ���õݹ�ʵ��쳲���������

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
	cout << "쳲��������е�" << i << "��Ϊ��" << fib(i) << endl;

	return 0;
}