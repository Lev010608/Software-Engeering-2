#include<stdio.h>
#include<iostream>
using namespace std;
int number, capacity; 
int *weight;
int *value;
int currentsum = 0, resultsum = 0, space;
int *currentchoice;
int *resultchoice;
//���Ӻ��������������
void search() {
	int t;
	long times = 1;
	//���������ܴ���times
	for (int i = 0; i < number; i++)
		times *= 2;
	for (int i = 0; i < times; i++) {
		currentsum = 0;
		space = capacity;
		t = i;
		for (int j = number - 1; j >= 0; j--) {
			currentchoice[j] = t % 2;
			t = t / 2;
			if (currentchoice[j] == 1) {
				currentsum += value[j];
				space -= weight[j];
				if (space < 0) {//�������ռ䲻��ʱ
					currentsum -= value[j];
					space -= weight[j];
					break;
				}
			}
		}
		if (currentsum > resultsum) {//�Ƚ��Ƿ����ܼ�ֵ���Ľ��
			for (int i = 0; i < number; i++)
				resultchoice[i] = currentchoice[i];
			resultsum = currentsum;
		}
	}
}

int main() {
	while (true) {
		cout << "��������Ʒ�����ͱ����������ÿո�ָ�" << endl;
		cin >> number >> capacity;
		weight = new int[number + 1];
		value = new int[number + 1];
		currentchoice = new int[number + 1];
		resultchoice = new int[number + 1];
		cout << "��ֱ����������Ʒ�������ͼ�ֵ" << endl;
		for (int i = 0; i < number; i++)
			cin >> weight[i] >> value[i];

		search();
		cout << "�����������װ�ļ�ֵΪ�� " << resultsum << endl;
		cout << "�������е���Ʒ�����ֱ�Ϊ��" << endl;
		for (int i = 0; i < number; i++)
			if (resultchoice[i])
				cout << weight[i] << endl;

		delete weight;
		delete value;
		delete currentchoice;
		delete resultchoice;

		cout << "�����Ƿ�Ҫ�����µĲ�ѯ������0�˳�ϵͳ: ";
		int iscontinue;
		cin >> iscontinue;
		if (!iscontinue) break;
	}
	


	

	
	return 0;
}