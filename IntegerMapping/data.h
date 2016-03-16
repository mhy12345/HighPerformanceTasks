#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;

void init()
{
		FILE *fin = fopen("count.txt","r");
		int x=0;
		if (fin)fscanf(fin,"%d",&x);
		srand(x);
		if (fin)fclose(fin);
		FILE *fout = fopen("count.txt","w");
		fprintf(fout,"%d\n",x+1);
		fclose(fout);
		fprintf(stderr,"SEED:%d\n",x+1);
}
