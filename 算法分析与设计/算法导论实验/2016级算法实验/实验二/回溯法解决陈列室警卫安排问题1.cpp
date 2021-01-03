#include<fstream>
#include<iostream>
using namespace std;

ifstream fin ("input.txt");
ofstream fout("output.txt");

class Exhibit_hall{
	friend void Setrobot(int ,int);
	
private:
	void set(int i,int j,int a[]);//���û�����
	void recover(int i,int j,int a[]);
	void Backtrack(int i,int j);
	void GreedySearch();	//̰������
	int search(int i,int j);	//������a[i][j]�����û�����ʱ�����ලδ���ල�ĳ����Ҹ���
	void set(int i,int j);		
	int m,n;	//���йݵ�����,����
	int mn;		//�����Ҹ���
	int g_num;	//���������ѱ����ӵĸ���
	int num;	//��ǰ�����˸���
	int num1;	//����̰�������л����˵ĸ���
	int **x;	//��ǰ��
	int bestn;	//��ǰ���Ž�ĸ���
	int **bestx;//��ǰ���Ž�
};


void Exhibit_hall::set(int i,int j,int a[])//x[][]Ϊ1��ʾ�˷����ѷ�����һ�������ˣ�Ϊ2��ʾ�˷����ѱ�����
{
	num++;
	a[0]=x[i][j];
	if(a[0]==0) g_num++;//���˳�����δ�����ӣ����ʱ�ѱ�����g_num++
	x[i][j]=1;//��λ�÷�����һ��������
	if(x[i-1][j]==0) {a[1]=1;x[i-1][j]=2;g_num++;}//���Ϸ�δ������,���ʱ����δ�ѱ�����
	if(x[i][j+1]==0) {a[2]=1;x[i][j+1]=2;g_num++;}
	if(x[i+1][j]==0) {a[3]=1;x[i+1][j]=2;g_num++;}
	if(x[i][j-1]==0) {a[4]=1;x[i][j-1]=2;g_num++;}
}
	
void Exhibit_hall::recover(int i,int j,int a[])//����������
{
	num--;
	x[i][j]=a[0];
	if(a[0]==0) g_num--;

	if(a[1]) {x[i-1][j]=0;g_num--;}
	if(a[2]) {x[i][j+1]=0;g_num--;}
	if(a[3]) {x[i+1][j]=0;g_num--;}
	if(a[4]) {x[i][j-1]=0;g_num--;}
	a[0]=0;a[1]=0;a[2]=0;a[3]=0;a[4]=0;
}


void Exhibit_hall::Backtrack(int i,int j)//����
{
	if(i>m){
		if(num<bestn)
		{
			for(int k=1;k<m+1;k++)
				for(int l=1;l<n+1;l++)
					bestx[k][l]=x[k][l];
			bestn=num;
		}
		return;
	}

	if(num+(mn-g_num)/5>=bestn) return;

	//���˳������ѱ����ӣ���û��Ҫ�ڴ˳����ҷ����þ���������
	//��Ϊx[i+1][j+1]����һ���������ڴ˴��Ż�����

	if(x[i][j]!=0)
		Backtrack(i+j/n,j%n+1);

	//�ڴ˳����ұ�����
	else
	{
		int a[5]={0};
		if(i<m)		//�ڴ˳�����������û����˼��Ӵ˳�����
		{
			set(i+1,j,a);
			Backtrack(i,j);
			recover(i+1,j,a);
		}
		if((j<n) && (x[i][j+1]==0||x[i][j+2]==0))		//�ڴ˳������ұ߷��û����˼��Ӵ˳�����
		{
			set(i,j+1,a);
			Backtrack(i,j);
			recover(i,j+1,a);
		}
		if(x[i+1][j]==0&&x[i][j+1]==0)		//�ڴ˳����ҷ��û�����
		{
			set(i,j,a);
			Backtrack(i,j);
			recover(i,j,a);
		}
	}
}
int Exhibit_hall::search(int i,int j)
{
	if(i==m+1||j==n+1) return 0;
	int count=0;
	if(x[i][j]==0)count ++;
	if(x[i-1][j]==0)count ++;
	if(x[i][j+1]==0)count ++;
	if(x[i+1][j]==0)count ++;
	if(x[i][j-1]==0)count ++;
	return count;
}
void Exhibit_hall::set(int i,int j)
{
	num1++;
	x[i][j]=1;

	if(x[i-1][j]==0)x[i-1][j]=2;
	if(x[i][j+1]==0)x[i][j+1]=2;
	if(x[i+1][j]==0)x[i+1][j]=2;
	if(x[i][j-1]==0)x[i][j-1]=2;
}
	
void Exhibit_hall::GreedySearch()
{
	for(int i=1;i<=m;i++)
		for(int j=1;j<=n;j++)
		{
			if(x[i][j]==0)
			{
				int a1=0,a2=0,a3=0;
				a1=search(i,j);
				a2=search(i+1,j);
				a3=search(i,j+1);
				if(a1>=a2&&a1>=a3)set(i,j);
				else{
					if(a2>=a3)
					{
						if(a2>a3)set(i+1,j);
						else 
							if(x[i+1][j]!=0&&x[i][j+1]==0)set(i,j+1);
							else set(i+1,j);
					}
					else set(i,j+1);
				}
			}
		}
	for(int i=1;i<=m;i++)
		for(int j=1;j<=n;j++)
		{
			bestx[i][j]=x[i][j];
			x[i][j]=0;
		}
	bestn=num1;
}
				
				

void Setrobot(int m,int n)
{
	Exhibit_hall Ex;
	Ex.m=m;
	Ex.n=n;
	Ex.mn=m*n;
	Ex.num=0;
	Ex.num1=0;
	Ex.bestn=m*n;
	Ex.g_num=0;
	Ex.x=new int*[m+2];
	for(int i=0;i<m+2;i++)
	{
		Ex.x[i]=new int[n+2];
		for(int j=0;j<n+2;j++)Ex.x[i][j]=0;
	}

	Ex.bestx=new int*[m+2];
	for(int i=0;i<m+2;i++)
	{
		Ex.bestx[i]=new int[n+2];
		for(int j=0;j<n+2;j++)Ex.bestx[i][j]=0;
	}
	for(int k=0;k<n+2;k++){Ex.x[0][k]=2;Ex.x[m+1][k]=2;}
	for(int k=1;k<m+1;k++){Ex.x[k][0]=2;Ex.x[k][n+1]=2;}
	
	Ex.GreedySearch();

	cout<<Ex.bestn<<endl;

	Ex.Backtrack(1,1);

	fout<<Ex.bestn<<endl;
	for(int j=1;j<=m;j++){
		for(int k=1;k<=n;k++)
		{
			if(Ex.bestx[j][k]==1)fout<<1<<' ';
			else fout<<0<<' ';
		}
		fout<<endl;
	}	
	delete [] Ex.x;
	delete [] Ex.bestx;
}
int main()
{
	int m,n;
	fin>>m>>n;
	Setrobot(m,n);
}


