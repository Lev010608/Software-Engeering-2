/*
*
*ʵ���� ��̬�滮���01��������
*
*BY TianYu 
*
*2018 12 20
*
*
*/

#include<stdio.h>
int bag_w,num;
int goods_v[5],goods_w[5]; 
int bag_v[5][11];
void Start()
{
	printf("�����뱳��������");
	scanf("%d",&bag_w);
	printf("��������Ʒ��Ŀ��");
	scanf("%d",&num);
	printf("��ֱ�����ÿ����Ʒ�ļ�ֵ��\n");
	for(int i=1;i<=num;i++)
	{
		scanf("%d",&goods_v[i]);
	}
	printf("��ֱ�����ÿ����Ʒ�������\n");
	for(int j=1;j<=num;j++)
	{
		scanf("%d",&goods_w[j]);
	}
}

void Max()
{
	for(int i=1;i<=num;i++)
	{
		for(int j=1;j<=bag_w;j++)
		{
			if(j<goods_w[i])//װ����ȥ
			{
				bag_v[i][j]=bag_v[i-1][j];
			} 
			else //����װ 
			{
				//��װ��ֵ�� 
				if(bag_v[i-1][j]>bag_v[i-1][j-goods_w[i]]+goods_v[i])
				{
					bag_v[i][j]=bag_v[i-1][j];
				}
				//ǰi-1����Ʒ�����Ž����i����Ʒ�ļ�ֵ֮�͸���
				else
				{
					bag_v[i][j]=bag_v[i-1][j-goods_w[i]]+goods_v[i];
				}
			}
		}
	}
}

int item[5];

void Find(int i,int j)
{
	if(i>=0)
    {
        if(bag_v[i][j]==bag_v[i-1][j])//���˵��ûװ
        {
            item[i]=0;//ȫ�ֱ��������δ��ѡ��
            Find(i-1,j);
        }
        else if(j-goods_w[i]>=0 && bag_v[i][j]==bag_v[i-1][j-goods_w[i]]+goods_v[i])
        {
            item[i]=1;//����ѱ�ѡ��
            Find(i-1,j-goods_w[i]);//�ص�װ��֮ǰ��λ��
        }
    }
}

void Print()
{
	printf("��������ֵΪ��%d",bag_v[num][bag_w]);
	printf("\n�ֱ�����Ʒ��\n");
	for(int i=1;i<=num;i++)
	{
		if(item[i]!=0)
			printf("��%d����Ʒ\n",i);
	}
}

int main()
{
	Start();
	Max();
	Find(num,bag_w);
	Print();
	return 0;
}













