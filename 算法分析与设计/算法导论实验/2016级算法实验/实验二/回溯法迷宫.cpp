/*
*�㷨����ʵ���
*
*���ݷ�����Թ�����
*by TY 20181101
*
*
*/
#include<stdio.h>
#define n1 30//�����
#define n2 30//�����
struct migong
{
	int x;                                      	//��¼����
	int y;                                         	//��¼����
	int c;  										//����1Ϊ�ң�2Ϊ�ϣ�3Ϊ��4Ϊ�£�
} top[n1*n2];
int roww,linee;                             	//���·��ʱʹ��
int mapp[100][n1][n2];                          //��¼��
int a[100]= {0};                             	//·������
int row,line,r,l,ar,al,br,bl,i,j,k;
int n=0;										//��ĸ���
int xx[100][n1];
int yy[100][n2];								//���·��

void printbest()
{
	if(n==0)
	{
		printf("���Թ��޽�\n");
		return;
	}
	else
		printf("���Թ���%d����\n",n);

	int min,t,p,m;
	min=a[0];
	t=0;
	for(p=0; p<n; p++)                         //�ҳ����Ž�
	{
		if(a[p]<=min)
		{
			t=p;
			min=a[p];
		}
	}
	printf("\n���Ž�Ϊ:\n");
	for(p=0; p<n; p++)
	{
		if(a[p]==min)
		{
			printf("��%d�ֽ�:\n",p+1);
			printf("(%d,%d)",xx[p][0],yy[p][0]);
			for(m=1; m<=a[p]; m++)
			{
				printf("->(%d,%d)",xx[p][m],yy[p][m]);
			}
			printf("\n·��Ϊ(2�����߹���·):\n");
			for(roww=0; roww<row; roww++)
			{
				for(linee=0; linee<row; linee++)
					printf("%d ",mapp[p][roww][linee]);
				printf("\n");
			}
			printf("\n");
		}
	}
}

int main()
{
	//��ʼ���Թ�
	printf("��������������:");
	scanf("%d%d", &row, &line);
	int map[n1][n2];
	for(r=0; r<=row; r++)
	{
		for(l=0; l<=line; l++)
			map[r][l]=1;
	}
	printf("�������ͼ����0Ϊ·����1Ϊǽ(����һ�к󰴻س�����һ��):\n");
	for (r = 0; r < row; r++)
	{
		for (l = 0; l < line; l++)
		{
			scanf("%d", &map[r][l]);
		}
	}
	printf("�����Թ��������:");
	scanf("%d%d",&ar,&al);
	printf("�����Թ���������:");
	scanf("%d%d",&br,&bl);
	printf("\n");
	i=0;
	top[i].x=ar;
	top[i].y=al;
	top[i].c=1;
	do
	{
		if(top[i].c<5)
		{
			if(top[i].x==br&&top[i].y==bl)
			{
				n++;
				map[br][bl]=2;
				printf("��%d�ֽ�:\n",n);
				printf("(%d,%d)",top[0].x,top[0].y);
				for(j=1; j<=i; j++)
					printf("->(%d,%d)",top[j].x,top[j].y);
				printf("\n·��Ϊ(2�����߹���·):\n");
				for(roww=0; roww<row; roww++)
				{
					for(linee=0; linee<line; linee++)
					{
						printf("%d ",map[roww][linee]);
					}
					printf("\n");
				}
				a[n-1]=i;
				for(k=0; k<=i; k++)
					xx[n-1][k]=top[k].x;
				for(k=0; k<=i; k++)
					yy[n-1][k]=top[k].y;
				for(roww=0; roww<row; roww++)
				{
					for(linee=0; linee<line; linee++)
					{
						mapp[n-1][roww][linee]=map[roww][linee];
					}
					printf("\n");
				}
				map[br][bl]=0;
				printf("\n");
				map[top[i-1].x][top[i-1].y]=0;//����
				i--;
				top[i].c++;

			}
			switch(top[i].c)
			{
				case 1:                            //����
				{

					if(map[top[i].x][top[i].y+1]==0)
					{
						map[top[i].x][top[i].y]=2;
						i++;
						top[i].x=top[i-1].x;
						top[i].y=top[i-1].y+1;
						top[i].c=1;
					}
					else top[i].c++;
					break;
				}
				case 2:                                       //����
				{
					if(map[top[i].x-1][top[i].y]==0)
					{
						map[top[i].x][top[i].y]=2;
						i++;
						top[i].x=top[i-1].x-1;
						top[i].y=top[i-1].y;
						top[i].c=1;
					}
					else top[i].c++;
					break;
				}
				case 3:                                         //�Ϸ���
				{
					if(map[top[i].x][top[i].y-1]==0)
					{
						map[top[i].x][top[i].y]=2;
						i++;
						top[i].x=top[i-1].x;
						top[i].y=top[i-1].y-1;
						top[i].c=1;
					}
					else top[i].c++;
					break;
				}
				case 4:                                //�·���

				{
					if(map[top[i].x+1][top[i].y]==0)
					{
						map[top[i].x][top[i].y]=2;
						i++;
						top[i].x=top[i-1].x+1;
						top[i].y=top[i-1].y;
						top[i].c=1;
					}
					else top[i].c++;
					break;
				}
			}
		}
		else//����
		{
			if(i==0)
			{
				printbest();
				return  0;
			}
			else
			{
				map[top[i-1].x][top[i-1].y]=0;
				i--;
				top[i].c++;
			}
		}
	}
	while(1);
	return 0;
}


