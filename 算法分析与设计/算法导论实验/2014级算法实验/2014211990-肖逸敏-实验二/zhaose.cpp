#define _CRT_SECURE_NO_WARNINGS
#include<iostream> 
using namespace std; 

int color[100];
bool Ok(int k, int c[][100])   //�ж϶���k����ɫ�Ƿ�����ͻ 
{ 
for (int i = 1; i<k; i++)
	if (c[k][i] == 1 && color[i] == color[k]) //��������ɫ��ͬʱΪfalse              
		return false;      
return true;   
}
	
void GraphColor(int n, int m, int c[][100])      //���������±��1��ʼ��nΪ��������mΪ��ɫ��
{   
		for (int i = 1; i <= n; i++)     //������color[n]��ʼ��Ϊ0         
			color[i]=0;        
		int k=1;        
		while (k>=1)        
		{ 
			color[k] = color[k] + 1;          
			while (color[k] <= m)                
				if (Ok(k, c))     
					break;                
				else      
					color[k] = color[k] + 1;   //������һ����ɫ          
			if (color[k]<=m && k==n) //�����ϣ������          
			{ 
				for (int i = 1; i <= n; i++)                   
					cout << color[i];        //������       
				return;           
			}
		  else if (color[k] <= m && k<n)
		  {
			  k = k + 1;             //������һ������                       
			  color[k]=0;
		  }          
		  else  
			  k = k - 1;    //����           
		}   
} 

			  
int main(){
	//����ͼ���ڽӾ���
	int e[5][5]={
	{0,1,1,0,0},     
	{1,0,1,1,1},      
	{1,1,0,0,1},      
	{0,1,0,0,1},      
	{0,1,1,1,0}
	};  

	int i, j;
	int n=5, m=3;
	int c[100][100];//�洢n�����������ͼ������  
	printf("��֪����������ɫ���ֱ�Ϊ5��3\n");
	printf("��֪����ͼ���ڽӾ���:\n{0,1,1,0,0}\n{1,0,1,1,1}\n{1,1,0,0,1}\n{0,1,0,0,1}\n{0,1,1,1,0}\n"); 
	for (i = 1; i <= n; i++)
		for (j = 1; j <= n; j++) 
			c[i][j] = e[i - 1][j - 1];
	printf("��ɫ���п��ܵĽ�:\n");
	GraphColor(n, m, c);
	printf("\n");
	system("pause");
	return 0;
}