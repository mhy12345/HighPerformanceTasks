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

namespace task1//Simple Random
{
		void generate(int n,unsigned xrange,unsigned yrange,int rate=50)
		{
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
		void main ()
		{
				init();
				int rate[]={5,50,95};
				int total[]={10,1000,100000,1000000,10000000};
				unsigned rglist[]={100,100000,0xffffffffu};
				char cc[100];
				int cnt=0;
				for (int i=0;i<3;i++)
				{
						for (int j=0;j<3;j++)
						{
								for (int k=0;k<5;k++)
								{
										fprintf(stderr,"%d %d %d\n",i,j,k);
										++cnt;
										sprintf(cc,"a%d.txt",cnt);
										FILE *fdet = fopen(cc,"w");
										fprintf(fdet,"Rate:%d\n",rate[i]);
										fprintf(fdet,"Size:%d\n",total[k]);
										fprintf(fdet,"Range:%d\n",rglist[j]);
										fclose(fdet);
										sprintf(cc,"a%d.in",cnt);
										freopen(cc,"w",stdout);
										generate(total[k],rglist[j],rglist[j],rate[i]);
										fclose(stdout);
								}
						}
				}
		}
}
namespace task2
{
		vector<unsigned> seq;
		void generate(int n,unsigned xrange,unsigned yrange,int rate=50)
		{
				seq.clear();
				printf("%d\n",n);
				for (int i=0;i<n;i++)
				{
						int opt=rand()%100<rate?1:2;
						if (opt==2 && !seq.size())opt=1;
						if (opt==1)
						{
								unsigned x,y;
								x=randu(xrange),y=randu(yrange);
								seq.push_back(x);
								printf("1 %u %u\n",x,y);
						}
						else if (opt==2)
								printf("2 %u\n",seq[rand()%seq.size()]);
				}
		}
		void main ()
		{
				init();
				int rate[]={5,50,95};
				int total[]={10,1000,100000,1000000,10000000};
				unsigned rglist[]={100,100000,0xffffffffu};
				char cc[100];
				int cnt=0;
				for (int i=0;i<3;i++)
				{
						for (int j=0;j<3;j++)
						{
								for (int k=0;k<5;k++)
								{
										fprintf(stderr,"%d %d %d\n",i,j,k);
										++cnt;
										sprintf(cc,"b%d.txt",cnt);
										FILE *fdet = fopen(cc,"w");
										fprintf(fdet,"Rate:%d\n",rate[i]);
										fprintf(fdet,"Size:%d\n",total[k]);
										fprintf(fdet,"Range:%d\n",rglist[j]);
										fclose(fdet);
										sprintf(cc,"b%d.in",cnt);
										freopen(cc,"w",stdout);
										generate(total[k],rglist[j],rglist[j],rate[i]);
										fclose(stdout);
								}
						}
				}
		}
}

int main()
{
		task2::main();
}
