#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int g_output[10000];
int text[10000];

void swap(int a[], int p, int q)
{
	int tmp;

	tmp = a[p];
	a[p] = a[q];
	a[q] = tmp;
}


int partition(int arr[], int l, int r)
{
	int pivotKey;
	int low, high, mid;

	mid = (l + r) / 2;
	// 3, 18, 45
	if ((arr[mid] - arr[l])*(arr[mid] - arr[r]) <= 0)
	{	//45, 18, 3
		swap(arr, l, mid);
	}
	//15, 4, 6
	else if ((arr[r] - arr[l])*(arr[r] - arr[mid]) <= 0)
	{	//6, 4, 15
		swap(arr, l, r);
	}

	low = l;
	high = r;
	pivotKey = arr[low];

	while (low < high) {
		while (high > low && arr[high] >= pivotKey) {
			high--;
		}
		arr[low] = arr[high];
		while (low < high && arr[low] <= pivotKey) {
			low++;
		}
		arr[high] = arr[low];
	}
	arr[low] = pivotKey;

	return low;
}

int select(int arr[], int l, int r, int k)
{
	int i;

	i = partition(arr, l, r);
	if (k == i) {
		return arr[i];
	}
	else if (k < i) {
		return select(arr, l, i - 1, k);
	}
	else {
		return select(arr, i + 1, r, k);
	}
}

int main()
{
	int n;
	int i, rel;
	printf("������Ԫ�صĸ���");
	scanf("%d", &n);
	for (i = 0; i < n; ++i) {
		scanf("%d", &g_output[i]);
		text[i] = g_output[i];
	}
	printf("��������Ҫ�ҵ�Ԫ�صĴ�С�����λ��");
	int k;
	scanf("%d", &k);
	rel = select(g_output, 0, n - 1, k-1);
	for (i = 0; i < n; ++i) {
		if (text[i] == rel)printf("λ��Ϊ%d\n", i+1);
	}
	
	printf("Ԫ��Ϊ%d", rel);
	system("pause");
}
