#include<stdlib.h>
#include <stdio.h>
int goods[4];//ԭ������goods[1/2/3]


int flag[3];//�������Խ�goods[1/2/3]��Ϊ�м����ת���flag
			

int w[3] = { 20,15,10 };//��Ʒ����
int v[3] = { 20,30,25 };//��Ʒ��ֵ
int c = 25;//��������
int value = 0;//������һ�ڵ���ܼ�ֵ
int weight = 0;//������һ�ڵ��������
int k = 0;//������
void Select(int a)
{
	int i = 0;
	if (weight > c) return;
	if (value > goods[0])
		//��Ϊ������Ǹ�ѭ�������ȫѭ�����֮��
		//�Ὣvalue��goods��־λ�ټ���0 
		//����Ҫ�ڱȵ�ǰ���Ż��ŵ�ʱ���ȼ�¼���� 
	{
		goods[0] = value;
		for (int j = 0; j < 3; j++)
		{
			if (goods[j + 1]) flag[j] = 1;
		}
	}

	for (i = a; i <= 3; i++)
		//һ������value��goods���ó�0��
		//�Ͼ�������ô�Գƣ��ȼӺ�� 
		//���ѭ�������ĵط����ǽ�Select(a)��a��Ϊ
		//��ѭ��������i�ĳ�ֵ�������Ϳ���ֱ�Ӵ���һ���ڵ㿪ʼ��
		//�������ڴ˽ڵ����һ���ڵ㱻��֦������ʱ��
		//����ʱ�Ϳ���ֱ�ӽ�a�ڵ���˷�����һ�� 
	{
		value += v[i];
		weight += w[i];
		goods[i + 1] = 1;

		Select(i + 1);

		value -= v[i];
		weight -= w[i];
		goods[i + 1] = 0;
	}

}
void Print()
{
	printf("ѡ�����Ʒ�ǣ�\n");
	for (int j = 0; j < 3; j++)
	{
		if (flag[j])
			printf("��Ʒ%d ", j + 1);
	}
	printf("\n�ܼ�ֵ��%d", goods[0]);
}
int main()
{
	Select(k);
	Print();
	system("pause");
}
