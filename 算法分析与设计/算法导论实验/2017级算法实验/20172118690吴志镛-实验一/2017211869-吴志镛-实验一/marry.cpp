
#include<iostream>
#include <stack>

using namespace std;

#define NUM 4
#define NIL -1

int GetPositionFromLaday(int ladayArray[][NUM], int laday, int man)
{
	for (int i = 0; i < NUM; i++)
		if (ladayArray[laday][i] == man)
			return i;
	return NIL;
}

void ChoosePartener(stack<int>& manStack, int manPos, int manArray[][NUM], int ladayArray[][NUM], int manPerfer[], int manStartPos[], int ladayNow[])
{
	//ѡ���Լ�������������λ��Ů��
	int perferLaday = manArray[manPos][manStartPos[manPos]];
	//�����Ů��û�н��ܹ���ף�����ܸ��к��ı��
	if (ladayNow[perferLaday] == NIL)
	{
		ladayNow[perferLaday] = manPos;
		manPerfer[manPos] = perferLaday;
	}
	//����Ѿ�����������ף����ж�������ӵ�е���û������׷��ĺ�
	else
	{
		int oldPos = GetPositionFromLaday(ladayArray, perferLaday, ladayNow[perferLaday]);
		int newPos = GetPositionFromLaday(ladayArray, perferLaday, manPos);
		if (oldPos < newPos)
		{
			manStartPos[manPos]++;//˵����Ů����ϲ������ӵ�еģ�ѡ��Ŀ�еڶ�λ
			//���뵥������
			manStack.push(manPos);
		}
		else //������
		{
			//��˦�����ѻָ��������
			manStartPos[ladayNow[perferLaday]]++;
			//���뵥������
			manStack.push(ladayNow[perferLaday]);
			//��׷�����ʿ��Ϊ��������
			ladayNow[perferLaday] = manPos;
			manPerfer[manPos] = perferLaday;
		}
	}
}

int main()
{
	int manArray[NUM][NUM] = { {2,3,1,0},{2,1,3,0},{0,2,3,1},{1,3,2,0} };
	int ladayArray[NUM][NUM] = { {0,3,2,1},{0,1,2,3},{0,2,3,1},{1,0,3,2} };

	int manPerfer[NUM] = { 0 };//ÿλ����ѡ�е�Ů��
	int manStartPos[NUM] = { 0 };//��¼ÿλ����ѡȡ������Ŀ�еڼ�λ��Ů��
	int ladayNow[NUM] = { NIL,NIL,NIL,NIL };//Ů����Ӧ������

	stack<int> manStack; // �����ڵ������ʿ

	//���е�һ�ֵ�����ÿ��������ѡ���Լ�������������λ��Ů����
	for (int pos = 0; pos < NUM; pos++)
	{
		ChoosePartener(manStack, pos, manArray, ladayArray, manPerfer, manStartPos, ladayNow);
	}

	while (manStack.size() != 0)
	{
		int manPos = manStack.top();
		manStack.pop();
		ChoosePartener(manStack, manPos, manArray, ladayArray, manPerfer, manStartPos, ladayNow);
	}

	for (int i = 0; i < NUM; ++i)
		cout << "Man NO.: " << i << " Laday NO.: " << manPerfer[i] << endl;

	system("pause");
}


