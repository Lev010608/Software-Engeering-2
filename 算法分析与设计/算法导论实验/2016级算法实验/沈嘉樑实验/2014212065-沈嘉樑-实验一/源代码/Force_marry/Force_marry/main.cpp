#include<stdio.h>
#include<iostream>
using namespace std;

int positionOfLove(int number, int ftom[100][100],int indexOfFemale, int indexOfMale) {
	for (int i = 0; i < number; i++) {
		if (ftom[indexOfFemale][i] == indexOfMale) return i;
	}
	
}
int main() {
	int number;
	int mtof[100][100], ftom[100][100];
	int femaleIsMarry[100];
	int maleIsMarry[100];
	int numberOfMarried = 0;
	cout << "������������" << endl;
	cin >> number;
	for (int i = 0; i < number; i++) {
		maleIsMarry[i] = -1;
		femaleIsMarry[i] = -1;
	}

	cout << "������������Ů���ĺøжȾ���" << endl;
	for (int i = 0; i < number; i++)
		for (int j = 0; j < number; j++)
			cin >> mtof[i][j];

	cout << "������Ů���������ĺøжȾ���" << endl;
	for (int i = 0; i < number; i++)
		for (int j = 0; j < number; j++)
			cin >> ftom[i][j];
	//��������ƥ���ʱѭ���Ž���
	for (int i = 0; numberOfMarried!=number ; i++) {
		i = i % number;
		if (maleIsMarry[i]!=-1) // �������Ѿ�ƥ���˶���
			continue; 
		for (int j = 0; j < number; j++) {//���øжȴӸߵ���ƥ��
			if (*(femaleIsMarry + mtof[i][j]) == -1) {//��Ů����û�ж���ʱ
				maleIsMarry[i] = mtof[i][j];
				*(femaleIsMarry + mtof[i][j]) = i;
				numberOfMarried++;
				break;
			}
			else {//��Ů���Ѿ��ж���ʱ
				if (positionOfLove(number, ftom, mtof[i][j], i) < positionOfLove(number, ftom, mtof[i][j], *(femaleIsMarry + mtof[i][j]))) {//�Ƚ����������ĺøж�
					*(maleIsMarry + *(femaleIsMarry + mtof[i][j])) = -1; 
					*(femaleIsMarry + mtof[i][j]) = i;
					maleIsMarry[i] = mtof[i][j];
					break;
				}
			}
		}
	}
	cout << "����Ȣ��Ů����" << endl;
	for (int i = 0; i < number; i++)
		cout << maleIsMarry[i] << endl;

	cout << "Ů���޵��к���" << endl;
	for (int i = 0; i < number; i++)
		cout << femaleIsMarry[i] << endl;



	return 0;
}
