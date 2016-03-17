#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include "data.h"
using namespace std;
inline unsigned randu(unsigned range)
{
		unsigned ret=(unsigned)rand()+(unsigned)rand()+(unsigned)rand();
		return ret%range;
}

int main()
{
		freopen("input.txt","w",stdout);
		init();
		const int xrange = 1000000000;
		const int yrange = 1000000000;
		const int rate = 50;
		int n=10000000;
		printf("%d\n",n);
		for (int i=0;i<n;i++)
		{
				int opt=rand()%100<rate?1:2;
				if (opt==1)
						printf("1 %u %u\n",randu(xrange),randu(yrange));
				else if (opt==2)
						printf("2 %u\n",randu(xrange));
		}
}
