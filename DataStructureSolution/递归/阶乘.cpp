// ͨ���ݹ�ʵ�ֽ׳�

/*
*		|  1          n = 0
* n! =	|
*		|  n*(n-1)    n > 0
*/


#include <iostream>
using namespace std;

int factorial(int i)
{
	if (i == 0)
		return 1;
	else
		return i * factorial(i - 1);
}

int main()
{
	int n = 20;
	cout << n << "!Ϊ��" << factorial(n) << endl;

	return 0;
}