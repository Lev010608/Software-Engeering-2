#include <iostream>
#include <stdlib.h>
#include <stdio.h>
int n; 
int c[1000][1000];
unsigned int mincost = 100000; //���õĳ�ʼֵ,���ڿ��ܵĳɱ� 
int task[1000],temp[1000],worker[1000];
int main()
{ 
	void Plan(int k,unsigned int cost);
	int i,j;	 
	printf("������������������:");
	scanf("%d%d",&n,&n);
	printf("����ÿ������ɸ�������ĳɱ�����:\n");  
	for(i=0;i<n;i++)
	{  
	    /*task[i]:ֵΪ0��ʾ����iδ����,ֵΪj��ʾ����i�������Աj;
	      worker[k]:ֵΪ0��ʾ��Աkδ��������,ֵΪ1��ʾ��Աk�ѷ�������;*/
	      worker[i] = 0;  
	      task[i]   = 0; 
	      temp[i]   = 0; 
	      for(j=0;j<n;j++) 
		  scanf("%d",&c[i][j]);
	} 
	Plan(0,0);    //������0��ʼ����
	printf("��С�ܷ���:%d\n",mincost);
	for(i=0;i<n;i++)
		printf("��Ա:%dִ������:%d\n",i+1,temp[i]+1);
	
	return 0;
} 
void Plan(int k,unsigned int cost)
{
	int i; 
	if(k>=n && cost<mincost) 
	{
		mincost = cost;   
		for(i=0;i<n;i++)  
			temp[i] = task[i]; //��Աi�������temp[i] 
	}
	else 
	{ 
		for(i=0;i<n;i++) 
		{ 
			//��������k  
			if(worker[i]==0) 	
			{ worker[i] = 1;
			  task[k] = i;
			  Plan(k+1,cost+c[k][i]); 
			  worker[i] = 0; 
			  task[k] = 0;  
			}  
		} 
	}
}

