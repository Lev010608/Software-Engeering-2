 #include<cstdio>
#include<cstdlib>
#include<iostream>
using namespace std;
#define MAX = 1000;
int d[6][3] = { {0,0,0}, {0,0,0}, {0,0,-1}, {0,-1,0}, {0,0,1}, {0,1,0} };
int x[100][100];
int y[100][100];
int bestx[100][100];    //x�������õ�ǰ������y������ʾ��������bestx�������ս��
int n, m, best, k = 0, t = 0;   //��ǰ�����õľ�����Ϊk���ܼ��ӵĳ�������Ϊt����ǰ���پ�����Ϊbest
int t1, t2, more;               //�ж��½��֦����������
bool p;


void change(int i, int j) {    //��(i, j)������һ�����������ı�����Χ�ܼ�����
	x[i][j] = 1;
	k++;
	for (int r = 1; r <= 5; r++) {    //���Լ������������������ط������ܿ�
		int p = i + d[r][1];
		int q = j + d[r][2];
		y[p][q]++;
		if (y[p][q] == 1)
			t++;
	}
}
void restore(int i, int j) {    //������(i, j)�����õľ��������ı�����Χ�ܼ�����
	x[i][j] = 0;
	k--;
	for (int r = 1; r <= 5; r++) {
		int p = i + d[r][1];
		int q = j + d[r][2];
		y[p][q]--;
		if (y[p][q] == 0)
			t--;
	}
}
void search(int i, int j) {   //��������
	do {                             //���ϵ��£�������������û����ص�λ��
		j++;
		if (j > m) {
			i++;
			j = 1;
		}
	} while (!((y[i][j] == 0) || (i > n)));
	if (i > n) {
		if (k < best) {            //ˢ�¾���ֵ
			best = k;
			for (int p = 1; p <= n; p++)
				for (int q = 1; q <= m; q++)
					bestx[p][q] = x[p][q];
			return;
		}
	}
	if (k + (t1 - t) / 5 >= best)    return;            //�������½� = �������õ����پ����� + ���еľ�����
	if ((i < n - 1) && (k + (t2 - t) / 5 >= best))    return;   //��������ž�������Ļ����ͼ�ȥ��һ��֦
	if (i < n) {                //���p
		change(i + 1, j);
		search(i, j);            //�ݹ�������һ����
		restore(i + 1, j);        //�ָ�
	}
	if (y[i][j + 1] == 0) {        //���q
		change(i, j);
		search(i, j);
		restore(i, j);
	}
	if ((j < m) && ((y[i][j + 1] == 0) || (y[i][j + 2] == 0))) {    //���r
		change(i, j + 1);
		search(i, j);
		restore(i, j + 1);
	}
}

void compute() {
	more = m / 4 + 1;
	if (m % 4 == 3)
		more++;
	else if (m % 4 == 2)
		more += 2;
	t2 = m * n + more + 4;
	t1 = m * n + 4;
	best = 65536;
	if (m == 1 && n == 1) {
		cout << "1" << endl;
		cout << "1" << endl;

	}
	for (int i = 0; i <= m + 1; i++) {    //�������������һȦ�����ڴ���߽����
		y[0][i] = 1;
		y[n + 1][i] = 1;
	}
	for (int i = 0; i <= n + 1; i++) {
		y[i][0] = 1;
		y[i][m + 1] = 1;
	}
	search(1, 0);
}

/**
 * �����������й����⣨���ݷ���
 */
int main() {
	printf("�����ó��й�����: \n");
	printf("m: ");
	cin >> m;
	printf("n:");
	cin >> n;
	compute(); //����
	cout << "������Ҫ" << best << "������" << endl;

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++)
			cout << bestx[i][j] << " ";
		printf("\n");
	}
	system("pause");
}