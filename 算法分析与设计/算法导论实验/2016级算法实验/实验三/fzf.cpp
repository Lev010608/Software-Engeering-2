/*
*
*��֧�޽編���01�������� 
*
*BY Tian Yu 2018 11 22
*
*
*
*/

#include<iostream>
#include<cstdio>
#include<conio.h>
#include<iomanip>
using namespace std;
int *x;


struct node *front,*bestp,*first; //���ף����㡢�����
int *p,*w,n,c,*M;//������ֵ����������Ʒ����������������¼��С˳���ϵ
long lbestp;//�����������Ž� 
int nos;//�����Ӽ�����Ʒ����
int t[50];//��¼���Ӽ�����Ʒ��ż�����
int sum_v=0,sum_w=0;
int state;//�㷨ѡ�� 

struct goods
{
//����һ���ṹ���ʾ��Ʒ 
	int w;
	int v;
	int flag;
} a[100];
struct node 
	{
	          //���������ݽṹ
       node  *parent,//�����ָ��
             *next; //��̽��ָ��
       int    level,//���Ĳ�
              bag,//�ڵ�Ľ�
              cw,//��ǰ����װ���� 
              cp;//��ǰ������ֵ             
       float  ub; //�����Ͻ�ֵ
	};

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

int recordWithFZF(int sum_v)
	{
		int i;
		int count=0;
		t[0]=sum_v;
		for(i=n;i>=1;i--)
			{   
				x[M[i-1]]=bestp->bag;
				bestp=bestp->parent;
			}
		for(i=0;i<=n;i++)
		{
		if(x[i-1])
		t[++count]=i+1;
	    }
		return count;
	}

float Bound(int i,int cw,int cp)
	{// �����Ͻ�
		int cleft=c-cw; 
		float b=(float)cp; 
		while (i<n&&w[i]<=cleft)
		{
			cleft-=w[i];
			b+=p[i];
			i++;
		}
		if (i<n) b+=1.0*p[i]/w[i]*cleft;
		return b;
	}
node *nnoder(struct node *pa,int ba,float uub)
	{//����һ���½��
		node * nodell=new(node);
		nodell->parent=pa;
		nodell->next=NULL;
		nodell->level=(pa->level)+1;
		nodell->bag=ba;
		nodell->ub=uub;
		if(ba==1)
		{
			nodell->cw=pa->cw+w[pa->level];
			nodell->cp=pa->cp+p[pa->level] ;
		}
		else 
		{
			nodell->cw=pa->cw;
			nodell->cp=pa->cp;
		}
		return(nodell);
		}
void addnode(node *no)
	{//�����������ȶ���
		node *p=front->next,*next1=front;
		float ub=no->ub;
		while(p!=NULL)
		{
			if(p->ub<ub)
				{no->next=p;next1->next=no;break;}
			next1=p;
			p=p->next;
		}
		if(p==NULL){next1->next=no;
		}
	}
node *nextnode()
	{//ȡ��������� 
		node *p=front->next;
		front->next=p->next;
		return(p);
	}
void Sort()
	{
		int i,j,k,kkl;
		float minl; 
		for(i=1;i<n;i++)
		{   
			minl=1.0*p[i]/w[i];
			k=0;
			for(j=1;j<=n-i;j++)
				{
				  if(minl<1.0*p[j]/w[j])
					{
						minl=1.0*p[j]/w[j];
						swap(p[k],p[j]);
						swap(w[k],w[j]);
						swap(M[k],M[j]);          
						k=j;
					} 
				}
		}
	}
	
void Knap(int *pp,int *ww,int cc,int nn) 
	{
		int i;
		n=nn;
		c=cc;
		p=new int[n];
		w=new int[n];
		M=new int[n];
		for(i=0;i<n;i++)
		{
			p[i]=pp[i];
			w[i]=ww[i];
			M[i]=i;
		}
		front=new node[1];
		front->next=NULL;
		lbestp=0;
		bestp=new node[1];
		bestp=NULL;
		Sort();
	}
//void solvebag()
//	{//�����������
//		int i;
//		float ubb;
//		node *aa;
//		first=new node[1]; //�����
//		first->parent=NULL;
//		first->next=NULL;
//		first->level=0;
//		first->cw=0;
//		first->cp=0;
//		first->bag=0;
//		ubb=Bound(0,0,0);
//		first->ub=ubb;
//		front->next=first;
//		while(front->next!=NULL)
//			{
//				aa=nextnode();
//				i=aa->level;
//				if(i==n-1)
//					{   
//						if(aa->cw+w[i]<=c&&(long)(aa->cp+p[i])>lbestp)
//							{
//								lbestp=aa->cp+p[i];
//								bestp=nnoder(aa,1,(float)lbestp);
//							}
//						if((long)(aa->cp)>lbestp)
//							{ 
//								lbestp=aa->cp;
//								bestp=nnoder(aa,0,(float)lbestp);
//							}
//					}
//				if(i<n-1)
//					{ 
//						if(aa->cw+w[i]<=c&&Bound(i+1,
//							aa->cw+w[i],aa->cp+p[i])>(float)lbestp)
//							{
//								ubb=Bound(i,aa->cw+w[i],aa->cp+p[i]);
//								addnode(nnoder(aa,1,ubb));
//							}
//						ubb=ubb=Bound(i,aa->cw,aa->cp);
//						if(ubb>lbestp)
//						  addnode(nnoder(aa,0,ubb));
//					}
//				}
//				nos=recordWithFZF();
//			}
//�������Ž�
void super_vWithMLF(int x)
{
	int i;
	if(sum_w>c)
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
	
		cout<<"����ѡ���⼸����Ʒ��������м�ֵ���Ӽ���\n"<<endl;
		for(i=1;i<=nos;i++)
		cout<<i<<"th"<<endl;
		cout<<"�ܼ�ֵΪ:"<<t[0]<<endl;
} 

void super_vWithHSF(int x)
{
	int i=0;
	if(x>=n){
		if(sum_v>t[0])
		nos=record(sum_v);
		return;
	}
	else if(sum_w+a[x].w<=c)
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
	
		cout<<"����ѡ���⼸����Ʒ��������м�ֵ���Ӽ���\n"<<endl;
		for(i=1;i<=nos;i++)
		cout<<i<<"th"<<endl;
		cout<<"�ܼ�ֵΪ:"<<t[0]<<endl;
}

void super_vWithFZF(int *pp,int *ww,int cc,int nn)
{
		int i;
		n=nn;
		c=cc;
		p=new int[n];
		w=new int[n];
		M=new int[n];
		for(i=0;i<n;i++)
		{
			p[i]=pp[i];
			w[i]=ww[i];
			M[i]=i;
		}
		front=new node[1];
		front->next=NULL;
		lbestp=0;
		bestp=new node[1];
		bestp=NULL;
		Sort();
//�����������
		float ubb;
		node *aa;
		first=new node[1]; //�����
		first->parent=NULL;
		first->next=NULL;
		first->level=0;
		first->cw=0;
		first->cp=0;
		first->bag=0;
		ubb=Bound(0,0,0);
		first->ub=ubb;
		front->next=first;
		while(front->next!=NULL)
			{
				aa=nextnode();
				i=aa->level;
				if(i==n-1)
					{   
						if(aa->cw+w[i]<=c&&(long)(aa->cp+p[i])>lbestp)
							{
								lbestp=aa->cp+p[i];
								bestp=nnoder(aa,1,(float)lbestp);
							}
						if((long)(aa->cp)>lbestp)
							{ 
								lbestp=aa->cp;
								bestp=nnoder(aa,0,(float)lbestp);
							}
					}
				if(i<n-1)
					{ 
						if(aa->cw+w[i]<=c&&Bound(i+1,
							aa->cw+w[i],aa->cp+p[i])>(float)lbestp)
							{
								ubb=Bound(i,aa->cw+w[i],aa->cp+p[i]);
								addnode(nnoder(aa,1,ubb));
							}
						ubb=ubb=Bound(i,aa->cw,aa->cp);
						if(ubb>lbestp)
						  addnode(nnoder(aa,0,ubb));
					}
				}
		nos=recordWithFZF(lbestp);
		
		cout<<"����ѡ���⼸����Ʒ��������м�ֵ���Ӽ���\n"<<endl;
		for(i=1;i<=nos;i++)
		cout<<i<<"th"<<endl;
		cout<<"�ܼ�ֵΪ:"<<t[0]<<endl;
}
int main()
	{
		int c,n;
		int i=0;
		int *p;
		int *w;
		cout<<"�����뱳������:"<<endl;
		cin>>c;
		cout<<"��������Ʒ��:"<<endl;
		cin>>n; 
		x=new int[n];
		p=new int[n];
		w=new int[n];
		cout<<"������"<<n<<"����Ʒ������:"<<endl;
		for(i=0;i<n;i++)
		{
		    cin>>w[i]; 
		    a[i].w=w[i];
		    a[i].flag=0;
	    } 
		cout<<"������"<<n<<"����Ʒ��ֵ:"<<endl;
		for(i=0;i<n;i++)
		{
			cin>>p[i];
			a[i].v=p[i];
			a[i].flag=0;
		x=new int[n];
		
		cout<<"��ѡ���㷨��\n"<<endl;
		cout<<"1.��������2.���ݷ���3.��֧��\n"<<endl;
		cin>>state; 
		
		switch(state)
	    {
		    case 1:super_vWithMLF(0);
		    case 2:super_vWithHSF(0);
		    case 3:super_vWithFZF(p,w,c,n); 
	    }
//
//		cout<<"����ѡ���⼸����Ʒ��������м�ֵ���Ӽ���\n"<<endl;
//		for(i=1;i<=nos;i++)
//		cout<<i<<"th"<<endl;
//		cout<<"�ܼ�ֵΪ:"<<t[0]<<endl;
		getch();			
		return 0;
	}
}

