#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
#define N 100

struct goods
{
	int wight;
	int value;
	int sign;
}good[N];

int n;//�ܵ���������
int maxValue, maxWight;//����ֵ���������
int cw, cv;//Ŀǰ��������Ŀǰ�ļ�ֵ
int X[N], cx[N];//����·������ǰ·��

int BackTrack(int i)
{
	if (i > n - 1)//��������Ʒ���ӽ�ȥ֮��
	{
		if (maxValue < cv)
		{
			for (int k=0; k < n; k++)
				X[k] = cx[k];
			maxValue = cv;
		}
		return maxValue;
	}
	if (cw + good[i].wight <= maxWight)//����������
	{
		cw = cw + good[i].wight;
		cv = cv + good[i].value;
		cx[good[i].sign] = 1;//װ��Ϊ1
		BackTrack(i + 1);
		cw -= good[i].wight;//���ݽ���������
		cv -= good[i].value;
	}
	cx[good[i].sign] = 0;//��װ��Ϊ0
	BackTrack(i + 1);
}

int BackPack(int n,goods good[],int maxWight,int x[])
{
	for (int i = 0; i < n; i++)//��ʼ��
	{
		x[i] = 0;
		good[i].sign = i;
	}
	BackTrack(0);
	return maxValue;
}

int main()
{
		printf("��Ʒ����n: ");
		scanf("%d", &n);	//������Ʒ����
		printf("��������C: ");
		scanf("%d", &maxWight);	//���뱳������
		for (int i = 0; i<n; i++)	//������Ʒi������w�����ֵv
		{
			printf("��Ʒ%d������w[%d]�����ֵv[%d]:  ", i + 1, i + 1, i + 1);
			scanf("%d%d", &good[i].wight, &good[i].value);
		}
		int sum = BackPack(n, good, maxWight, X);//���û��ݷ���0/1��������
		printf("���ݷ����0/1��������:\nX=[ ");
		for (int i = 0; i<n; i++)
			cout << X[i] << " ";//�������X[n]����
		printf("]	װ���ܼ�ֵ%d\n", sum);
		system("pause");
		return 0;
	}
