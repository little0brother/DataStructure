/* 
	8X8的棋盘上放置8个皇后，任意两个皇后都不在同一条横线、竖线、斜线	
	利用递归实现棋盘的计算
*/

#include <iostream>
using namespace std;

int countt = 0;

// 判断该行、列、主次对角线是否安全
bool IsDanger(int row, int lin, int(*chess)[8])
{
	int flag1 = 0;
	int flag2 = 0;
	int flag3 = 0;
	int flag4 = 0;
	int flag5 = 0;

	// 判断列
	for (int i = 0; i < 8; i++)
	{
		if (chess[i][row] != 0)
		{
			flag1 = 1;
			break;
		}
	}

	// 判断左上对角线
	for (int i = row, int j = lin; i >= 0 && j >=0; i--, j--)
	{
		if (chess[i][j] != 0)
		{
			flag2 = 1;
			break;
		}
	}

	// 判断右下对角线
	for (int i = row, int j = lin; i < 8 && j < 8; i++, j++)
	{
		if (chess[i][j] != 0)
		{
			flag3 = 1;
			break;
		}
	}

	// 判断右上对角线
	for (int i = row, int j = lin; i >= 0 && j < 8; i--, j++)
	{
		if (chess[i][j] != 0)
		{
			flag4 = 1;
			break;
		}
	}
	
	// 判断左下对角线
	for (int i = row, int j = lin; i < 8 && j >= 0; i++, j--)
	{
		if (chess[i][j] != 0)
		{
			flag5 = 1;
			break;
		}
	}

	// 如果又一个为真 则代表不安全
	if (flag1 || flag2 || flag3 || flag4 || flag5)
	{
		return false;
	}
	else
	{
		return true;
	}
}

// row: 代表起始行号
// lin: 代表列好
// (*chess)[8]: 指向棋盘每一行的指针
void EightQueen(int row, int lin, int(*chess)[8])
{
	int chess2[8][8];   // 暂存棋盘内容

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			chess2[i][j] = chess[i][j];
		}
	}

	// 皇后已经全部放到棋盘上
	// 打印结果
	if (row == 8)
	{
		cout << "第" << countt + 1 << "种：" << endl;
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				cout << chess2[i][j] << " ";
			}
			cout << endl;
		}

		cout << endl;
		countt++;
	}
	// 寻找安全位置放置皇后
	else 
	{
		// 代表每一列
		for (int j = 0; j < 8; j++)
		{
			if (IsDanger(row, j, chess))
			{
				// 给当前行所有元素赋为0
				for (int i = 0; i < 8; i++)
				{
					chess2[row][i] = 0;
				}

				// 将当前行 安全位置 放置皇后
				chess[row][j] = 1;
			}

			// 寻找下一行的安全位置
			EightQueen(row + 1, lin, chess2);
		}
	}

}

int main()
{
	int chess[8][8] = { 0 };

	// EightQueen(0, 8, chess);

	cout << "hell" << endl;

	return 0;
}