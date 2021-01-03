#include<stdlib.h>  
#include<time.h>  
#include<stdio.h>
#include<malloc.h>

int partition(int a[],int p,int r)
{
 int z=p,x=r+1;
 int y=a[p];
 int t;
 while(1)
 {
  while(a[++z]<y&&z<r);//��ѭ��������������ʱ����ִ��
  while(a[--x]>y);
  if(z>=x)break;
  t=a[z];
  a[z]=a[x];
  a[x]=t;
 }
 a[p]=a[x];
 a[x]=y;
 return x;
}
void quicksort(int a[],int p,int r)
{
 int q;
 if(p<r)
 {
  q=partition(a,p,r);
        quicksort(a,p,q-1);
        quicksort(a,q+1,r);
 }
}   

int main()
{
 for(;;)
 {
 int k,*a,*b,n,i,d,s;
   
    printf("�������������: \n");
    scanf("%d",&n);
    a=(int *)malloc(sizeof(int)*n);  //������a����ռ�
    srand((unsigned)time(NULL));
    b=(int *)malloc(sizeof(int)*n); //������b����ռ�
    srand((unsigned)time(NULL)); 
    printf("����������: \n");
	for(i=0 ;i<n;i++){
		scanf("%d",&a[i]);
    }
	for(i=0,d=0;d<n;d++){   //������a����b 
		b[d]=a[i];
		i++;
	}
	quicksort(a,0,i-1);            //���ÿ��������������
	printf("�����: \n");
	for(i=0;i<n;i++){
		printf("%d ",a[i]);
    }
    printf("\n");
	printf("�������kСԪ��:");
    scanf("%d",&k);
	for(d=0;d<n;d++){
		if(b[d]==a[k-1])          //������b���ҳ���kС������ԭ�����е�λ��
        s=d+1;
    }
	printf("��%dСԪ��Ϊ:%d\n",k,a[k-1]);
	printf("��%dСԪ��λ��Ϊ:%d",k,s);
	printf("\n"); 
	system("pause");
 }
}
