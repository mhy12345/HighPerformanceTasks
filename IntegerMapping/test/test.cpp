#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

int main()
{
		char cc[100];
		for (int i=1;i<=45;i++)
		{
				sprintf(cc,"./sqlmap <b%d.in >b%d.out",i,i);
				system(cc);
				sprintf(cc,"diff b%d.ans b%d.out",i,i);
				if (system(cc))
						break;
				printf("%d\n",i);
		}
}
