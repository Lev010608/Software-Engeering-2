#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<fstream>
#include<string.h>

using namespace std;

int wordNum=0;//������
int characterNum=0;//�ַ���
int lineNum=1;//����
int errorNum = 0;//������
int errorLine[100];//��������Ϣ

void scanner()
{
	ifstream output;
    output.open("input.txt");//��ȡ�ļ�
	char structer[11][10] = { "if", "else", "for", "return", "switch", "case", "break", "continue", "while", "do" ,"goto"};//�����ṹ
	char dataType[14][10] = { "int", "char", "float", "double", "void","signed","unsigned","short","long","static","struct","union","typedef","volatile" };//��������
	char preDeal[2][10] = { "include", "define" };//Ԥ�������
	char word[30] = { '\0' };
	int i = 0;//ɨ���������±�
	bool k = false;//��¼����״̬
	int a = 0;//ɨ��С��ʱѭ���Ŀ��Ʊ���
	int b = 0;//ɨ��ע��ʱѭ���Ŀ��Ʊ���
	int state = 1;//ѭ����case��Ĭ��ȡֵ
	char ch;
	ch = output.get();
	characterNum++;

	while (ch != '$')//δ����
	{
		//�����ַ��Ƿָ���
		if (ch == '\n' || ch == ' ' || ch == '\0' || ch == '\t')
		{
			if (ch == '\n')
			{
				lineNum++;
			}
			ch = output.get();
			characterNum++;
		}
		else if (((ch >= 'a') && (ch <= 'z')) || ((ch >= 'A') && (ch <= 'Z')))//����Ϊ��ĸ
		{
			word[i++] = ch;
			characterNum++;
			ch = output.get();
			while (((ch >= 'a') && (ch <= 'z')) || ((ch >= 'A') && (ch <= 'Z')) || ((ch >= '0') && (ch <= '9')||(ch=='_')))
			{
				word[i++] = ch;
				ch = output.get();
				characterNum++;
			}
			//��ѯ�ǲ��ǻ����ṹ
			for (int j = 0; j < 11; j++)
			{
				if (strcmp(word, structer[j]) == 0)
				{
					k = true;//���ʱ��ҵ�
					cout << "�����ṹ" << word << endl;
					break;
				}
			}
			//��ѯ�ǲ�����������
			for (int j = 0; j < 11; j++)
			{
				if (strcmp(word, dataType[j]) == 0)
				{
					k = true;//���ʱ��ҵ�
					cout << "��������" << word << endl;
					break;
				}
			}
			if (k == false)//Ϊ��ʶ��
			{
				cout << "��ʶ��" << word << endl;
			}
			wordNum++;
			for (int j = 0; j < i; j++)
			{
				word[j] = '\0';
			}
			i = 0;
			k = false;
		}

		else if ((ch >= '0') && (ch <= '9'))//����Ϊ����
		{
			word[i++] = ch;
			ch = output.get();
			characterNum++;
			while (a != 1)
			{
				switch (state){
				case 1://�жϰ˽��ƻ�ʮ������
					char chpro;
					chpro = word[i-1];
					if (chpro == '0')//��һ������Ϊ0
					{
						if ((ch >= '0') && (ch <= '7'))//Ϊ�˽���
						{
							while ((ch >= '0') && (ch <= '7'))
							{
								word[i++] = ch;
								ch = output.get();
								characterNum++;
							}
							if ((ch >= 'a'&&ch <= 'z') || (ch >= 'A'&&ch <= 'Z') || ch == '8' || ch == '9')//���ɹ�����������ĸ��8��9
							{
								while ((ch >= 'a'&&ch <= 'z') || (ch >= 'A'&&ch <= 'Z') || (ch >= '0'&&ch <= '9'))
								{
									word[i++] = ch;
									ch = output.get();
									characterNum++;
								}
								cout << "�����У��к��ǣ�" << lineNum << endl;
								errorLine[errorNum] = lineNum;
								errorNum++;
								state = 8;
								break;
							}
							else //�ɹ�Ϊ�˽�����
							{
								cout << "�˽�����" << word << endl;
								wordNum++;
								state = 8;
								break;
							}
						}
						else if (ch == 'x' || ch == 'X')//Ϊʮ��������
						{
							word[i++] = ch;
							ch = output.get();
							characterNum++;
							while (((ch >= '0') && (ch <= '9')) || ((ch <= 'f') && (ch >= 'a')) || ((ch <= 'F') && (ch >= 'A')))
							{
								word[i++] = ch;
								characterNum++;
								ch = output.get();
							}
							if ((ch >= 'h'&&ch <= 'z') || (ch >= 'H'&&ch <= 'Z'))//δ�ɹ���������h-z
							{
								while ((ch >= 'a'&&ch <= 'z') || (ch >= 'A'&&ch <= 'Z') || (ch >= '0'&&ch <= '9'))
								{
									word[i++] = ch;
									ch = output.get();
									characterNum++;
								}
								cout << "�����У��к��ǣ�" << lineNum << endl;
								errorLine[errorNum] = lineNum;
								errorNum++;
								state = 8;
								break;
							}
							else
							{
								cout << "ʮ��������" << word << endl;
								wordNum++;
								state = 8;
								break;
							}
						}
						else//��û�����ǰ˽���Ҳû������ʮ�����ƣ���ת��״̬2
						{
							state = 2;
							break;
						}

					}
					else//����ĵ�һ�����ֲ���0
					{
						state = 2;
						break;
					}

				case 2:
					if ((ch >= '0') && (ch <= '9'))//��������
					{
						state = 2;//�Ա�����״̬2
						word[i++] = ch;
						ch = output.get();
						characterNum++;
					}
					else if (ch == '.')//����С����
					{
						state = 3;//��ת��״̬3
						word[i++] = ch;
						ch = output.get();
						characterNum++;
					}
					else if (ch == 'e' || ch == 'E')//����ָ������
					{
						state = 5;//ת��״̬5
						word[i++] = ch;
						ch = output.get();
						characterNum++;
					}
					else if (ch == 'l')//�ж��ǲ���long����
					{
						ch = output.get();
						characterNum++;
						word[i++] = ch;
						cout << "long����" << word << endl;//���long����
						wordNum++; 
						state = 8;//��ת��״̬8��ɨ�����
					}
					else if (ch == 'u')//�ж��ǲ���unsigned����
					{
						ch = output.get();
						characterNum++;
						word[i++] = ch;
						cout << "unsigned����" << word << endl;//���unsigned����
						wordNum++;
						state = 8;;//��ת��״̬8��ɨ�����
					}
					else
						state= 7;
					break;

				case 3://ʶ��С�����Ժ�Ĳ���
					if (ch >= '0' && ch <= '9')//С�����������
					{
						state = 4;//��ת��״̬4
						word[i++] = ch;
						ch = output.get();
						characterNum++;
						
					}
					else//С����������֣�����
					{
						cout << "�����У��к��ǣ�" << lineNum << endl;
						errorLine[errorNum] = lineNum;
						errorNum++;
						state = 8;
					}
					break;

				case 4://С������ǳ�����
					if (ch >= '0' && ch <= '9')//С�����ĳ��������ǳ���
					{
						state = 4;
						word[i++] = ch;
						ch = output.get();
						characterNum++;
						
					}
					else if (ch == 'e' || ch == 'E')//С�����ĳ�������ָ������
					{
						state = 5;//��ת��״̬5
						word[i++] = ch;
						ch = output.get();
						characterNum++;
						
					}
					else
						state= 7;
					break;

				case 5://ʶ����ָ��֮��Ĳ���
					if (ch == '+' || ch == '-')//ָ�����ź���������
					{
						state = 6;//��ת��״̬6
						word[i++] = ch;
						ch = output.get();
						characterNum++;
						
					}
					else if (ch >= '0'&&ch <= '9')//ָ�����ź�������
					{
						state = 6;//��ת��״̬6
						word[i++] = ch;
						ch = output.get();
						characterNum++;
						
					}
					else//ָ�����ź�Ȳ�������Ҳ���������ţ�����
					{
						cout << "�����У��к��ǣ�" << lineNum << endl;
						errorLine[errorNum] = lineNum;
						errorNum++;
						state = 8;
					}
					break;

				case 6://ָ��֮���֮��
					if (ch >= '0'&&ch <= '9')
					{
						state = 6;
						word[i++] = ch;
						ch = output.get();
						characterNum++;
						
					}
					else
						state= 7;
					break;

				case 7:
					if ((ch<'a'||ch>'z') && (ch<'A'||ch>'Z'))//������ţ��������
					{
					cout << "����" << word << endl;
					wordNum++;
				    }
					else if ((ch >= 'a'&&ch <= 'z') || (ch >= 'A'&&ch <= 'Z'))//������ĸ������
					   {
						   while ((ch >= 'a'&&ch <= 'z') || (ch >= 'A'&&ch <= 'Z'))
						   {
							   word[i++] = ch;
							   ch = output.get();
							   characterNum++;
						   }
						   cout << "�����У��к��ǣ�" << lineNum << endl;
						   errorLine[errorNum] = lineNum;
						   errorNum++;
					   }
					   else//��������������
					   {
						   cout << "�����У��к��ǣ�" << lineNum << endl;
						   errorLine[errorNum] = lineNum;
						   errorNum++;
					   }
					   a = 1;
					   break;
						
					case 8://ɨ����ɣ�����ѭ��
						a = 1;
						break;
				}
			}
			//ɨ����ϣ���������ʼ��
			for (int j = 0; j <= i; j++)
			{
				word[j] = '\0';
			}
			i = 0;
			a = 0;
			state = 1;
		}

		else if (ch == '#')//ʶ���Ƿ�ΪԤ�����
		{
			ch = output.get();
			characterNum++;
			if (ch >= 'a'&&ch <= 'z')//#���������Сд��ĸ
			{
				word[i++] = ch;
				ch = output.get();
				characterNum++;
				while (ch >= 'a'&&ch <= 'z')
				{
					word[i++] = ch;
					ch = output.get();
					characterNum++;
				}

				for (int j = 0; j <= i; j++)
				{
					if (strcmp(word, preDeal[j]) == 0)//�ж��ǲ���Ԥ�����
					{
						k = true;//���ʱ��ҵ�����Ԥ�����
						cout << "Ԥ�����#" << word << endl;
						wordNum++;
						break;
					}
				}
				for (int j = 0; j <= i; j++)//��ʼ��
				{
					word[j] = '\0';
				}
				i = 0;
				k = false;
			}
			else//����Ԥ���������#��Ϊ�����������
			{
				cout << "�����#" << endl;
				wordNum++;
			}
		}

		else if (ch == '<')//ʶ����<��ͷ�ķ���
		{
			word[i++] = ch;
			ch = output.get();
			characterNum++;
			if (ch == '=' || ch == '>')//ʶ��<=,<>
			{
				word[i++] = ch;
				ch = output.get();
				characterNum++;
				wordNum++;
				cout << "�����" << word << endl;
			}
			else if(ch=='<')//ʶ��<<,<<=
			{
				word[i++] = ch;
				ch = output.get();
				characterNum++;
				if (ch == '=')//ʶ��<<=
				{
					word[i++] = ch;
					wordNum++;
					ch = output.get();
					characterNum++;
					cout << "�����" << word << endl;
				}
				else//ʶ��<<
				{
					cout << "�����" << word << endl;
					wordNum++;
				}
			}
			else//<��Ϊ�����������
			{
				cout << "�����" << word << endl;
				wordNum++;
			}
			for (int j = 0; j <= i; j++)//��ʼ��
			{
				word[j] = '\0';
			}
			i = 0;
		}

		else if (ch == '>')//ʶ����>��ͷ�ķ���
		{
			word[i++] = ch;
			ch = output.get();
			characterNum++;
			//ʶ��>=
			if (ch == '=')
			{
				wordNum++;
				word[i++] = ch;
				ch = output.get();
				characterNum++;
				cout << "�����" << word << endl;
			}
			else if (ch == '>')//ʶ��>>=,>>
			{
				word[i++] = ch;
				ch = output.get();
				characterNum++;
				if (ch == '=')
				{
					word[i++] = ch;
					wordNum++;
					ch = output.get();
					characterNum++;
					cout << "�����" << word << endl;
				}
			}
			else//>Ϊ���������
			{
				cout << "�����" << word << endl;
				wordNum++;
			}
			for (int j = 0; j <= i; j++)//word��ʼ��
			{
				word[j] = '\0';
			}
			i = 0;
		}

		else if (ch == ':')//ʶ����:��ͷ�ķ���
		{
			word[i++] = ch;
			ch = output.get();
			characterNum++;
			//ʶ��:=
			if (ch == '=')
			{
				word[i++] = ch;
				ch = output.get();
				characterNum++;
				wordNum++;
				cout << "�����" << word << endl;
			}
			else//����
			{
				cout << "�����У�����Ϊ��" << lineNum << endl;
				errorLine[errorNum] = lineNum;
				errorNum++;
			}
			for (int j = 0; j <= i; j++)//word��ʼ��
			{
				word[j] = '\0';
			}
			i = 0;
		}

		else if (ch == '*' || ch == '+' || ch == '-')//ʶ�������
		{
			word[i++] = ch;
			ch = output.get();
			characterNum++;
			//ʶ��*=��/=��+=��-=
			if (ch == '=')
			{
				word[i++] = ch;
				ch = output.get();
				characterNum++;
				wordNum++;
				cout << "�����" << word << endl;
			}
			else//*��+��-��Ϊ���������
			{
				wordNum++;
				cout << "�����" << word << endl;
			}
			for (int j = 0; j <= i; j++)//word��ʼ��
			{
				word[j] = '\0';
			}
			i = 0;
		}

		else if (ch == '/')//ʶ��ע��
		{
			ch = output.get();
			if (ch == '/')//ע����//ʽ
			{
				characterNum--;
				ch = output.get();
				while (ch != '\n')//ע��//ʽ����
				{
					word[i++] = ch;
					ch = output.get();
				}
				cout << "ע��" << word << endl;
				for (int j = 1; j <= i; j++)
				{
					word[j] = '\0';
				}
				i = 0;
				characterNum++;
			}
			else if (ch == '*')//ע����/**/ʽ
			{
				characterNum--;
				ch = output.get();
				while (ch != '*')
				{
					word[i++] = ch;
					ch = output.get();
				}
				ch = output.get();
				if (ch == '/')
					cout << "ע��" << word << endl;
				for (int j = 1; j <= i; j++)
				{
					word[j] = '\0';
				}
				i = 0;
				ch = output.get();
				characterNum++;
			}
			else
			{
				word[i++] = '/';
				characterNum++;
				if (ch == '=')
				{
					wordNum++;
					word[i++] = ch;
					ch = output.get();
					characterNum++;
					cout << "�����" << word << endl;
				}
				else
				{
					wordNum++;
					cout << "�����" << word << endl;
				}
				for (int j = 0; j <= i; j++)
				{
					word[j] = '\0';
				}
				i = 0;
			}
		}

		else if (ch == '(' || ch == ')' || ch == '{' || ch == '}' || ch == ',' || 
			ch == ';' || ch == '.' || ch == '[' || ch == ']' || ch == '_' || ch == '"')
		{
			cout << "�ָ���" << ch << endl;
			wordNum++;
			ch = output.get();
			characterNum++;

		}
		else
		{
			cout << "�����У��к�Ϊ��" << lineNum << endl;
			errorLine[errorNum] = lineNum;
			errorNum++;
			ch = output.get();
			characterNum++;
		}
		
	}
	output.close();
}

void main()
{
	cout << "~~~~~~~~~~~~~~~~~�﷨������~~~~~~~~~~~~~~~~~~" << endl;
	cout << "���������ݷ��ڳ�������Ŀ¼�µ�input.txt�ĵ�����$��β" << endl;
	scanner();
	cout << "���������" << endl;
	cout << "�ַ�����" <<characterNum<< endl;
	cout << "��������" <<wordNum<< endl;
	cout << "������" <<lineNum<< endl;
	cout << "����" <<errorNum<<"�д���"<< endl;
	cout << "���������ֱ�Ϊ��";
	for (int i = 0; i < errorNum; i++)
	{
		cout << errorLine[i] << " ";
	}
	cout << endl;
	system("pause");
}

