#include<math.h>
#include<iostream>
#include<random>
#include <ctime>
#include <iomanip>
#include "windows.h"
#include "mpi.h"
using std::cout; using std::endl;


//��¼�е�ֵ
long double PI = 0.0;
//��¼ÿ���������������ĺ�
long double ValueSum = 0.0;
//��������PI�Ŀ�ʼʱ�������ʱ��
long double StartTime, EndTime;
//��������,����ID
int Size, MyID;
//PI�����ۼӴ���,  �����޸����ڲ��ԣ�
long double N = 1e8; 
//ʵ��PIֵ
long double Actual_PI = 3.141592653589793238462643;


//1.������ּ���PIֵ
inline void areaIntegral() {
	long double X;
	//������ο��
	long double rectangleWide = 1.0 / N;
	//���ݽ���ID ����ÿ�����εĸ߶�,����� myid = 0 ���� ��1 5 9 14 ... myid = 2 ���� ��2 6 10 15... 
	for (int i = MyID + 1; i <= N; i += Size) {       //i = myid* n/size; i<= (myid+1) * n/size; i++Ҳ��.   
		X = rectangleWide * ((long double)i - 0.5);       //��i������x����            
		ValueSum = ValueSum + (4.0 / (1 + X * X));      //���θ߶��ۼ�               
	}
	//��������� ��*��
	ValueSum *= rectangleWide;
}


inline long double arctg(int i, int value)
{
	double result = pow(-1, (i % 2)) / ((2.0 * i + 1.0) * pow(value, 2 * i + 1));
	return result;
}

//2.�ݼ���(MyID + 1) * N / Size
inline void powerSeries() {
	for (long double i = MyID * N / Size; i < (MyID + 1) * N / Size; i++)
		ValueSum += arctg((int)i, 1);
			
	ValueSum *= 4;
}


//3.�Ľ����ݼ���
inline void powerSeriesImprove()
{
	for (long double i = MyID * N / Size; i < (MyID + 1) * N / Size; i++)
		ValueSum += 4 * arctg((int)i,5) - arctg((int)i, 239);

	ValueSum *= 4;
}

//4.���ؿ���ķ�ʽ
inline void MonteCarlo()
{
	long double randomFrequency = N / Size;
	long double count = 0.0;
	long double x, y;

	for (int i = 0; i < randomFrequency; i++)
	{
		x = rand() / double(RAND_MAX); //���������0~1
		y = rand() / double(RAND_MAX);
		if (sqrt(x * x + y * y) <= 1)
			count++;
	}
	ValueSum = 4.0 * count / (randomFrequency * Size);
}

//5.������ֵķ���
inline void powerSeriesIm()
{
	long double randomFrequency = N / Size;
	long double X = 0.0;
	long double rectangleWide = 1.0 / N;
	for (int i = 0; i < randomFrequency; i++)
	{
		X = rand() / double(RAND_MAX);  //���������0~1
		ValueSum = ValueSum + (4.0 / (1.0 + X * X));//���θ߶��ۼ�
	}
	// ������� ��*��
	ValueSum *= rectangleWide;
}

//6.���￵���㷨
inline void JinTianKangZheng()
{
	for (long double i = ceil(MyID * N / Size); i < ceil((MyID + 1) * N / Size); i++)
	{
		ValueSum += 12 * arctg((int)i, 49) + 32 * arctg((int)i, 57) - 5 * arctg((int)i, 239) + 12 * arctg((int)i, 110443);
	}
	ValueSum *= 4;
}

inline long double fac(int n)
{
	long double sum = 1;
	for (int i = 1; i <= n; i++)
		sum *= i;
	return sum;
}

//7.Chudnovsky�㷨
inline void Chudnovsky()
{
	long double part1 = 0;
	long double part2 = 0;
	long double P61 = sqrt(61);
	long double A = 1657145277365 + 212175710912 * P61;
	long double B = 107578229802750 + 13773980892672 * P61;
	long double C = 5280 * (236674 + 30303 * P61);

	for (int i = (int)(MyID * N / Size); i < (MyID + 1) * N / Size; i++)
	{
		part1 = pow(-1, (i % 2)) * fac(6 * i) / 3.0 * fac(i) * pow(fac(i), 3);
		part2 = A * i + B / pow(C, 3 * i + 1.5);
		cout << "part1:" << part1 << "   part2:" << part2 << endl;
		ValueSum += part1 * part2;
	}
	ValueSum *= 12;
	ValueSum = 1/ValueSum;
}


int main(int argc, char* argv[]) {
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &MyID);
	MPI_Comm_size(MPI_COMM_WORLD, &Size);
	cout << "����" << MyID << "����" << endl;

	if (0 == MyID) { StartTime = MPI_Wtime(); 	srand((int)time(0));}
	MPI_Bcast(&N, 1, MPI_INT, 0, MPI_COMM_WORLD);  //��N�㲥�����н�����
	//1.������ּ���PIֵ ����N�ķ�Χ 1e3~1e7
	areaIntegral();

	//2.�ݼ������ּ���PIֵ ����N�ķ�Χ 1e3~1e7
	//powerSeries();

	//3.�Ľ��ݼ��� ����N�ķ�Χ 1e3~1e7
	//powerSeriesImprove()

	//4.���ؿ������PIֵ ����N�ķ�Χ 1e3~1e7
	//MonteCarlo();

	//5.������ֵķ��� ����N�ķ�Χ 1e3~1e7
	//powerSeriesIm();

	//6.���￵���㷨 ����N�ķ�Χ 2~10
	//JinTianKangZheng()

	//7.Chudnovsky�㷨 ����N�ķ�Χ 1~5
	//Chudnovsky();

	//����Reduce���������н��̵�ValueSum�ۼӵ�root����(0)��PI��������
	MPI_Reduce(&ValueSum, &PI, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);  


	if (0 == MyID) {
		EndTime = MPI_Wtime();
		auto deviation = PI - Actual_PI;
		cout << endl;
		cout << "�����PIֵΪ:" << std::setprecision(24) << PI << endl;
		cout << "ʵ�ʵ�PIֵΪ:" << Actual_PI << endl;
		cout << "PI�����Ϊ:" << std::setprecision(24) << deviation << endl;
		cout << "�ܹ���ʱΪ:" << EndTime - StartTime << endl;
	}
	MPI_Finalize();
	return 0;
}