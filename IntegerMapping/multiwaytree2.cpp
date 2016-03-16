#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cassert>
using namespace std;
const int inf = 0x3f3f3f3f;
int skiplen=8;
const int maxn = 10000000;
const int maxp = 10000000;
const int maxlevel = 64;

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
struct node
{
		int skip;
		int lev;
		node** array;
		int value;
}trie[maxn];
int topt=0;
bool flag[maxlevel];
int delta[maxlevel];
void Insert(node*& now,unsigned key,int value,int cur=32)
{
		if (!now)
		{
				now=trie+(++topt);
				now->lev=cur;
				now->skip=1;
				now->array=(node**)malloc(sizeof(node*)*2);
		}
		flag[cur]=1;
		unsigned t=(key>>(cur-now->skip))&((1<<now->skip)-1);
		if (!now->array[t])
		{
				int k=cur+(cur&(-cur));
				while (k<=32 && !flag[k])k+=k&(-k);
				delta[k]++;
		}
		Insert(now->array[t],key,value,cur-now->skip);
		flag[cur]=0;
		delta[k]=0;
}

int main()
{
		freopen("input.txt","r",stdin);
		freopen("output.txt","w",stdout);
		int n,m;
		readInt(n);
		node* troot=NULL;
		while (n--)
		{
				int opt;
				unsigned x;
				int y;
				readInt(opt);
				if (opt==1)
				{
						readInt(x);
						readInt(y);
						Insert(troot,x,y);
				}else
				{
						readInt(x);
				}
		}
}
