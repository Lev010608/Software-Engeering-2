/*
*�㷨����ʵ��һ
* 
*���������0/1��������
*by TY 20181018 
*
*��Ŀ���ã����û����뱳������������Ʒ�������Լ�
*�۸�Ĭ������Ϊһ����Ȼ�������ֵ��ߵ����
*����ʾ��ֵ 
*
*/
#include<stdio.h>

int n;//��Ʒ�ܸ���
int b;//��������
int nos;//�����Ӽ�����Ʒ����
int t[50];//��¼���Ӽ�����Ʒ��ż�����
int sum_v=0,sum_w=0;
 
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
void super_v(int x)
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
		
		super_v(i+1);
		
		sum_v=sum_v-a[i].v;
		sum_w=sum_w-a[i].w;
		a[i].flag=0;
	}
} 

int main()
{
	int i;
	printf("��������Ʒ������ ");
	scanf("%d",&n);
	printf("�����뱳�����أ� ");
	scanf("%d",&b);
	printf("�������������������Լ���ֵ�� ");
	for(i=0;i<n;i++)
	{
		scanf("%d %d",&a[i].w,&a[i].v);
		a[i].flag=0;
	} 

super_v(0);

printf("����ѡ���⼸����Ʒ��������м�ֵ���Ӽ���\n");
for(i=1;i<=nos;i++)
printf("%d\n",t[i]); 
printf("�ܼ�ֵΪ %d\n",t[0]);

}
