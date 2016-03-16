#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
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
		short key;
		ptr_t* next;
		node* ptr;
}ptrbuf[maxp],*topptr=ptrbuf;
ptr_t *trash[maxp];
int toptrash;
struct node
{
		int totrope;
		ptr_t* first;
		node** array;
		int value;
}trie[maxn];
int topt=0;
void Insert(node*& now,unsigned key,int value,int cur=32)
{
		if (!now)
		{
				now=trie+(++topt);
				now->totrope=0;
				now->value=0;
		}
		if (!cur)
		{
				now->value=value;
				return ;
		}
		if (now->totrope==-1)
		{
				int t=(key>>(cur-skiplen))&((1u<<skiplen)-1);
				Insert(now->array[t],key,value,cur-skiplen);
				return ;
		}
		for (ptr_t* np=now->first;np;np=np->next)
		{
				if (np->key == ((key>>(cur-skiplen))&((1u<<skiplen)-1)))
				{
						Insert(np->ptr,key,value,cur-skiplen);
						return ;
				}
		}
		int t=(key>>(cur-skiplen))&((1u<<skiplen)-1);
		ptr_t* tmp;
		tmp=toptrash?trash[toptrash--]:(topptr++);
		tmp->next=now->first;
		tmp->key=t;
		tmp->ptr=NULL;
		now->first=tmp;
		now->totrope++;
		Insert(tmp->ptr,key,value,cur-skiplen);
		if (now->totrope>(1u<<skiplen>>2))
		{
				now->array=(node**)calloc((1u<<skiplen),sizeof(node*));
				now->totrope=-1;
				for (ptr_t *np=now->first;np;np=np->next)
				{
						now->array[np->key]=np->ptr;
						trash[++toptrash]=np;
				}
				now->totrope=-1;
		}
}
int Find(node* now,unsigned key,int cur=32)
{
		if (!now)return 0;
		if (!cur)return now->value;
		int t=(key>>(cur-skiplen))&((1u<<skiplen)-1);
		if (now->totrope==-1)
				return Find(now->array[t],key,cur-skiplen);
		else
		{
				for (ptr_t* np=now->first;np;np=np->next)
				{
						if (np->key == t)
								return Find(np->ptr,key,cur-skiplen);
				}
				return 0;
		}
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
						printf("%d\n",Find(troot,x));
				}
		}
}
