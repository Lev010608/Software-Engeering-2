#include "Conio.h"

//�ж�������ַ��Ƿ�Ϊ����
int isDigit(char ch) {
    if (ch >= '0' && ch <= '9') {
        return 1;
    }
    else {
        return 0;
    }
}

//�ж�������ַ��Ƿ�Ϊ��ĸ����д+Сд��
int isLetter(char ch) {
    if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')) {
        return 1;
    }

    else {
        return 0;
    }
}

//�ж�������ַ��Ƿ�Ϊ�հ׷�
int isBlank(char ch) {
    if (ch == ' ' || ch == '\t' || ch == '\b' || ch == '\n'){
        return 1;
    }
    else {
        return 0;
    }
}