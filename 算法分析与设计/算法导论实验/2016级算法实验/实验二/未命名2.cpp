#include <iostream>
#include <fstream>
#include <algorithm>
#include <bits/stdc++.h>
using namespace std;

const int MAX = 50;
int board[MAX][MAX];  //��¼���񱻼������
int root[MAX][MAX];      //��¼������λ��
int m, n;             //����Ϊ m * n
int k = 0;                //�����˸���
int bestk;

void compute()
{
    memset(root, 0, sizeof(root));
    bool ok = false;
    int i, k;
    if(m == 1)  //����ֻ��һ�е����
    {
        k = n / 3;
        if(n%3 == 1)
        {
            for(i=0; i<=k; i++)
                root[1][3*i+1] = 1;
        }
        else
        {
            if(n%3 == 0)
                k--;
            for(i=0; i<=k; i++)
                root[1][3*i+2] = 1;
        }
        bestk = k + 1;
        ok = true;
    }
    if(n == 1) //����ֻ��һ�е����
    {
        k = m / 3;
        if(m%3 == 1)
        {
            for(i=0; i<=k; i++)
                root[1][3*i+1] = 1;
        }
        else
        {
            if(m%3 == 0)
                k--;
            for(i=0; i<=k; i++)
                root[1][3*i+2] = 1;
        }
        bestk = k + 1;
        ok = true;
    }
    if(m==2 && n%2 == 1) //������2�У�������Ϊ����
    {
        int k = n / 4;
        if(m%4 == 0)
            k--;
        for(i=0; i<=k; i++)
        {
            root[1][4*i+3] = 1;
            root[2][4*i+1] = 1;
        }
        bestk = 2 * k + 2;
        ok = true;
    }
    if(n==2 && m%2 == 1) //������2�У�������Ϊ����
    {
        int k = m / 4;
        if(n%4 == 0)
            k--;
        for(i=0; i<=k; i++)
        {
            root[1][4*i+3] = 1;
            root[2][4*i+1] = 1;
        }
        bestk = 2 * k + 2;
        ok = true;
    }
    if(n==4 && m==4)  //4��4��
    {
        root[1][1] = 1;
        root[1][4] = 1;
        root[4][1] = 1;
        root[4][4] = 1;
        bestk = 4;
        ok = true;
    }
    if(ok)
    {
        //cout << "���ٵĻ����˸���Ϊ��" << bestk << endl;
        //cout << "������λ��Ϊ��\n";
        for(int i=1; i<=m; i++)
        {
            for(int j=1; j<=n; j++)
                cout << root[i][j] << " ";
            cout << endl;
        }
    }
    else
        cout << "-1\n";
}

int main()
{
    while(cin >> m>>n){
    compute();
    cout << endl;
    }
    return 0;
}
