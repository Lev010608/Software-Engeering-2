#include <stdio.h> 

int sum(int a[10001],int n) 
  { 
  int s=0,i;
  for(i=0;i<n;i++) 
  if(a[i]>a[n/2]) 
  s+=a[i]-a[n/2]; 
  else s+=a[n/2]-a[i]; 
  return s; 
  }
void sort(int a[10001],int n) 
{ 
  int i,j,tem; 
  for(i=0;i<n;i++) 
     { 
	   for(j=i+1;j<n;j++) 
	       if(a[i]>a[j])
		      {
			   tem=a[i]; 
			   a[i]=a[j]; 
			   a[j]=tem; 
			   } 
	 } 
}
int main() 
{ 
   int i,x,y,n,ax[10001],ay[10001]; 
   printf("��������������� \n");
   scanf("%d",&n);
   printf("�����������꣬�硰2 3���� \n");
   for(i=0;i<n;i++) 
     scanf("%d %d",&ax[i],&ay[i]);
	 sort(ax,n); 
	 sort(ay,n);
     printf("�ý���%d������㵽�ʾֵľ����ܺ���СΪ��%d\n",n,sum(ax,n)+sum(ay,n));
     return 0;
 }

