#include<stdio.h>
#include<stdlib.h>
#include<iostream>
using namespace std;

int n;//��Ʒ�ܸ���
int b;//��������
int nos;//�����Ӽ�����Ʒ����
int t[50];//��¼���Ӽ�����Ʒ��ż�����
int sum_v = 0, sum_w = 0;


class goods
{
public:
	int weight;
	int value;
	int flag;
	goods();
	~goods();

private:

};

goods::goods()
{
}

goods::~goods()
{
}

goods goodlist[100];

//��¼��ǰ�Ӽ�
int record(int sum_v)
{
	int i;
	int count = 0;
	t[0] = sum_v;
	for (i = 0; i <= n; i++)
	{
		if (goodlist[i].flag)
			t[++count] = i + 1;
	}
	return count;
}

//�������Ž�
void findbest(int x)
{
	int i;
	if (sum_w > b)
		return;
	if (sum_v > t[0])
		nos = record(sum_v);
	for (i = x; i <= n; i++)
	{
		sum_v = sum_v + goodlist[i].value;
		sum_w = sum_w + goodlist[i].weight;
		goodlist[i].flag = 1;

		findbest(i + 1);

		sum_v = sum_v - goodlist[i].value;
		sum_w = sum_w - goodlist[i].weight;
		goodlist[i].flag = 0;
	}
}

int main()
{
	int i;
	printf("��������Ʒ������ ");
	cin >> n ;
	printf("�����뱳�����أ� ");
	cin >> b;
	printf("�������������������Լ���ֵ�� ");
	for (i = 0; i < n; i++)
	{
		cin>>goodlist[i].weight>>goodlist[i].value;
		
		goodlist[i].flag = 0;
	}

	findbest(0);

	printf("����ѡ���⼸����Ʒ��������м�ֵ���Ӽ���\n");
	for (i = 1; i <= nos; i++)
		printf("%d\n", t[i]);
	printf("�ܼ�ֵΪ %d\n", t[0]);
	system("pause");

}
/*
7 42
3 12
4 40
5 25
*/