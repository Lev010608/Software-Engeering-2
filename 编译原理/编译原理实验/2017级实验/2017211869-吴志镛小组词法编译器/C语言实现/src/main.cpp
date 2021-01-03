#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Conio.h"

/******ȫ�ֱ�������*******/
FILE* readp, * writep;             //�ļ�ָ��
char token[30] = { 0 };          //���ÿ��ɨ��Ľ��
char keylist[32][20] = {         //C���Ե�32���ؼ��֣������ֵ�����������
    "auto", "break", "case", "char", "const", "continue",
    "default", "do", "double", "else", "enum", "extern",
    "float", "for", "goto", "if", "int", "long",
    "register", "return", "short", "signed", "sizeof", "static",
    "struct", "switch", "typedef", "union", "unsigned", "void",
    "volatile", "while"
};
char symbolList[100][5] = {      //������ͷֽ���ı�
    "+", "-", "*", "/", "<", "<=", ">", ">=", "=", "==", 
   "!=", "<<", ">>", "++", "--", "+=", "-=", "*=", "/=",
   "&=", "|=", ";", "(", ")", "^", ",", "\"", "\'", "&", 
   "&&", "|", "||", "%", "~", "<<", ">>", "[", "]", "{", 
   "}", "\\", ".", "\?", ":", "!"
};
char identifierTable[500][30] = { 0 };  //��ʶ����Ĭ��Ϊ��
int identifierNum = 0;                  //��ʶ������

int lineCount = 1;                //��¼����������
int charCount = -1;               //��¼�ַ�����

int wordCount = 0;                //��¼���ʵĸ���
int stringCount = 0;
int numCount = 0;                 //��¼�����ĸ���
int operatorCount = 0;            //��¼������ĸ���
int delimiterCount = 0;           //��¼����ĸ���


char getChar();                //���ļ��ж���һ���ַ�
void scan();                   //�����������мǺŵ�ʶ��
char scanFloat(char ch);       //�ӹ��ܺ�����ʶ�������͸�����
char scanString(char ch);      //�ӹ��ܺ�����ʶ���ַ����ṹ
int isCKey();                  //�ӹ��ܺ������ж�һ���ַ����Ƿ�ΪC���ԵĹؼ��֣�����ǣ����ظùؼ����ڱ��е�λ�ã����򷵻�-1
void clearToken();             //��������еĻ�����
int insertID();                //���ʶ�����м����µı�ʶ���������ر�ʶ���ĵ�ַ������Ѿ����룬�򲻽��в��������
int findSymbol(char str[]);    //��������ͷֽ�����в��ҷ��ţ��������ڱ��еĵ�ַ
void printResult();            //�ڿ���̨�д�ӡͳ�ƽ��


int main() {
    char ch;
    char str[10] = "asfa\e\n\5";
    //���ļ��ж���Դ����
    if ((readp = fopen("SourceCode.txt", "r")) == NULL) {
       printf("file cannot open \n");
       exit(0);
    }

    if ((writep = fopen("TokenStream.txt", "w")) == NULL) {
        printf("file cannot open \n");
        exit(0);
    }
    

    scan();
    printResult();
    if (fclose(readp) != 0) {
       printf("file cannot be closed \n");
    }
    if (fclose(writep) != 0) {
        printf("file cannot be closed \n");
    }
    system("pause");
    
    return 0;
}

//�����������мǺŵ�ʶ��
void scan() {
    char ch;
    ch = getChar();

    while (ch != EOF) {
        //ch�ǿհ׷����������еĿհ׷�
        if (isBlank(ch)) {
            while (isBlank(ch = getChar()));
        }
        //ch����ĸ����ʶ�� or �ؼ���
        else if (isLetter(ch)) {
            //ɨ��������ı�ʶ��
            int p = 0;
            do {
                token[p++] = ch;
                ch = getChar();
            } while (isDigit(ch) || isLetter(ch) || ch == '_');
            wordCount++;
            //�жϱ�ʶ��token�Ƿ�ΪC���Թؼ���
            int addr;
            if ((addr = isCKey()) != -1) {
                
                fprintf(writep, "%s --- �ؼ���%d\n", token, addr);
            }
            else {
                //����Ǳ�ʶ�������������ű���
                addr = insertID();

                fprintf(writep, "%s --- ��ʶ��%d\n", token, addr);
            }
            clearToken();
            
        }
        //ch�����֣����� or ������
        else if (isDigit(ch)) {
            ch = scanFloat(ch);
            clearToken();
        }
        else if (ch == '\"') {
            ch = scanString(ch);
        }
        //ch�������ַ�������� or ���
        else if(ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == ';' || ch == '(' || ch == ')' || ch == '^'
            || ch == ',' || ch == '\'' || ch == '~' || ch == '#' || ch == '%' || ch == '['
            || ch == ']' || ch == '{' || ch == '}' || ch == '\\' || ch == '.' || ch == '\?' || ch == ':' 
            || ch == '=' || ch == '<' || ch == '>' || ch == '!' || ch == '&' || ch == '|'){
             
            //��ch���з��������
            switch (ch) {
            case '#': {
                //Ԥ�����ֵ����ݣ���˱�������
                while (1) {
                    ch = getChar();
                    if (ch == '\n' || ch == '\b') {
                        break;
                    }
                }
                ch = getChar();
                break;
            }
            case '/': {
                ch = getChar();
                switch (ch) {
                case '/': {
                    //����ע�ͽṹ��������������
                    while (1) {
                        ch = getChar();
                        if (ch == '\n' || ch == '\b') {
                            break;
                        }
                    }
                    //ch = getChar();
                    break;
                }
                case '*': {
                    //����ע�ͽṹ��������������д��룬ֱ������'*/'
                    int flag = 0;        //flag������ʶ��һ���ַ��Ƿ�Ϊ*��
                    while (1) {
                        ch = getChar();
                        if (flag && ch == '/') {
                            //����ע��ʶ��
                            break;
                        }
                        if (ch == '*') {
                            flag = 1;
                        }
                        else {
                            flag = 0;
                        }
                        
                    }
                    //ch = getChar();
                    break;
                }
                case '=': {
                    char str[] = "/=";
                    operatorCount++;
                    fprintf(writep, "/= --- �����%d\n", findSymbol(str));
                    //ch = getChar();
                    break;
                }
                default: {
                    char str[] = "/";
                    operatorCount++;
                    fprintf(writep, "/ --- �����%d\n", findSymbol(str));
                    break;
                }
                }
                ch = getChar();
                break;
            }
            case '=':
            case '*':
            case '%':
            case '!': {
                //ʶ��= * % ! == *= %= !=
                token[0] = ch;
                ch = getChar();
                if (ch == '=') {
                    token[1] = ch;
                    ch = getChar();
                }
                operatorCount++;
                fprintf(writep, "%s --- �����%d\n", token, findSymbol(token));
                clearToken();

                break;
            }
            case '<':
            case '>':
            case '+':
            case '-': {
                //ʶ��++ -- += -= + -
                token[0] = ch;
                ch = getChar();
                if (token[0] == ch || ch == '=') {
                    token[1] = ch;
                    ch = getChar();
                }
                operatorCount++;
                fprintf(writep, "%s --- �����%d\n", token, findSymbol(token));
                clearToken();
                break;
            }
            case '&':
            case '|': {
                //ʶ��&& || &= |= & | << >> <= >= < >
                token[0] = ch;
                ch = getChar();
                if (token[0] == ch || ch == '=') {
                    token[1] = ch;
                    ch = getChar();
                }
                operatorCount++;
                fprintf(writep, "%s --- �����%d\n", token, findSymbol(token));
                clearToken();
                break;
            }
            case '~':
            case '^': {
                //����ֻ��һ���ַ���ɵ������
                char str[2] = { ch };
                operatorCount++;
                fprintf(writep, "%s --- �����%d\n", str, findSymbol(str));
                ch = getChar();
                break;
            }
            default: {
                //ʣ��ľ�Ϊ������Ҿ�ֻ��һ���ַ����
                char str[2] = { ch };
                delimiterCount++;
                fprintf(writep, "%s --- ���%d\n", str, findSymbol(str));
                ch = getChar();
                break;
            }
            }
        }
        //����C���Բ�����ķǷ��ַ�������
        else {
            printf("WARNING: �� %d �г��ַǷ��ַ������Ժ��������...\n", lineCount);
            while (!isBlank(ch = getChar()));
        }
    }

    
}

//�ӹ��ܺ�����ʶ�������͸�����
char scanFloat(char ch){
    //����������ɨ��������ŵ���������
    int p = 0;
    do {
        token[p++] = ch;
        ch = getChar();
    } while (isDigit(ch));
    if (isLetter(ch) && ch !='e' &&  ch != 'E') {
        printf("WARNING: �� %d �г��ַǷ��ַ������Ժ��������...\n", lineCount);
        while (!isBlank((ch = getChar())));
        return ch;
    }
    //num1����������֣�num2���С�����֣�num3���ָ������
    int num1 = 0, num3 = 0;
    double num2 = 0;
    for (int i = 0; i < strlen(token); i++) {
        char temp = token[i];
        num1 = num1 * 10 + (temp - '0');
    }
    clearToken();
    if (ch == '.') {    //ʶ��С���㣬˵��������С������
        //��С������ɨ��������ŵ���������
        int p = 0;
        while (isDigit((ch = getChar()))) {
            token[p++] = ch;
        }
        if (p == 0) {
            //С�������û�����֣�����
            printf("WARNING: �� %d �г��ַǷ��ַ������Ժ��������...\n", lineCount);
            while (!isBlank((ch = getChar())));
            return ch;
        }
        else {
            for (int i = strlen(token) - 1; i >= 0; i--) {
                char temp = token[i];
                num2 = (num2 + (temp - '0')) / 10.0;
            }
            clearToken();
        }
    }
    if (ch == 'e' || ch == 'E') {
        //ָ������
        int signal = 1;
        int p = 0;
        ch = getChar();
        if (ch == '+' || ch == '-') {
            if (ch == '-') {
                signal = -1;
            }
            ch = getChar();
            if (!isDigit(ch)) {
                printf("WARNING: �� %d �г��ַǷ��ַ������Ժ��������...\n", lineCount);
                while (!isBlank((ch = getChar())));
                return ch;
            }
            else {
                token[p++] = ch;
            }
        }
        else if (isDigit(ch)) {
            token[p++] = ch;
        }
        else {
            printf("WARNING: �� %d �г��ַǷ��ַ������Ժ��������...\n", lineCount);
            while (!isBlank((ch = getChar())));
            return ch;
        }

        while (isDigit((ch = getChar()))) {
            token[p++] = ch;
        }
        for (int i = 0; i < strlen(token); i++) {
            char temp = token[i];
            num3 = num3 * 10 + (temp - '0');
        }
        num3 = num3 * signal;
    }
    clearToken();
    numCount++;
    if (num2 == 0) {
        int num = num1 * (int)(pow(10, num3));
        fprintf(writep, "%d --- ������\n", num);
    }
    else {
        double num = (num1 + num2) * pow(10, num3);
        fprintf(writep, "%.2f --- ������\n", num);
    }
    return ch;
}

char scanString(char ch){
    //����������ɨ��������ŵ���������
    int p = 0;
    token[p++] = ch;
    while (1) {
        ch = getChar();
        token[p++] = ch;
        if (ch == '\"') {
            break;
        }
    }
    stringCount++;
    fprintf(writep, "%s --- �ַ���\n", token);
    clearToken();
    ch = getChar();
    return ch;
}

int insertID() {
    int isExist = 0;
    for (int i = 0; i < identifierNum; i++) {
        if (strlen(token) == strlen(identifierTable[i])) {
            int flag = 1;
            for (int j = 0; j < strlen(token); j++) {
                if (token[j] != identifierTable[i][j]) {
                    flag = 0;
                    break;
                }
            }
            if (flag) {
                isExist = 1;
                return i;
            }
        }
    }
    //���tokenδ�ڱ��У�����������
    if (!isExist) {
        for (int i = 0; i < strlen(token); i++) {

            identifierTable[identifierNum][i] = token[i];
        }
        identifierNum++;
        return identifierNum - 1;
    }
    return -1;
}

int findSymbol(char str[]){
    for (int i = 0; i < 50; i++) {
        if (strlen(str) == strlen(symbolList[i])) {
            int flag = 1;
            for (int j = 0; j < strlen(str); j++) {
                if (str[j] != symbolList[i][j]) {
                    flag = 0;
                    break;
                }
            }
            if (flag) {
                return i;
            }
        }

    }
    return -1;
    return 0;
}

void printResult(){
    printf("\n\n\n/---------ͳ�ƽ��----------/\n");
    printf("����������: %d\n", lineCount);
    printf("�������ַ�����: %d\n\n", charCount);
    printf("������ÿ�ּǺŵĸ�����\n");
    printf("\t����: %d\n", wordCount);
    printf("\t�ַ���: %d\n", stringCount);
    printf("\t�޷�����: %d\n", numCount);
    printf("\t�����: %d\n", operatorCount);
    printf("\t���: %d\n", delimiterCount);

    printf("/---------��ʶ����----------/\n");
    for (int i = 0; i < identifierNum; i++) {
        printf("%2d ------- %s\n", i, identifierTable[i]);
    }
    
}

int isCKey() {
    for (int i = 0; i < 32; i++) {
        if (strlen(token) == strlen(keylist[i])) {
            int flag = 1;
            for (int j = 0; j < strlen(token); j++) {
                if (token[j] != keylist[i][j]) {
                    flag = 0;
                    break;
                }
            }
            if (flag) {
                return i;
            }
        }
        
    }
    return -1;
}

char getChar() {
    char ch = fgetc(readp);
    if (!isBlank(ch) && ch != EOF) {
        charCount++;
    }
    
    if (ch == '\n' || ch == '\b') {
        lineCount++;
    }
    return ch;
}

void clearToken() {
    int l = strlen(token);
    for (int i = 0; i < l; i++) {
        token[i] = 0;
    }
}