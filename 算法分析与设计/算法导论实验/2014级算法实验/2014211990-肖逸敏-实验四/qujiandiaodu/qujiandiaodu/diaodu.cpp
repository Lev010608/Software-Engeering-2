#include<iostream>
#include<algorithm>

using namespace std;

const int MAX = 100000;

int N, s[MAX], t[MAX];//���룬s��ʼʱ�䣬t����ʱ��

pair<int, int> itv[MAX];//���ڶԹ��������pair����

int main()
{
	cout << "���빤����N��";
	cin >> N;
	cout << endl;

	cout << "���뿪ʼʱ��ͽ���ʱ�䣺" << endl;
	int i;
	for (i = 0; i<N; i++)
		cin >> itv[i].second >> itv[i].first;//�����Խ���ʱ���������ԸĴ�˳��
	cout << endl;
	sort(itv, itv + N);

	int ans = 0, t = 0;
	for (i = 0; i < N; i++){
		if (t < itv[i].second){
			ans++;
			t = itv[i].first;
		}
	}
	cout << "���Ĺ�����";
	cout << ans << endl;

	system("pause");
	return 0;
}