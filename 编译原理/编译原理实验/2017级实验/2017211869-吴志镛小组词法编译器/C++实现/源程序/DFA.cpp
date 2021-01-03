#include"DFA.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>



DFA::DFA()
{
	if ((infile = fopen("source.txt", "r")) == NULL)
	{
		printf("Open source file error!\n");
		exit(0);
	}
	if ((outfile = fopen("out.txt", "w")) == NULL)
	{
		printf("Open dest file error!\n");
		exit(0);
	}
	GetChar();
	GetBC();
	while (ch != EOF)
	{
		//ʶ������
		if (IsDigit(ch))
		{
			pos = 0;
			while (IsDigit(ch))
			{
				Concat(ch);
				GetChar();
			}
			//whileѭ���ڶ��� ���ֿ�ͷ+��ĸʱ���� 
			if (IsLetter(ch))
			{
				strToken[0] = '\0';
				printf("��%d���зǷ��ַ�����������......\n", numberOflines);
				while (IsLetter(ch))
					GetChar();
			}
			strToken[pos++] = '\0';
			if (strToken[0] != '\0')
				fprintf(outfile, "%s      ����\n", strToken);
			numberOfwords++;
			GetBC();
		}

		//ʶ��ؼ��֡���ʶ��           
		else if (IsLetter(ch))
		{
			pos = 0;
			while (IsLetter(ch) || IsDigit(ch) || ch == '_')
			{
				Concat(ch);
				GetChar();
			}
			strToken[pos++] = '\0';
			if (KeyList(strToken) == 1)
				fprintf(outfile, "%s      �ؼ���\n", strToken);
			else fprintf(outfile, "%s      ��ʶ��\n", strToken);

			numberOfwords++;
			GetBC();
		}


		//ʶ�������(��������� ��ϵ����� �߼������ ��ֵ����� ������λ�����) 
		else if (ch == '+') //+,++,+=
		{
			pos = 0;
			Concat(ch);
			GetChar();
			if (ch == '+' || ch == '=')
			{
				Concat(ch);
				strToken[pos++] = '\0';
				fprintf(outfile, "%s      �����\n", strToken);
				GetChar();
				GetBC();
			}
			else
			{
				strToken[pos++] = '\0';
				fprintf(outfile, "%s      �����\n", strToken);
				GetBC();//�������ch��Ӧ����GetChar()
			}
		}

		else if (ch == '-') //-,--,-=
		{
			pos = 0;
			Concat(ch);
			GetChar();
			if (ch == '-' || ch == '=')
			{
				Concat(ch);
				strToken[pos++] = '\0';
				fprintf(outfile, "%s      �����\n", strToken);
				GetChar();
				GetBC();
			}
			else
			{
				strToken[pos++] = '\0';
				fprintf(outfile, "%s      �����\n", strToken);
				GetBC();
			}
		}

		else if (ch == '*' || ch == '%' || ch == '!' || ch == '>' || ch == '<' || ch == '=')
			//*,*=,%,%=!,!=,>,>=,<,<=,=,==
		{
			pos = 0;
			Concat(ch);
			GetChar();
			if (ch == '=')
			{
				Concat(ch);
				strToken[pos++] = '\0';
				fprintf(outfile, "%s      �����\n", strToken);
				GetChar();
				GetBC();
			}
			else
			{
				strToken[pos++] = '\0';
				fprintf(outfile, "%s      �����\n", strToken);
				GetBC();
			}
		}

		else if (ch == '&') // &&
		{
			pos = 0;
			Concat(ch);
			GetChar();
			if (ch == '&')
			{
				Concat(ch);
				strToken[pos++] = '\0';
				fprintf(outfile, "%s      �����\n", strToken);
				GetChar();
				GetBC();
			}
			else
			{
				printf("��%d���зǷ��ַ�����������......\n", numberOflines);
				GetChar();
				GetBC();
			}
		}

		else if (ch == '|') // ||
		{
			pos = 0;
			Concat(ch);
			GetChar();
			if (ch == '|')
			{
				Concat(ch);
				strToken[pos++] = '\0';
				fprintf(outfile, "%s      �����\n", strToken);
				GetChar();
				GetBC();
			}
			else
			{
				printf("��%d���зǷ��ַ�����������......\n", numberOflines);
				GetChar();
				GetBC();
			}
		}

		else if (ch == '/') // /,/=,//
		{
			pos = 0;
			Concat(ch);
			GetChar();
			if (ch == '=')
			{
				Concat(ch);
				strToken[pos++] = '\0';
				fprintf(outfile, "%s      �����\n", strToken);
				GetChar();
				GetBC();
			}
			else if (ch == '/') //ע�͵Ĵ���(����)��ֻ����//�͵�ע�ͣ�������/**/�͵�ע��       
			// //��ע�Ͷ�������ĩβ
			{
				Retract();
				while (ch != '\n'&&ch != EOF) //���������һ�����Կ���EOF 
					GetChar();
				GetBC(); //�¼ӵ� 
			}
			else
			{
				strToken[pos++] = '\0';
				fprintf(outfile, "%s      �����\n", strToken);
				GetBC();
			}
		}

		//ʶ��ֽ��         
		else if (IsBound(ch))
		{
			pos = 0;
			Concat(ch);
			strToken[pos++] = '\0';
			fprintf(outfile, "%s      �ֽ��\n", strToken);
			GetChar();
			GetBC();
		}
		else
		{
			printf("��%d���зǷ��ַ�����������......\n", numberOflines);
			GetChar();
			GetBC();
		}
	}

	//��ӡͳ�ƽ��
	printf("\n����%d��\n", numberOflines);
	printf("\n���ʸ���Ϊ%d��(���ؼ��֡���ʶ�������ָ���)\n", numberOfwords);
	printf("\n�ַ�����Ϊ%d��(�������ո񡢻��С�ע���е��ַ����ڵ������ַ�)\n\n\n", numberOfchars);
	system("pause");

}

DFA::~DFA()
{
}

char DFA::getCH()
{
	return ch;
}

int DFA::getpos()
{
	return pos;
}

char DFA::GetChar()
{
	ch = fgetc(infile);
	if (ch == EOF)
		printf("\n source.txt �Ĵʷ����������,���������¼�� out.txt\n\n");
	numberOfchars++;
	return ch;
}

void DFA::GetBC()//���ch���ַ��Ƿ�հ� ���Ǽ�������GetChar()ֱ���ǿ�
{
	while (ch == ' ' || ch == '\t' || ch == '\b' || ch == '\n')
	{
		if (ch == '\n')
			numberOflines++;
		GetChar();
	}
}

void DFA::Concat(char ch)//��ch�е��ַ����ӵ�strToken��
{
	strToken[pos++] = ch;
}

int DFA::IsLetter(char ch)//�жϵ�ǰ�ַ��Ƿ�Ϊ��ĸ 
{
	if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
		return 1;
	else return 0;
}

int DFA::IsDigit(char ch)//�жϵ�ǰ�ַ��Ƿ�Ϊ���� 
{
	if (ch >= '0' && ch <= '9')
		return 1;
	else return 0;
}

int DFA::IsBound(char ch)//�жϵ�ǰ�ַ��Ƿ�Ϊ�ֽ�� 
{
	if (ch == '.' || ch == '{' || ch == '}' || ch == '[' || ch == ']' || ch == '(' || ch == ')' || ch == ',' || ch == ';' ||
		ch == '#' || ch == '\\' || ch == '\'' || ch == '\"' || ch == '\?' || ch == ':')
		return 1;
	else return 0;
}

void DFA::Retract() //strToken���ˣ���ch�ÿ� 
{
	pos--;
	ch = ' ';
}

int DFA::KeyList(char strToken[])//�ж�strToken���Ƿ�Ϊ�ؼ���
{
	if (strcmp(strToken, "auto") == 0)
		return 1;
	else if (strcmp(strToken, "break") == 0)
		return 1;
	else if (strcmp(strToken, "case") == 0)
		return 1;
	else if (strcmp(strToken, "char") == 0)
		return 1;
	else if (strcmp(strToken, "const") == 0)
		return 1;
	else if (strcmp(strToken, "continue") == 0)
		return 1;
	else if (strcmp(strToken, "default") == 0)
		return 1;
	else if (strcmp(strToken, "double") == 0)
		return 1;
	else if (strcmp(strToken, "do") == 0)
		return 1;
	else if (strcmp(strToken, "else") == 0)
		return 1;
	else if (strcmp(strToken, "enum") == 0)
		return 1;
	else if (strcmp(strToken, "extern") == 0)
		return 1;
	else if (strcmp(strToken, "float") == 0)
		return 1;
	else if (strcmp(strToken, "for") == 0)
		return 1;
	else if (strcmp(strToken, "goto") == 0)
		return 1;
	else if (strcmp(strToken, "if") == 0)
		return 1;
	else if (strcmp(strToken, "int") == 0)
		return 1;
	else if (strcmp(strToken, "long") == 0)
		return 1;
	else if (strcmp(strToken, "register") == 0)
		return 1;
	else if (strcmp(strToken, "return") == 0)
		return 1;
	else if (strcmp(strToken, "short") == 0)
		return 1;
	else if (strcmp(strToken, "signed") == 0)
		return 1;
	else if (strcmp(strToken, "sizeof") == 0)
		return 1;
	else if (strcmp(strToken, "static") == 0)
		return 1;
	else if (strcmp(strToken, "struct") == 0)
		return 1;
	else if (strcmp(strToken, "switch") == 0)
		return 1;
	else if (strcmp(strToken, "typedef") == 0)
		return 1;
	else if (strcmp(strToken, "union") == 0)
		return 1;
	else if (strcmp(strToken, "unsigned") == 0)
		return 1;
	else if (strcmp(strToken, "void") == 0)
		return 1;
	else if (strcmp(strToken, "volatile") == 0)
		return 1;
	else if (strcmp(strToken, "while") == 0)
		return 1;
	else return 0;
}
