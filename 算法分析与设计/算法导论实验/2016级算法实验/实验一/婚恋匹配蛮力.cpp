/*
*����ƥ��������
*
*
*by Tianyu 20181024
*
*/
#include<stdio.h>
#include<queue>
using namespace std;

struct man
{
	int num;
	int like[5];
	int marryOrnot;
};

struct woman
{
	int num;
	int like[5];
	int marryOrnot;
};

man male[5];
woman female[5];

int marrage_status(man m[],woman w[])
{
	int temp=0;
	for(int i=0;i<5;i++)
	{
		temp+=m[i].marryOrnot+w[i].marryOrnot;
	}
	return temp;
}

int look_up(woman w[],int num)
{
	for(int i=0;i<5;i++)
	{
		if(w[i].num==num)
		return 1;
	}
	return -1;
}

int rank(woman w[],int num,)//
{
	
}

int main()
{
	printf("��������ʿ���Ǳ�\n");
	for(int i=0; i<5; i++)
	{
		printf("������� %d λ��ʿ�����Ǳ�: \n",i+1);
		male[i].num=i;
		male[i].marryOrnot=-1;
		for(int j=0; j<5; j++)
		{
			scanf("%d",&male[i].like[j]);
		}
	}

	printf("������Ůʿ���Ǳ�\n");
	for(int i=0; i<5; i++)
	{
		printf("������� %d λŮʿ�����Ǳ�: \n",i+1);
		female[i].num=i;
		female[i].marryOrnot=-1;
		for(int j=0; j<5; j++)
		{
			scanf("%d",&female[i].like[j]);
		}
	}

	int mark[5][5];//��һλ�ȵ������Ƿ���ڶ�λ�ȵ�Ů�������
	for(int i=0; i<5; i++)
	{
		for(int j=0; j<5; j++) mark[i][j]=-1;
	}

	


	for (int i=0; i<5; i++)
	{
		printf("%d %d\n",male[i].num+1,male[i].marryOrnot);
	}

	getchar();
}



