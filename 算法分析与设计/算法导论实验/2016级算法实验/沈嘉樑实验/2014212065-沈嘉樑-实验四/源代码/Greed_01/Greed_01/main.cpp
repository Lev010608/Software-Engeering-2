#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
struct package {
	double v, w;       
	bool operator  < (const package &rhs)const {      
		return v / w > rhs.v / rhs.w;
	}
}bag[500];
int main() {
	int p = 0, n;
	double C, cur = 0, ans = 0;
	cout << "\n�����뱳�������������";
	cin >> C;
	cout << "��������Ʒ�ĸ�����";
	cin >> n;
	cout << "��ֱ�������Ʒ�������������" << endl;
	for (int i = 0; i < n; i++) {
		cin >> bag[i].w;
		cin >> bag[i].v;
	}
	sort(bag, bag + n);
	while (p < n) {
		if (cur + bag[p].w <= C) {
			cur += bag[p].w;
			ans += bag[p].v;
			cout << "ѡȡ��ֵΪ" << bag[p].v << "����Ʒ,��ȡ����Ϊ��" << bag[p].w << endl;
			p++;
		}
		else {
			ans += bag[p].v / bag[p].w * (C - cur);
			cout << "ѡȡ��ֵΪ" << bag[p].v << "����Ʒ,��ȡ����Ϊ��" << (C - cur) << endl;
			break;
		}
	}
	cout << "\n����ֵΪ��" << ans << endl;
	return 0;
}