/*
�������й�ϵ�����У�0��ʾ����֮�������ߣ�1��ʾ������
�ó����ܹ�������е�ȡɫ����
*/
#include<stdio.h>
#include<iostream>
using namespace std;

int relation[100][100], color[100], m, number, numOfResult;

bool isOk(int k) {//�ж��Ƿ��г�ͻ
	for (int j = 1; j <= number; j++)
		if (relation[k][j] && (color[j] == color[k]))
			return false;
	return true;
}

void draw(int index) {
	if (index > number) {
		numOfResult++;
		for (int i = 1; i <= number; i++) {
			cout << color[i] << " ";
		}
		cout << endl;
		return;
	}
	for (int i = 1; i <= m; i++) {
		color[index] = i;
		if (isOk(index)) {
			draw(index + 1);
		}
		color[index] = 0;
	}
}

int main() {
	cout << "�������ĸ���:" << endl;
	cin >> number;
	cout << "�������֮��Ĺ�ϵ����:" << endl;
	for (int i = 1; i <= number; i++)
		for (int j = 1; j <= number; j++) {
			cin >> relation[i][j];
		}
	cout << "��ռ�Ϊ:" << endl;

	for (int i = 1; i <= 10; i++) {
		m = i;
		numOfResult = 0;
		draw(1);
		if (numOfResult != 0) {
			cout << "������Ҫ����ɫ����Ϊ:" << m << endl;
			cout << "��ɫ��������Ϊ:" << numOfResult << endl;
			break;
		}
	}

	return 0;
}
