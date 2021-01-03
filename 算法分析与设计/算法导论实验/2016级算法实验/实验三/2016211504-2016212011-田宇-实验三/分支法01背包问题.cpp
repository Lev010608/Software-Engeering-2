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
struct node
{
	//����Ľ�����ݽṹ
	node  *parent,//�����ָ��
	      *next; //��̽��ָ��
	int    level,//���Ĳ�
	       bag,//�ڵ�Ľ�
	       cw,//��ǰ����װ����
	       cp;//��ǰ������ֵ
	float  ub; //�����Ͻ�ֵ
};
class Knap
{
	private:
		struct    node      *front, //���ж���
				*bestp,*first; //���㡢�����
		int       *p,*w,n,c,*M;//������ֵ����������Ʒ����������������¼��С˳���ϵ
		long      lbestp;//�����������Ž�
	public:
		void Sort();
		Knap(int *pp,int *ww,int cc,int nn);
		~Knap();
		float Bound(int i,int cw,int cp);//�����Ͻ���
		node *nnoder(node *pa,int ba,float uub);//����һ����� ba=1������ڵ� ba=0�����ҽڵ�
		void addnode(node *nod);//�������ӵ�������
		void deletenode(node *nod);//����������ɾ��
	struct node *nextnode(); //ȡ��һ��
		void display(); //������
		void solvebag(); //�����������
};

Knap::Knap(int *pp,int *ww,int cc,int nn)
{
	int i;
	n=nn;
	c=cc;
	p=new int[n];
	w=new int[n];
	M=new int[n];
	for(i=0; i<n; i++)
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
Knap::~Knap()
{
	delete []first;
	delete []front;
	delete []bestp;
	delete []p;
	delete []w;
}
float Knap::Bound(int i,int cw,int cp)
{
	// �����Ͻ�
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
node * Knap::nnoder(struct node *pa,int ba,float uub)
{
	//����һ���½��
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

void Knap::addnode(node *no)
{
	//�����������ȶ���
	node *p=front->next,*next1=front;
	float ub=no->ub;
	while(p!=NULL)
	{
		if(p->ub<ub)
		{
			no->next=p;
			next1->next=no;
			break;
		}
		next1=p;
		p=p->next;
	}
	if(p==NULL)
	{
		next1->next=no;
	}
}

node *Knap::nextnode()
{
	//ȡ���������
	node *p=front->next;
	front->next=p->next;
	return(p);
}

void Knap::Sort()
{
	int i,j,k,kkl;
	float minl;
	for(i=1; i<n; i++)
	{
		minl=1.0*p[i]/w[i];
		k=0;
		for(j=1; j<=n-i; j++)
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

void Knap::display()
{
	int i;
	for(i=n; i>=1; i--)
	{
		x[M[i-1]]=bestp->bag;
		bestp=bestp->parent;
	}
	cout<<"����ѡ���⼸����Ʒ��������м�ֵ���Ӽ�: "<<endl;
	for(i=1; i<=n; i++)
	{
		if(x[i-1])
			cout<<i<<"th"<<endl;
	}

	cout<<"�ܼ�ֵΪ:"<<lbestp<<endl;
}

void Knap::solvebag()
{
	//�����������
	int i;
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
	display();
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
	for(i=0; i<n; i++)
		cin>>w[i];
	cout<<"������"<<n<<"����Ʒ��ֵ:"<<endl;
	for(i=0; i<n; i++)
		cin>>p[i];
	x=new int[n];
	Knap knbag(p,w,c,n);
	knbag.solvebag();
	getch();
	return 0;
}

