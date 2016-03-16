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
struct node
{
		node *lch,*rch;
		int value,weight,key;
}treap[maxn];
int topt=0;
void l_rotate(node *&now)
{
		node* t=now->rch;
		now->rch=t->lch;
		t->lch=now;
		now=t;
}
void r_rotate(node *&now)
{
		node* t=now->lch;
		now->lch=t->rch;
		t->rch=now;
		now=t;
}
void Insert(node *&now,int k,int v)
{
		if (!now)
		{
				now=treap+(++topt);
				now->weight=rand();
				now->key=k;
				now->value=v;
				return ;
		}
		if (now->key==k)
		{
				now->value=v;
				return ;
		}
		if (k<now->key)
		{
				Insert(now->lch,k,v);
				if (now->lch->weight>now->weight)
						r_rotate(now);
		}
		else
		{
				Insert(now->rch,k,v);
				if (now->rch->weight>now->weight)
						l_rotate(now);
		}
}
int Find(node* now,int k)
{
		if (!now)return 0;
		if (now->key==k)return now->value;
		if (k<now->key)
				return Find(now->lch,k);
		else
				return Find(now->rch,k);

}

int main()
{
		freopen("input.txt","r",stdin);
		freopen("output.txt","w",stdout);
		int n,m;
		readInt(n);
		node* troot=0;
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
