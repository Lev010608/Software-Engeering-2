#include <stdio.h>
#include <tchar.h>
#include <queue>
#include "iostream"
using namespace std;
int N;
int s[100];
int t[100];
int solve()
{
	int temp;
	for (int i = 0; i < N; i++) {
		for (int j = i + 1; j < N; j++)
			if (t[i]>t[j]) {
				temp = s[i];
				s[i] = s[j];
				s[j] = temp;
				temp = t[i];
				t[i] = t[j];
				t[j] = temp;
			}
	}
	int count = 0;
	int time = 0;
	for (int i = 0; i < N; i++) {
		if (time <= s[i]) {
			count++;
			time = t[i];
			cout << "ѡ��ʼʱ��Ϊ" << s[i] << "������ʱ��Ϊ" << t[i] << endl;
		}
	}
	return count;
}
int main() {
	cout << "������һ���ж��ٸ���������";
	cin >> N;
	cout << "��ֱ�����ÿ���������Ŀ�ʼ�ͽ���ʱ�䣺" << endl;
	for (int i = 0; i < N; i++)
		cin >> s[i] >> t[i];
	int num = solve();
	cout << "����Ϊ��" << num << endl;
	return 0;
}