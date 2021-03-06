// CalcJoey.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<ctime>
#include"cstdio"
#include"cstring"
using namespace std;
#define MAX 20000000//求MAX范围内的素数
long long su[MAX], cnt;
bool isprime[MAX];


void prime()
{
	FILE *ofile;
	errno_t oerr;
	oerr = fopen_s(&ofile, "prime.txt", "w");

	cnt = 1;
	memset(isprime, 0, sizeof(isprime));//初始化认为所有数都为非素数

	for (long long i = 2;i <= MAX;i++)
	{
		if (!isprime[i])//保存素数
		{
			su[cnt++] = i;
			fprintf(ofile, "%I64d\n", i);
		}
		for (long long j = i * 2;j < MAX;j += i)//素数的倍数都为合数
		{
			isprime[j] = 1;
		}
	}


}

int prime2() {
	FILE *ofile;
	errno_t oerr;
	oerr = fopen_s(&ofile, "prime2.txt", "w");

	int i,j,len = 0;
	int JoeyCount = 0;
	int JoeySum = 0;

	memset(isprime, 0, sizeof(isprime));//初始化认为所有数都为非素数

	for (i = 2; i <= MAX; i++)
	{
		if (JoeyCount<333333)
		{
			if (!isprime[i]) {
				su[len++] = i;
				if (i % 100 == 3 or i % 100 == 9
					or i % 100 == 13 or i % 100 == 23
					or i % 100 == 27 or i % 100 == 33
					or i % 100 == 43 or i % 100 == 53
					or i % 100 == 63 or i % 100 == 73
					or i % 100 == 81 or i % 100 == 83
					or i % 100 == 93 or i % 100 == 99)
				{
					JoeyCount++;
					JoeySum = JoeySum + i;
					fprintf(ofile, "%d\n", i);
				}

			}
			for (j = 0; j < len &&su[j] * i <= MAX; j++)
			{
				isprime[su[j] * i] = 1;
				if (i % su[j] == 0) break;
			}
		}
		else break;
	}
	return JoeySum;
}

int main()
{
	clock_t begin, end;
	int Sum;

	begin = clock();
	Sum=prime2();
	end = clock();
	printf("Joey Number Sum :%d\n", Sum);
	printf("Prime2 Time used:%d ms\n", end - begin);

	return 0;
}