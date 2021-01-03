#include <iostream>
#define MaxSize 100
using namespace std;

//����ʹ�ö�λ���ݽ����Թ�����:0��ʾͨ·��1��ʾǽ 
int maze[10][10] =        //�Թ��ڼ�����е�����洢��ʽ
{
   {1,1,1,1,1,1,1,1,1,1},
   {1,0,0,1,1,0,1,1,0,1},
   {1,0,0,1,0,0,0,1,0,1},
   {1,0,0,0,0,1,1,0,0,1},
   {1,0,1,1,1,0,0,1,1,1},
   {1,0,0,0,1,0,0,0,0,1},
   {1,0,1,0,0,0,1,0,0,1},
   {1,0,1,1,1,0,1,1,0,1},
   {1,0,0,1,1,0,0,1,0,1},
   {1,1,1,1,1,1,1,1,1,1}
};

//����˳��ջ,���ڴ洢��ǰ��λ����Ϣ����һ���ķ��� 
struct Try
{
	int i;
	int j;
	int d;
}path[MaxSize];
int top = -1;    //��ʼ��ջָ�� 

void FindPath(int xb, int yb, int xe, int ye)
{
	//�����ջ
	top++;
	path[top].i = xb;
	path[top].j = yb;
	path[top].d = -1;
	maze[xb][yb] = -1;    //������     
	int i, j, k, d, find;    //ӳ����������ı��� 
	while (top > -1)
	{
		i = path[top].i;
		j = path[top].j;
		d = path[top].d;
		if (i == xe && j == ye)
		{
			cout << "�Թ�·�����£�" << endl;
			for (k = 0; k <= top; k++)
			{
				cout << "(" << path[k].i << "," << path[k].j << ") ";    //��������ջ����ջ�׿�ʼ��� 
				if ((k + 1) % 5 == 0) cout << endl;    //ÿ������������ 
			}
			cout << endl;
			return;
		}
		find = 0;
		while (d < 4 && find == 0)    //ѭ���ж���������ÿһ����������������1ֱ����ջ����1�ٴ�ѭ����ѭ���Ĵζ���1��ջ 
		{
			d++;
			switch (d)
			{
			case 0:
				i = path[top].i - 1;
				j = path[top].j;
				break;
			case 1:
				i = path[top].i;
				j = path[top].j + 1;
				break;
			case 2:
				i = path[top].i + 1;
				j = path[top].j;
				break;
			case 3:
				i = path[top].i;
				j = path[top].j - 1;
				break;
			}
			if (maze[i][j] == 0) find = 1;
		}
		if (find == 1)
		{
			path[top].d = d;
			top++;
			path[top].i = i;
			path[top].j = j;
			path[top].d = -1;
			maze[i][j] = -1;    //���ÿһ��ͨ·Ϊ-1����ֹԭ·���أ������ջ����Ӧ��-1��Ϊ0 
		}
		else
		{
			maze[path[top].i][path[top].j] = 0;
			top--;
		}
	}
	cout << "��·���ߣ�" << endl;
}

void PrintMaze()
{
	cout << "������·�����Թ���" << endl;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			printf("%3d", maze[i][j]);
		}
		cout << endl;
	}
}

int main()
{
	FindPath(1, 1, 8, 8);
	PrintMaze();
	system("pause");
}