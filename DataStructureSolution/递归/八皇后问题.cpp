/* 
	8X8�������Ϸ���8���ʺ����������ʺ󶼲���ͬһ�����ߡ����ߡ�б��	
	���õݹ�ʵ�����̵ļ���
*/

#include <iostream>
using namespace std;

int countt = 0;

// �жϸ��С��С����ζԽ����Ƿ�ȫ
bool IsDanger(int row, int lin, int(*chess)[8])
{
	int flag1 = 0;
	int flag2 = 0;
	int flag3 = 0;
	int flag4 = 0;
	int flag5 = 0;

	// �ж���
	for (int i = 0; i < 8; i++)
	{
		if (chess[i][row] != 0)
		{
			flag1 = 1;
			break;
		}
	}

	// �ж����϶Խ���
	for (int i = row, int j = lin; i >= 0 && j >=0; i--, j--)
	{
		if (chess[i][j] != 0)
		{
			flag2 = 1;
			break;
		}
	}

	// �ж����¶Խ���
	for (int i = row, int j = lin; i < 8 && j < 8; i++, j++)
	{
		if (chess[i][j] != 0)
		{
			flag3 = 1;
			break;
		}
	}

	// �ж����϶Խ���
	for (int i = row, int j = lin; i >= 0 && j < 8; i--, j++)
	{
		if (chess[i][j] != 0)
		{
			flag4 = 1;
			break;
		}
	}
	
	// �ж����¶Խ���
	for (int i = row, int j = lin; i < 8 && j >= 0; i++, j--)
	{
		if (chess[i][j] != 0)
		{
			flag5 = 1;
			break;
		}
	}

	// �����һ��Ϊ�� �������ȫ
	if (flag1 || flag2 || flag3 || flag4 || flag5)
	{
		return false;
	}
	else
	{
		return true;
	}
}

// row: ������ʼ�к�
// lin: �����к�
// (*chess)[8]: ָ������ÿһ�е�ָ��
void EightQueen(int row, int lin, int(*chess)[8])
{
	int chess2[8][8];   // �ݴ���������

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			chess2[i][j] = chess[i][j];
		}
	}

	// �ʺ��Ѿ�ȫ���ŵ�������
	// ��ӡ���
	if (row == 8)
	{
		cout << "��" << countt + 1 << "�֣�" << endl;
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
	// Ѱ�Ұ�ȫλ�÷��ûʺ�
	else 
	{
		// ����ÿһ��
		for (int j = 0; j < 8; j++)
		{
			if (IsDanger(row, j, chess))
			{
				// ����ǰ������Ԫ�ظ�Ϊ0
				for (int i = 0; i < 8; i++)
				{
					chess2[row][i] = 0;
				}

				// ����ǰ�� ��ȫλ�� ���ûʺ�
				chess[row][j] = 1;
			}

			// Ѱ����һ�еİ�ȫλ��
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