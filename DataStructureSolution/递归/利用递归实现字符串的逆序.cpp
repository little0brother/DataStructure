#include <iostream>
using namespace std;

void printchar()
{
	char ch;
	cin >> ch;

	if (ch != '#')
		printchar();
	if (ch != '#')
		cout << ch;
}

int main()
{
	printchar();

	return 0;
}