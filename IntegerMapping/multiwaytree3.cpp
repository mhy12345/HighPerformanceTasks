#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<map>
#include<ext/pb_ds/assoc_container.hpp>
using namespace std;
//#define map __gnu_pbds::cc_hash_table
const int totdigit=30;
const int skiplen=10;
const int expandsize = (1<<3);
const int maxn = 10000000;

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
		map<unsigned,node*> *ptr;
		node** array;
		int value;
}trie[maxn];
int topt=0;
void Insert(node*& now,unsigned key,int value,int cur=totdigit)
{
		if (!now)
		{
				now=trie+(++topt);
				now->value=0;
				now->array=NULL;
				now->ptr = new map<unsigned,node*>();
		}
		if (!cur)
		{
				now->value=value;
				return ;
		}
		if (now->array)
		{
				int t=(key>>(cur-skiplen))&((1u<<skiplen)-1);
				Insert(now->array[t],key,value,cur-skiplen);
				return ;
		}
		int t=(key>>(cur-skiplen))&((1u<<skiplen)-1);
		Insert((*(now->ptr))[t],key,value,cur-skiplen);
		if (now->ptr->size()>expandsize)
		{
				now->array=(node**)calloc((1u<<skiplen),sizeof(node*));
				for (map<unsigned,node*>::iterator it1=now->ptr->begin();it1!=now->ptr->end();it1++)
						now->array[it1->first]=it1->second;
				delete now->ptr;
		}
}
int Find(node* now,unsigned key,int cur=32)
{
		if (!now)return -1;
		if (!cur)return now->value;
		int t=(key>>(cur-skiplen))&((1u<<skiplen)-1);
		if (now->array)
				return Find(now->array[t],key,cur-skiplen);
		else
				return Find((*(now->ptr))[t],key,cur-skiplen);
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
