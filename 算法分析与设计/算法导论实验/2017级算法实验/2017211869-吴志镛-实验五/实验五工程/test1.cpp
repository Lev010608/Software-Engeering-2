
#include<iostream>
#include<cstdio>
using namespace std;

int f[11][11] = { 0 }, w[11], p[11];//�����������������10����Ʒ����,������10����
void knap9(int m, int n)
{
	int i = 0, j = 0;
	//��ʼ��
	for (j = 0; j <= m; ++j)
	{
		f[n][j] = 0;
	}
	//����n����Ʒ����
	for (j = w[n]; j <= m; ++j)
	{
		f[n][j] = p[n];
	}
	//���ж�̬�滮
	for (i = n - 1; i > 1; --i)
	{
		//���ǲ��Ӵ���Ʒ��ȥ�����
		for (j = 0; j <= m; ++j)
		{
			f[i][j] = f[i + 1][j];
		}
		//������Ʒ��������
		for (j = w[i]; j <= m; ++j)
		{
			if (f[i + 1][j] > f[i + 1][j - w[i]] + p[i])
				f[i][j] = f[i + 1][j];
			else
				f[i][j] = f[i + 1][j - w[i]] + p[i];
		}
	}
	if (m >= w[1])
	{
		if (f[1][m] > f[2][m - w[1]] + p[1])
			f[1][m] = f[2][m];
		else
			f[1][m] = f[2][m - w[1]] + p[1];
	}
}
int main()
{
	int m, n, i, s;
	int currw, currp;
	cout << "�����뱳�����������:";
	cin >> m;
	cout << "��������Ʒ�ĸ���:";
	cin >> n;
	//��ʼ����Ʒ������������
	n = n - 1;
	i = 1;
	s = 0;
	cout << "����������������:";
	cin >> currw >> currp;
	while (i <= n && currw > 0 && currp > 0)
	{
		s = s + currw;
		if (currw <= m)
		{
			w[i] = currw;
			p[i] = currp;
			i = i + 1;
		}
		else
		{
			cout << "��Ʒ����������������!������" << endl;
		}
		cout << "����������������:";
		cin >> currw >> currp;
	}
	if (s <= m)
	{
		cout << "whloe choose" << endl;
		return 0;
	}
	knap9(m, n);
	printf("The max value is %d\n", f[1][m]);


	system("pause");

}
/*
10
5
2 3
4 5
2 6
3 5
4 2
*/