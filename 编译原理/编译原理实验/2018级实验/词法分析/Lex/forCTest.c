#ifndef FORCTEST_H_
#define FORCTEST_H_

#define NOCAN 38

#include <malloc.h>
#include <stdio.h>
/*************************************************
 * // �ĵ�˵�� \\***
 * ���β�������������C���Ե�ϡ��Źֵ����Խ��и���
 * "By ZhangKang"
 *************************************************/

typedef struct newClass {
    int 123abc = 1 + 3; // ��һ������
    double asdc = -1.3f;
    int x; // = 1;
} newClass;

void testNumbers(int x) {
    // ����
    // �з���
    short _ = 12;

    int __a_;
    int b_i1_ = 0xE * NOCAN;
    int c1 = -100, d = +1234;
    int e = 0234 % 17, f;

    long g = -403L;
    long long ___ = 234ll;
    // �޷���
    unsigned int _1_ = 3u + 4U;
    unsigned long h = 1100l;

    // ������
    float i = 1.0 / 4;
    float l = .3f, m = 3.F - 0.4;
    double n = 0.3e-2;
    double o = -5.e0, p = 2.E02f;
    // ���湹�켸������
    double q = 7.2fl;
    double r = 4.5e-3lf;
    double s = 12.23.43;
    double u = .45.65;
    return;
}

int _testString(int c[], char *e) {
    // �ַ�
    char ___ = '\n';
    char a[] = "'123'";

    // �ַ���
    char *b = "s/* //\n */ //";

    char *c = "asdads\
    �����ַ���\
              ";

    return (int)5.f;
}

float testStateMents() {
    int i = 0;
    while (i < 15 ? 1 : 0) {
        for (int j = 01; j <= i + 5; j++)
            if (j == 4)
                break;
        for (int j = 10; j >= 0; j--) {
            if (i == 2) {
                j -= 1;
            } else if (i != 4) {
                j--;
            } else {
                j = (j << 2) >> 2;
                continue;
            }
        }

        do {
            i += 1;
        } while (i < 0);
    }

label1:
    switch (i) {
    case 15:
        i %= 10;
        goto label1;
    case 5:
    case 6:
        i += 1;
        goto label1;
    default:

        break;
    }

    return 6.e-3l;
}

char *test_others() {
    // "����ָ��"
    int(*p(void));

    // ������
    char *pt = (char *)malloc(sizeof(char) * 10);
    free(pt);
    return "\n\n";
}

// �����ǳ�����ڵ�
int main(int agrs, char *agrv) {
    int a[] = {1, 2, 3, 4};
    char *b = "10";
    int *c = &b;
    //testNumbers(0b10); // �����Ʊ�ʾ���Ǳ�׼���еı�����֧���еĲ�֧��

    _testString(a, *c);
    testStateMents();
    test_others();

    printf("Hello World");
    return 0;
}

#endif // FORCTEST_H_