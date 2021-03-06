// CalcJoey.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<ctime>
#include"cstdio"
#include"cmath"
#include"cstring"
using namespace std;
#define MAX 20000000//assume max N is 20M
#define PRIME_LIM 2000000//assume max prime number count less than 2M with 0~20M
long su[PRIME_LIM];
bool isprimeFlag[MAX];

//Method 1

unsigned __int64 euler_sieve_JoeySum()
{
	int i, j, len = 0;
	int JoeyCnt = 0;
	__int64 Sum = 0;

	//init all flag as false
	memset(isprimeFlag, 0, sizeof(isprimeFlag));
	for (i = 2; i <= MAX; i++)
	{
		if (JoeyCnt < 333333)
		{
			if (!isprimeFlag[i])
			{
				su[len++] = i;
				if (i% 100 % 9 == 0 or i % 10 == 3)
				{
					Sum = Sum + + i;
					JoeyCnt++;
				}
			}
			for (j = 0; j < len &&su[j] * i <= MAX; j++)
			{
				isprimeFlag[su[j] * i] = 1;
				if (i % su[j] == 0) break;
			}
		}
		else break;
	}
	return Sum;
}

long primes[PRIME_LIM] = { 0 };
long isprimeFlag2[MAX / 96 + 1] = { 0 };

//Method 2
__int64 euler_sieve_JoeySum2()
{
	int JoeyCnt = 0;
	__int64 Sum = 3;

	int nu = 5, to = 0;
	primes[0] = 2;
	primes[1] = 3;
	for (int i = 0; nu <= MAX; i++)
	{
		if (JoeyCnt < 333332)
		{
			if (!(isprimeFlag2[i >> 5] & (1 << (i & 31))))
			{
				primes[++primes[0]] = nu;
				if (nu % 100 % 9 == 0 or nu % 10 == 3)
				{
					Sum = Sum + +nu;
					JoeyCnt++;
				}
			}
			for (int j = 3; j <= primes[0] && primes[j] * nu <= MAX; j++)
			{
				to = (nu * primes[j] - 5) >> 1;
				to -= to / 3;
				isprimeFlag2[to >> 5] |= 1 << (to & 31);
				if (!(nu % primes[j])) break;
			}
			nu += 2 + ((i & 1) << 1);
		}
		else break;
	}
	return Sum;
}

int main()
{
	clock_t begin, end;
	unsigned __int64 JoeySum = 0;

	//Sieve of Euler, and calc Joey Sum directly 
	begin = clock();
	printf("\nEeuler solution Joey Number Sum :%I64u\n", euler_sieve_JoeySum());
	end = clock();
	printf("Total Run Time :%d ms\n", end - begin);

	//optimized Sieve of Euler
	begin = clock();
	printf("\nOptimized solution Joey Number Sum :%I64u\n", euler_sieve_JoeySum2());
	end = clock();
	printf("Total Run Time :%d ms\n", end - begin);
	
	system("pause");
	return 0;
}