#include <iostream>
using namespace std;
#define MAX_CAPACITY 1001
#define MAX_NUMBER 101
class packet {
private:
	int c[MAX_NUMBER][MAX_CAPACITY] = { 0 };
	int number;
	int capacity;
	int w[MAX_NUMBER];
	int p[MAX_NUMBER];
public:
	int max(int n1, int n2) {
		if (n1 > n2) return n1;
		else return n2;
	}
	void knap() {
		for (int j = 1; j <= capacity; j++)
			for (int i = 1; i <= number; i++){
				if (j < w[i]){
					c[i][j] = c[i - 1][j];
					continue;
				}
				else c[i][j] = max(c[i - 1][j], c[i - 1][j - w[i]] + p[i]);
			}
	}
	packet() {
		cout << "��ֱ�������������������ո�ָ���:" << endl;
		cin >> capacity >> number;
		cout << "��ֱ������������������ͼ�ֵ:" << endl;
		for (int i = 1; i <= number; i++)
			cin >> w[i] >> p[i];
		knap();
		cout << "��������ֵ��Ϊ��" << c[number][capacity] << endl;

	}
};
int main() {

	packet p = packet();
	return 0;

}