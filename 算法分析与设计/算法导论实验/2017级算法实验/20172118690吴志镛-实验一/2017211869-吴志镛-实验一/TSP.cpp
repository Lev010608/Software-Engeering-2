#include<iostream>
#include<cstring>
#include<algorithm>
#include<vector>
#include<cstdio>
#include<cmath>
#include<string>
#define LL long long 
#define n 4 
using namespace std;
int main() {
	int i, k, j, l;
	int s[n];  //���ڴ洢�ѷ��ʹ��ĳ��� 
	int D[n][n]; //���ڼ�¼��������֮��ľ��� 
	int sum = 0; //���ڼ����ѷ��ʹ��ĳ��е���С·������ 
	int Dtemp;//��֤Dtemp������������������֮��ľ��붼�� 
	int flag;//��Ϊ���ʵı�־���������ʹ���Ϊ1����δ�����ʹ���Ϊ0 
	i = 1;//i�������Ѿ����ʹ��ĳ��� 
	s[0] = 0;
	D[0][1] = 3; D[0][2] = 6; D[0][3] = 7; D[1][0] = 12;
	D[1][2] = 2; D[1][3] = 8; D[2][0] = 8; D[2][1] = 6;
	D[2][3] = 2; D[3][0] = 3; D[3][1] = 7; D[3][2] = 6;

	do {
		k = 1;      //�ڼ���λ�� 
		Dtemp = 10000;
		do {
			l = 0; flag = 0;
			do {
				if (s[l] == k) { //�жϸó����Ƿ񱻷��ʹ��� 
					flag = 1;
					break;
				}
				else {
					l++;
				}
			} while (l < i);
			if (flag == 0 && D[k][s[i - 1]] < Dtemp) {
				j = k; //j���� �洢�Ѿ����ʹ��ĳ��� 
				Dtemp = D[k][s[i - 1]];
			}
			k++;
		} while (k < n);
		s[i] = j;  //���ѷ��ʹ��ĳ��д洢���� 
		i++;
		sum += Dtemp; //���������֮�����̾��� 
	} while (i < n);
	sum += D[0][j];//D[0][j]Ϊ���������ڵ����һ������ 
	cout << "���ξ����� ���к�Ϊ";
	for (j = 0; j < n; j++) {
		cout << s[j]+1 << " ";
	}
	cout << "\n"<<"�ܵ����·��Ϊ" << sum<<endl;
	system("pause");
}
