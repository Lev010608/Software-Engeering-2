/*
*�㷨����ʵ��� 
* 
*���ݷ����ͼ��ɫ���� 
*by TY 20181101 
*
*��Ŀ���ã����û����붥����������ɫ��Ŀ������������ͼ���ڽӾ���������������ɫ���� 
*
*/ 

#include "cstdio"
#include "cstring"
int color[500];
bool ok(int k,int c[][100])
{
    for(int i=1;i<k;i++)
    {
        if(c[k][i]==1&&color[i]==color[k])///���Ѿ���ɫ�� ��֮�����Ķ������ͬɫ���
            return false;
    }
    return true;
}
int graphColor(int n,int m,int c[][100])
{
    int cnt=0;
    memset(color,0,sizeof(color));
    int k=1;
    while(k>=1)
    {
        color[k]+=1;///Ⱦ��һ����ɫ
        while(color[k]<=m)
        {
            if(ok(k,c))
                break;
            else
                color[k]++;///������һ����ɫ
        }///��ѡ������ɫ
        if(color[k]<=m&&k==n)///����  ���
        {
            for(int i=1;i<=n;i++)
                printf("%d ",color[i]);
            printf("\n");
            cnt++;
        }
        else if(color[k]<=m&&k<n)
        {
            k++;///Ⱦ��һ������
        }
        else
        {
            color[k]=0;///���� ����������
            k--;
        }
    }
    return cnt;
}
int main()
{
    int n,m,i,j;
    int c[100][100];
    printf("���붥����n����ɫ��m:\n");
    scanf("%d %d",&n,&m);
    printf("��������ͼ���ڽӾ���:\n");
    for(i=1;i<=n;i++)
        for(j=1;j<=n;j++)
            scanf("%d",&c[i][j]);
    printf("��ɫ���п��ܵĽ�:\n");
    int cnt=graphColor(n,m,c);
    printf("������: %d\n",cnt);
}
