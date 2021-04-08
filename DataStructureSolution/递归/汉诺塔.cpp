// 汉诺塔游戏
// 可以从最简单的三层结构入手
// 分析三层结构移动规则，类比至多层结构 发现移动规律完全相同

/*
* 
1 > 把n - 1个圆盘由A移到B；
2 > 把第n个圆盘由A移到C；
3 > 把n - 1个圆盘由B移到C；

****那如何把n-1个圆盘从A移到B呢？（借助C塔移到了B上）

我们可以把n-2个圆盘看成一个整体去分析：
1>把n-2个圆盘由A移到C；
2>把第n-1个圆盘由A移到B；
3>把n-2个圆盘由C移到B；

****那如何把n-1个圆盘从B移到C呢？（借助A塔移到了C上）

1>把n-2个圆盘由B移到A；
2>把第n-1个圆盘由B移到C；
3>把n-2个圆盘由A移到C；


重点：
（1）中间的一步是把最大的一个盘子由A移到C上去；
（2）中间一步之上可以看成把A上n-1个盘子通过借助C塔移到了B上，
（3）中间一步之下可以看成把B上n-1个盘子通过借助A塔移到了C上；
*/

#include <iostream>
using namespace std;

void move(int n, char x, char y, char z)
{
	if (n == 1)
	{
		cout << x << "->" << z << endl;
	}
	else
	{
		move(n - 1, x, z, y);
		cout << x << "->" << z << endl;
		move(n - 1, y, x, z);
	}
}

int main()
{
	int n;

	cout << "请输入层数：";
	cin >> n;

	cout << "步骤为：" << endl;
	move(n, 'x', 'y', 'z');

	return 0;
}