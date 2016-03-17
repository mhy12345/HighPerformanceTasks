#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<map>
using namespace std;
map<unsigned,int> mp;

const int maxbuf = 1000;
char buf[maxbuf];
int bufhead=0,buftail=0;
#define readChar()\
		(((bufhead == buftail)?(bufhead=0,buftail=fread(buf,1,maxbuf,stdin)):0),buf[bufhead++])
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

int main()
{
		//freopen("input.txt","r",stdin);
		//freopen("output.txt","w",stdout);
		int n;
		readInt(n);
		//scanf("%d",&n);
		while (n--)
		{
				int opt;
				int x,y;
				readInt(opt);
				//scanf("%d",&opt);
				if (opt==1)
				{
						readInt(x);
						readInt(y);
						//scanf("%d%d",&x,&y);
						mp[x]=y;
				}else
				{
						readInt(x);
						map<unsigned,int> :: iterator it1;
						it1=mp.find(x);
						if (it1==mp.end())
								printf("-1\n");
						else
								printf("%d\n",mp[x]);
						//scanf("%d",&x);
				}
		}
}
