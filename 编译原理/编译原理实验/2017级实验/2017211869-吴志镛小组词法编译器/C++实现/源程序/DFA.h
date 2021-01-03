#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

class DFA
{
public:

	FILE *infile, *outfile;
	char GetChar();
	void GetBC();//���ch���ַ��Ƿ�հ� ���Ǽ�������GetChar()ֱ���ǿ�
	void Concat(char ch); //��ch�е��ַ����ӵ�strToken��
	int IsLetter(char ch); //�жϵ�ǰ�ַ��Ƿ�Ϊ��ĸ 
	int IsDigit(char ch); //�жϵ�ǰ�ַ��Ƿ�Ϊ���� 
	int IsBound(char ch); //�жϵ�ǰ�ַ��Ƿ�Ϊ�ֽ�� 
	void Retract();  //strToken���ˣ���ch�ÿ� 
	int KeyList(char strToken[]); //�ж�strToken���Ƿ�Ϊ�ؼ���
	DFA();
	~DFA();
	char getCH();
	int getpos();

private:
	char strToken[100];   //��Ź��ɵ��ʷ��ŵ��ַ��� 
	char ch;    //������¶�����Դ�����ַ� 
	int pos = 0;  //��ǰ�ַ�����λ��ָ�� 
	int numberOflines = 1; //ͳ������ 
	int numberOfwords = 0; //ͳ��Դ�����е��ʸ���,���Ϳո񲻼�Ϊ���� 
	int numberOfchars = -1; //ͳ��Դ�������ַ����� Ҫȥ��EOF 


};
