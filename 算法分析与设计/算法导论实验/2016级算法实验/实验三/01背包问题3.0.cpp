/*
*
*��֧�޽編���01�������� 
*
*BY Tian Yu 2018 11 22
*
*
*
*/
#include<stdio.h>
#include<windows.h> 

int n;//��Ʒ�ܸ���
int b;//��������
int nos;//�����Ӽ�����Ʒ����
int t[50];//��¼���Ӽ�����Ʒ��ż�����
int sum_v=0,sum_w=0;
int state;//�㷨ѡ�� 
 
//����һ���ṹ���ʾ��Ʒ 
struct goods
{
	int w;
	int v;
	int flag;
} a[100];

//��¼��ǰ�Ӽ�
int record (int sum_v)
{
	int i;
	int count=0;
	t[0]=sum_v;
	for(i=0;i<=n;i++)
	{
		if(a[i].flag)
		t[++count]=i+1;
	}
	return count;
} 

//�������Ž�
void super_vWithMLF(int x)
{
	int i;
	if(sum_w>b)
	return;
	if(sum_v>t[0])
	nos=record(sum_v);
	for(i=x;i<=n;i++)
	{
		sum_v=sum_v+a[i].v;
		sum_w=sum_w+a[i].w;
		a[i].flag=1;
		
		super_vWithMLF(i+1);
		
		sum_v=sum_v-a[i].v;
		sum_w=sum_w-a[i].w;
		a[i].flag=0;
	}
} 

void super_vWithHSF(int x)
{
	if(x>=n){
		if(sum_v>t[0])
		nos=record(sum_v);
		return;
	}
	else if(sum_w+a[x].w<=b)
	{
		a[x].flag=1;
		sum_v=sum_v+a[x].v;
		sum_w=sum_w+a[x].w;
		super_vWithHSF(x+1);
		sum_v=sum_v-a[x].v;
		sum_w=sum_w-a[x].w;
		a[x].flag=0;
		super_vWithHSF(x+1);
	}
	else{
		a[x].flag=0;
		super_vWithHSF(x+1);
	}
}

void super_vWithFZF(int x)
{
	
}

int main()
{
	int i;
	printf("��������Ʒ������ ");
	scanf("%d",&n);
	printf("�����뱳�����أ� ");
	scanf("%d",&b);
	printf("�������������������� ");
	for(i=0;i<n;i++)
	{
		scanf("%d %d",&a[i].w,&a[i].v);
		a[i].flag=0;
	} 
	printf("��ѡ���㷨��\n");
	printf("1.��������2.���ݷ� ;3.��֧��\n"); 
	scanf("%d",&state);
	
	switch(state)
	{
		case 1:super_vWithMLF(0);
		case 2:super_vWithHSF(0);
		case 3:super_vWithFZF(0); 
	}


printf("����ѡ���⼸����Ʒ��������м�ֵ���Ӽ���\n");
for(i=1;i<=nos;i++)
printf("%dth\n",t[i]); 
printf("�ܼ�ֵΪ %d\n",t[0]);

}
