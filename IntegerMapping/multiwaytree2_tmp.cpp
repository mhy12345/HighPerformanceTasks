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
struct node;
struct ptr_t
{
		unsigned key;
		ptr_t* next;
		node* ptr;
}ptrbuf[maxp],*topptr=ptrbuf;
ptr_t *trash[maxp];
int toptrash;
struct node
{
		int totrope;
		int step;
		int skip;
		ptr_t* first;
		node** array;
		int value;
}trie[maxn];
int topt=0;
void Insert(node* now,unsigned key,int value,int cur=32)
{
		assert(now);
		if (!cur)
		{
				now->value=value;
				return ;
		}
		if (now->step==0)
		{
				unsigned t=(key>>(cur-now->step))&((1<<now->step)-1);
				for (ptr_t* np=now->first;np;np=np->next)
				{
						if (ne->value==t)
						{
								Insert(np->ptr,key,value,cur-now->step);
								return ;
						}
				}
				tmp=toptrash?trash[toptrash--]:(topptr++);
				tmp->key=t;
				tmp->ptr=++topt;
				now->ptr=tmp;
				tmp->next=now->first;
				now->first=tmp;
		}else
		{
		}
}

int main()
{
		freopen("input.txt","r",stdin);
		freopen("output.txt","w",stdout);
		int n,m;
		readInt(n);
		node* troot=trie+(++topt);
		troot->skip=32;
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
						printf("%d\n",Find(troot,x));
				}
		}
}
