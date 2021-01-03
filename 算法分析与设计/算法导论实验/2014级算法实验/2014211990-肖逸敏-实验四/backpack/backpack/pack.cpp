#include <iostream>
using namespace std;
typedef struct 
{ 
	int v; 
	int w;
	float pv;
}pvu; 

void sortByPv(pvu[], int);
int   zeroneBags(pvu[], int, int, int *); 
void print(pvu a[], int n) 
{ 
	for (int i = 0; i<n; i++) 
	{ 
		cout << a[i].w << " " << a[i].v << " " << a[i].pv << endl;
	} 
	cout << endl;
}

int main() {

	int remained=0;
	int i, maxw;  
	int w[] = { 1, 2, 3, 2 }; 
	int v[] = { 9, 10, 15, 6 }; 
	int n = sizeof(w) / sizeof(int);  
	int N = n;
	pvu arr[30]; 
	for (i = 0; i<n; i++) 
	{ 
		arr[i].v = v[i]; 
		arr[i].w = w[i];
		arr[i].pv = v[i] * 1.0 / w[i];
	} 
	cout << "��֪��Ʒ�������ֱ�Ϊ1��2��3��2" << endl;
	cout << "��Ʒ�ļ�ֵ�ֱ�Ϊ9��10��15��6" << endl;
	cout << "���뱳������������:\n"; 
	cin >> maxw; 
	cout << "����ֵΪ:" << zeroneBags(arr, n, maxw, &remained) << "\n��ʣ" << remained << "�ռ�δʹ��" << endl;
	return 0;
}
void sortByPv(pvu arr[], int n)
{ 
	pvu t;  
	int i, j; 
	for (i = 0; i<n - 1; i++)
		for (j = 0; j<n - 1 - i; j++)     
			if (arr[j].pv<arr[j + 1].pv)  
			{
		t = arr[j];  
		arr[j] = arr[j + 1];   
		arr[j + 1] = t;
			} 
}
int   zeroneBags(pvu arr[], int n, int maxw, int *e)
{
	int i = 0, j, minw, totalv = 0;
	int avail = maxw; 
	sortByPv(arr, n); //�����λ������ֵPV�Ӵ�С������ 
	while (avail&&i<n) 
	{ 
		minw=i; 
		for (j=0;j<n;j++) 
			if (arr[i].pv==arr[j].pv) 
			{ 
			if (arr[i].w>arr[j].w&&j>i)  
			{  
				minw=j;  
			} 
			}  
		if (arr[minw].w<=avail) 
		{   
			avail-=arr[minw].w;  
			totalv+=arr[minw].v; 
			i++;  
		} 
		else  
			i++; 
	} 
	*e = avail; 
	return totalv;
}