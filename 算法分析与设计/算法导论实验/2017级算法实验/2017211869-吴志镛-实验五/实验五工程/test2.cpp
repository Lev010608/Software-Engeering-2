#include<stdio.h>
#include<iostream>
#include<algorithm>
#include<string.h>
using namespace std;
//������01��������(��ǰ״̬��ѡ�벻ѡȡ���)
int dp[1005];
struct node
{
	int s, e, v;
}a[1005];
bool cmp(node a, node b)
{
	if (a.s == b.s) return a.e < b.e;
	return a.s < b.s;
}
int m, r;
int main()
{

	printf("������������ȵ��������������ʱ�䣺");
	cin  >> m >> r;

	for (int i = 0; i < m; i++) {
		printf("����������Ŀ�ʼʱ�䣬����ʱ���Ȩֵ");
		cin >> a[i].s >> a[i].e >> a[i].v;
	}
	sort(a, a + m, cmp);
	for (int i = 0; i < m; i++)
	{
		dp[i] = a[i].v;
		for (int j = 0; j <= i; j++)
		{
			if (a[j].e + r <= a[i].s)
				dp[i] = max(dp[i], dp[j] + a[i].v);//ת�Ʒ��̣�i��ö��ÿһ������,ÿһ�����ѭ��
				//�����ö�������������µ����Ч�棨�ڴ�ѭ�������������֮ǰ�Ĳ���ͻ�����䣩
				//Ҳ����dp[i]����ö��������䵱ǰ���Ч���
		}
	}
	int res = 0;
	for (int i = 0; i < m; i++)
		res = max(res, dp[i]);

	cout<<"�������Ϊ��" << res;

	system("pause");
	return 0;
}

/*
6 0
0 1 2
2 3 5
4 5 7
7 8 10
5 7 9
5 9 5
*/
