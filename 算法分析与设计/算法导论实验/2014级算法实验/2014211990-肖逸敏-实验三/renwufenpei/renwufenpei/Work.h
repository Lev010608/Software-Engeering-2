#if !defined(AFX_WORK_H__FFC92D1D_03FB_4BE1_AE4E_6B64ADF7D9C0__INCLUDED_)
#define AFX_WORK_H__FFC92D1D_03FB_4BE1_AE4E_6B64ADF7D9C0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class Work
{
	int n;
	int **c;
	int *work;  //�洢��ǰ���˵ķ���
	int *tmp;
	int cc, minc, highest;
	void swap(int &a, int &b);
	void init(); //��ʼ��+���ļ��ж�ȡ����
	void showArray();
	void show();
	int getHighest(); //�����Ͻ�
public:
	int count; //���ڼ�¼�ݹ����
	Work();
	virtual ~Work();
	void find(int i);   //��֧���޷�
	void output();    //�������ʱ��
};

#endif // !defined(AFX_WORK_H__FFC92D1D_03FB_4BE1_AE4E_6B64ADF7D9C0__INCLUDED_)
