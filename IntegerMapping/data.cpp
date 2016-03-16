#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include "data.h"
using namespace std;

int main ()
{
		freopen("input.txt","w",stdout);
		init();
		int n = 10000000;
		int big = 10000000;
		printf("%d\n",n);
		for (int i=0;i<n;i++)
		{
				int opt=rand()%2;
				if (opt==0)
						printf("1 %d %d\n",rand()%big,rand()%big);
				else if (opt==1)
						printf("2 %d\n",rand()%big);
		}
}
