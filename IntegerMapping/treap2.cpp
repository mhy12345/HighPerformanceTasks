#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxbuf = 1000;
char buf[maxbuf];
int bufhead=0,buftail=0;
#define readChar()\
		(((bufhead == buftail)?(bufhead=0,buftail=(int)fread(buf,1,maxbuf,stdin)):0),buf[bufhead++])
#define readInt(t)\
{\
		register char ch; \
		register int _x = 0; \
		register bool flag = false;\
		while (ch = readChar(),ch!='-' && (ch>'9' || ch<'0'));\
		if (ch == '-')flag ^= 1,ch=readChar();\
		while (_x=_x*10+ch-'0',ch = readChar(), ch<='9' && ch>='0');\
		t=flag?-_x:_x;\
}

const int maxn = 10000000;
int L[maxn],R[maxn];
L[x] -> Node[x].L
int value[maxn],weight[maxn],key[maxn];
int topt=0;
void l_rotate(int &now)
{
		int t=R[now];
		R[now]=L[t];
		L[t]=now;
		now=t;
}
void r_rotate(int &now)
{
		int t=L[now];
		L[now]=R[t];
		R[t]=now;
		now=t;
}
void Insert(int &now,int k,int v)
{
		if (!now)
		{
				now=++topt;
				weight[now]=rand();
				key[now]=k;
				value[now]=v;
				return ;
		}
		if (key[now]==k)
		{
				value[now]=v;
				return ;
		}
		if (k<key[now])
		{
				Insert(L[now],k,v);
				if (weight[L[now]]>weight[now])
						r_rotate(now);
		}
		else
		{
				Insert(R[now],k,v);
				if (weight[R[now]]>weight[now])
						l_rotate(now);
		}
}
int Find(int now,int k)
{
		if (!now || key[now]==k)return value[now];
		if (k<key[now])
				return Find(L[now],k);
		else
				return Find(R[now],k);

}

int main()
{
		freopen("input.txt","r",stdin);
		freopen("output.txt","w",stdout);
		int n,m;
		readInt(n);
		int troot=0;
		//scanf("%d",&n);
		while (n--)
		{
				int opt;
				int x,y;
				readInt(opt);
				if (opt==1)
				{
						readInt(x);
						readInt(y);
						Insert(troot,x,y);
				}else
				{
						readInt(x);
						printf("%d\n",Find(troot,x));
				}
		}
}
