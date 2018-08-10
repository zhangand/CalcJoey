// CalcJoey.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<ctime>
#include"cstdio"
#include"cmath"
#include"cstring"
using namespace std;
#define MAX 20000000//assume max N is 20M
long su[MAX/2-1];
bool isprime[MAX];

//Method 1

unsigned __int64 euler_sieve_JoeySum()
{
	int i, j, len = 0;
	int JoeyCnt = 0;
	__int64 Sum = 0;

	//init all flag as false
	memset(isprime, 0, sizeof(isprime));
	for (i = 2; i <= MAX; i++)
	{
		if (JoeyCnt < 333333)
		{
			if (!isprime[i])
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
				isprime[su[j] * i] = 1;
				if (i % su[j] == 0) break;
			}
		}
		else break;
	}
	return Sum;
}

//Method 2
long * eratosthenes_sieve()
{
	int i, j, t;
	//init su[Max] with odd numbers[3,5,7,...]
	for (i = 0;i < MAX/2; i++)
		su[i] = 2 * i + 3;
	//i*(2*i+6)+3<MAX,i<=(sqrt(3+2*MAX)-3)/2
	t = (int)(sqrt(2 * MAX) / 2);
	for (i=0;i<=t;i++)
	{
		if (su[i])
		{
			for (j  = i*(2*i+6)+3; j < MAX/2; j+=2*i+3)
			{
				su[j] = 0;
			}
		}
	}
	return su;
}


__int64  CalcJoey(long *InputList)
{
	__int64 Sum = 0;
	int JoeyCnt = 0;

	for (int i = 0; i < MAX/2; i++)
	{
		if (JoeyCnt<333333)
		{
			if (*(InputList + i))
			{
				if (*(InputList + i) % 100 % 9 == 0 or *(InputList + i) % 10 == 3)
				{
					Sum = Sum + *(InputList + i);
					JoeyCnt++;
				}
			}
		}
		else break;
	}
	return Sum;

}

int main()
{
	clock_t begin, middle, end;
	unsigned __int64 JoeySum = 0;
	long *primeList;

	//optimized Sieve of Eratosthenes
	begin = clock();
	primeList = eratosthenes_sieve();
	end = clock();
	middle = clock();
	printf("\nEratosthenes_sieve Prime Time used:%d ms\n", middle - begin);

	JoeySum = CalcJoey(primeList);
	end = clock();
	printf("Eratosthenes_sieve Calc Joey Time used:%d ms\n", end - middle);
	printf("Eratosthenes_sieve Joey Number Sum :%I64u\n", JoeySum);
	printf("Total Run Time :%d ms\n", end - begin);



	//Sieve of Euler, and calc Joey Sum directly 
	begin = clock();
	printf("\nTunkey solution Joey Number Sum :%I64u\n", euler_sieve_JoeySum());
	end = clock();
	printf("Total Run Time :%d ms\n", end - begin);

	system("pause");
	return 0;
}