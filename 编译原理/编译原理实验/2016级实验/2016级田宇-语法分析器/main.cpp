/*
*
*
*�﷨������ 
*
*
*By TianYu 
*2018 12 20
*
*
*
*/

#include<stdlib.h>
#include<stdio.h>
#include<string.h>

/*������Լʱѹ�����ջ�ķ��š�������Լ������ת�������״̬*/
int symbol,status;
/*�������ջ*/
int analysis_stack [50];
/*ipΪջ��Ԫ���±�*/
int ip = -1;

/*��������Ŵ�w������������*/
char buffer[30];
/*��������ַ���ת��Ϊ������ʽ*/
int code[30];
/*positionΪcode������±�*/
int position = 0;
/*XΪ��ǰ��ȡ��������ŵĴ���*/
int X;

/*ѭ����־*/
int flag = 1;

typedef struct{/*�����ķ�����ʽ�Ľṹ*/
    int Vn;/*�ķ�����ʽ���󲿷��ս���Ĵ���*/
    int Str[4];/*�ķ�����ʽ�Ҳ��Ĵ��봮*/
    int size;/*�ķ�����ʽ�Ҳ��ĳ���*/
}G;

G production[11] = {/*���ķ������в���ʽ*/
    {0},
    {101,{0,102},1},/*S -> E*/
    {102,{0,102,3,103},3},/*E -> E+T*/
    {102,{0,102,4,103},3},/*E -> E-T*/
    {102,{0,103},1},/*E -> T*/
    {103,{0,103,5,104},3},/*T -> T*F*/
    {103,{0,103,6,104},3},/*T -> T/F*/
    {103,{0,104},1},/*T -> F*/
    {104,{0,7},1},/*F -> id*/
    {104,{0,1,101,2},3},/*F -> (E)*/
    {104,{0,8},1},/*F -> num*/
};
int GOTO[17][5] = {/*LR������goto*/
    {0,0,1,2,3},/*0*/
    {0,0,0,0,0},/*1*/
    {0,0,0,0,0},/*2*/
    {0,0,0,0,0},/*3*/
    {0,0,0,0,0},/*4*/
    {0,0,11,2,3},/*5*/
    {0,0,0,0,0},/*6*/
    {0,0,0,12,3},/*7*/
    {0,0,0,13,3},/*8*/
    {0,0,0,0,14},/*9*/
    {0,0,0,0,15},/*10*/
    {0,0,0,0,0},/*11*/
    {0,0,0,0,0},/*12*/
    {0,0,0,0,0},/*13*/
    {0,0,0,0,0},/*14*/
    {0,0,0,0,0},/*15*/
    {0,0,0,0,0}/*16*/
};
int ACTION[17][9] = {/*LR������action*/
    {51,5,52,51,51,51,51,4,6},//0
    {999,53,52,7,8,0,0,53,53},//1
    {-4,53,-4,-4,-4,9,10,53,53},//2
    {-7,0,-7,-7,-7,-7,-7,0,0},//3
    {-8,0,-8,-8,-8,-8,-8,0,0},//4
    {0,5,52,51,51,51,51,4,6},//5
    {-10,0,-10,-10,-10,-10,-10,0,0},//6
    {51,5,52,51,51,51,51,4,6},//7
    {51,5,52,51,51,51,51,4,6},//8
    {51,5,52,51,51,51,51,4,6},//9
    {51,5,52,51,51,51,51,4,6},//10
    {0,53,16,7,8,0,0,53,53},//11
    {-2,53,-2,-2,-2,9,10,53,53},//12
    {-3,53,-3,-3,-3,9,10,53,53},//13
    {-5,0,-5,-5,-5,-5,-5,0,0},//14
    {-6,0,-6,-6,-6,-6,-6,0,0},//15
    {-9,0,-9,-9,-9,-9,-9,0,0}//16
};

void TRANS();/*�������buffer�������ݰ��ַ�ת��Ϊ��Ӧ���Ŵ���code������*/
void GetFromCode();/*ȡ�õ�ǰ������Ŵ���Ԫ��*/
void PUSH(int A,int S);/*��ջ����*/
void POP();/*��ջ����*/
void SHITF();/*�������*/
void REDUCE();/*��Լ����*/
void ACC();/*���ܲ���*/ 
void E1();/*������*/
void E2();
void E3();
main()
{
    int c=1; 
    printf("��������ʽ,����$��β�����磺'a+b$'\n");
    scanf("%s",buffer);/*�����������ʽ��������buffer��*/
    printf("\n");
    TRANS();/*���ַ��͵�buffer�����������ַ�Ϊ��λ��ת��Ϊ��Ӧ���ţ���������������w��*/
    
    PUSH(0,0);/*״̬S0��ջ*/
    GetFromCode();//�����뻺������ȡһ���ַ� 
       
    while(flag){
        if( ACTION[analysis_stack[ip]][X] > 0 && ACTION[analysis_stack[ip]][X] <50 ){/*�����������*/
            SHITF();
            GetFromCode();
        }
        else if( ACTION[analysis_stack [ip]][X] < 0 ){/*���й�Լ����*/
            REDUCE();
        } 
        else if( ACTION[analysis_stack[ip]][X] == 999 ){/*�����ɹ�*/
            ACC();
        } 
        else
        {
            switch(ACTION[analysis_stack[ip]][X])
            {
                case 51: E1();break;
                case 52: E2();GetFromCode();break;
                case 53: E3();GetFromCode();break;
            }
            }
    }
    
    system("pause");
    return 0;
}
void TRANS(){/*�������buffer�������ݰ��ַ�ת��Ϊ��Ӧ���Ŵ���w������*/
    int x=0,y=0;/*xΪָ��buffer������±� */
    while(buffer[x]!='$'){
        if( buffer[x]>=48 && buffer[x]<=57 ){/*��ǰ�ַ�Ϊ���֣���num*/
            while( buffer[x]>=48 && buffer[x]<=57 ) x++;
            code[y++] = 8;/*��buffer����������w��д�����num��8,����y����*/
        }
        else if( (buffer[x]>=97 && buffer[x]<=122) || (buffer[x]>=65 && buffer[x]<=90) ){/*��ǰ�ַ�Ϊ��ĸ����id*/
            while( (buffer[x]>=97 && buffer[x]<=122) || (buffer[x]>=65 && buffer[x]<=90) ) x++;
            code[y++] = 7;/*��buffer����������w��д�����id��7������y����*/
        }
        else{
            switch(buffer[x++]){/*��buffer�е��ַ�Ϊһ������һ��ʱ���Զ�ת��Ϊ��Ӧ�Ĵ��Ŵ���w��*/ 
                case '&': code[y++] = 0;break;
                case '(': code[y++] = 1;break;
                case ')': code[y++] = 2;break;
                case '+': code[y++] = 3;break;
                case '-': code[y++] = 4;break;
                case '*': code[y++] = 5;break;
                case '/': code[y++] = 6;break;
            }
        }
    }
    code[y] = 0;
}
void GetFromCode(){/*ȡ�õ�ǰ������Ŵ���Ԫ��*/
    X = code[position++];
}
void PUSH(int A,int S){/*��ջ����*/
    ip++;/*��ջָ��ipָ������Ԫ�� */
    analysis_stack[ip] = A;/*������A����ջ��*/
    ip++;
    analysis_stack[ip] = S;/*��״̬S����ջ��*/
};
void POP(){/*��ջ����*/
    ip--;/*����һ��ջ��Ԫ�أ�ջָ��ip���ƣ�ָ���µ�ջ��*/
    ip--;
};
void SHITF(){/*�������*/
    int x;
    x = ACTION[analysis_stack[ip]][X];/*����goto����ȷ����ǰ����������������״̬*/
    PUSH(X,x);/*����ǰ������ַ���״̬ѹ��ջ*/
    printf("s%d\tShift in.\n",x);
}
void REDUCE(){/*��Լ����*/
    int x,y,z;
    x = -ACTION[analysis_stack[ip]][X];/*����action����ȷ����ǰ��Լ�����������ĸ�����ʽ��Լ*/
    printf("r%d\tReduce by\t",x);
    switch(production[x].Vn){
        case 101: printf("S -> ");break;
        case 102: printf("E -> ");break;
        case 103: printf("T -> ");break;
        case 104: printf("F -> ");break;
    }
    for(int i = 1; i <= production[x].size; i++){
        POP();/*��ջ��Ԫ�أ�����Լ����ʽ���Ҳ����Ƚ��е�������*/
        switch(production[x].Str[i]){
            case 0: printf("$");break;
            case 1: printf("(");break;
            case 2: printf(")");break;
            case 3: printf("+");break;
            case 4: printf("-");break;
            case 5: printf("*");break;
            case 6: printf("/");break;
            case 7: printf("id");break;
            case 8: printf("num");break;
            case 101: printf("S");break;
            case 102: printf("E");break;
            case 103: printf("T");break;
            case 104: printf("F");break;
        }
    }
    printf("\n");
    y = GOTO[analysis_stack[ip]][production[x].Vn-100];/*����goto����ȷ����Լ��ɺ���Ҫת����״̬*/
    PUSH(production[x].Vn,y);/*����Լ����ʽ����ѹ��ջ�У�������Ӧ��ת��״̬ѹ��ջ��*/
}
void ACC(){
    flag = 0;
    printf("Acc!\n");
}
void E1()
{//�ڴ�(������������ַ������������������$
    printf("e1\t\t\tȱ���������,idѹ��ջ\n"); 
    PUSH(7,4);
}
void E2()
{//���Ų�ƥ�䣬ɾ�������� 
    printf("e2\t\t\t���Ų�ƥ��,ɾ��������\n");
    
}
void E3()
{//�ڴ�������ţ�������(��������� 
    int pointer = position;
    switch(analysis_stack[ip])
    {
        case 1: PUSH(3,7);printf("e3\t\t\tȱ�������,����������ջ");break;
        case 2: case 12: case 13: PUSH(5,9);printf("e3\t\t\tȱ�������,����������ջ");break;
        case 11:
            if( code[pointer] >=3 && code[pointer] <=6 )//�ڴ��������
            {PUSH(2,16);printf("e3\t\t\tȱ��������,�����������ջ");}
            else if( code[pointer] >= 7 && code[pointer]<=8 )
            {PUSH(3,7);printf("e3\t\t\tȱ�������,����������ջ");}
            break;
    }
}

