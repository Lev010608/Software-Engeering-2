#include<stdio.h>
#include<iostream>
int number, capacity;
int *weight;
int *value;
int sum = 0, result = 0;
int *choice;
int *resultchoice;
using namespace std;

void bubble(int number) {
	int temp;
	for (int i = 0; i < number - 1; i++)
		for (int j = i + 1; j < number;j++)
			if (weight[j]>weight[i]) {
				temp = weight[i];
				weight[i] = weight[j];
				weight[j] = temp;
				temp = value[i];
				value[i] = value[j];
				value[j] = temp;
			}
}

void put(int index, int space) {
	if (index == number - 1 || space < weight[number-1])
		if (sum > result) {
			for (int i = 0; i < number;i++)
				resultchoice[i] = choice[i];
			result = sum;
		}
		else return;
	for (int i = index+1; i < number; i++) {
		if (weight[i] <= space) {
			choice[i] = 1;
			sum += value[i];
			put(i, space - weight[i]);
			sum -= value[i];
			choice[i] = 0;
		}
		else {
			choice[i] = 0;
			put(i, space);
		}
	}
}


int main() {
	cout << "���������뱳���������ͱ������������ÿո�ָ���" << endl;
	cin >> number >> capacity;
	weight = new int [number + 1];
	value  = new int [number + 1];
	choice = new int[number + 1];
	resultchoice = new int[number + 1];

	for (int i = 0; i < number; i++)
		choice[i] = 0;
	cout << "���������������Ʒ�������ͼ�ֵ���ÿո�ָ���" << endl;
	for (int i = 0; i < number; i++)
		cin >> weight[i] >> value[i];

	bubble(number);

	put(-1, capacity);

	cout << "����ֵΪ�� " << result << endl;
	cout << "ѡ�����ƷΪ(1��ʾѡ��0��ʾ��ѡ)��" << endl;
	for (int i = 0; i < number; i++)
		cout << weight[i] << ':' << resultchoice[i] << endl;

	delete weight;
	delete value;
	delete choice;
	delete resultchoice;
	return 0;
}