#include<stdio.h>

int greedy(int A[],int d,int n){
	int num=0;
	for(int i=0;i<=n;i++){
		if(A[i]>d){
			printf("�޽⡣\n");
			return 0;
		}
	}
	for(int i=0,s=0;i<=n;i++){
		s+=A[i];
		if(s>d){
			num++;
			s=A[i];
		}
	}
	printf("���ټ��ʹ���Ϊ%d.\n",num);
}
int main(){
	int i,d,n;
	int A[100];
	printf("������ÿ�μ��Ϳ���ʻ·�̣� \n"); 
	scanf("%d",&d);
	printf("���������վ������ \n"); 
	scanf("%d",&n); 
	printf("������%d������վ֮����룺 \n",n); 
	for(i=0;i<n;i++){
	scanf("%d",&A[i]);  
    }
    greedy(A,d,n);
} 


