#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cassert>
using namespace std;
const int startskip = 4;
const int maxn = 10000000;
const int maxlevel = 32;
const int memlimit = 30000000;
const int maxnode = memlimit < (long long)maxn*maxlevel ? memlimit : maxn*maxlevel;
const int maxstack = maxlevel + (1<<16);
int totmem=0;

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
		short skip;
		unsigned totb;
		node** array;
		unsigned value;
}tree[maxnode];
node* trash[maxnode];
int toptrash=-1;
int topt=0;
node* ptr[maxlevel][maxlevel];
node* expand_ptr;
int expand_level;

void Insert(node*& now,unsigned key,unsigned value,int cur=32)
{
		if (!now)
		{
				node **cp = ptr[cur];
				while (*cp)(*(cp++))->totb++;
				now = ~toptrash ? trash[toptrash--] : tree + (++topt);
				assert(topt<memlimit);
				now->skip = startskip;
				now->array = (node**)calloc(1u<<startskip,sizeof(node*));
				totmem+=(1u<<startskip)*sizeof(node*);
				now->totb = 0;
		}
		if (!cur)
		{
				now->value = value;
				return ;
		}
		node **cp;
		if (cur>=now->skip*2)
		{
				cp = ptr[cur - now->skip*2];
				while (*cp)cp++;
				*cp = now;
		}
		unsigned t = (key>>(cur-now->skip)) & ((1u<<now->skip)-1);
		Insert(now->array[t],key,value,cur-now->skip);
		if (cur>=now->skip*2)
				*cp = NULL;
		if ((now -> totb > (1u<<now->skip>>1u)) && ((1u << now->skip >>1u) != (cur&(-cur))) && now->skip<16)
				expand_ptr = now;
}
node* stackp[maxstack];int tops=-1;
short stackl[maxstack];
unsigned stackv[maxstack];
void Expand(node* root)
{
		node *now;
		node **narray = (node**)calloc(1u<<root->skip<<root->skip,sizeof(node*));
		root->totb = 0;
		++tops;
		stackp[0]=root;
		stackl[0]=0;
		stackv[0]=0;
		short clevel;
		unsigned ckey;
		while (~tops)
		{
				clevel = stackl[tops];
				ckey = stackv[tops];
				now = stackp[tops--];
				if (clevel == root->skip*2)
						narray[ckey] = now;
				if (clevel == root->skip*4)
				{
						root->totb ++;
						continue;
				}
				for (int i=0;i<(1<<now->skip);i++)
				{
						if (now->array[i])
						{
								stackp[++tops]=now->array[i];
								stackv[tops]=(ckey<<now->skip) + i;
								stackl[tops]=(short)(clevel + now->skip);
								if ((short)(clevel + now->skip) < root->skip*2)
										trash[++toptrash]=now->array[i];
						}
				}
		}
		free(root->array);
		root->array = narray;
		root->skip<<=1;
}
unsigned Find(node* now,unsigned key,int cur=32)
{
		if (!now)return ~0;
		if (!cur)return now->value;
		unsigned t = (key>>(cur-now->skip)) & ((1u<<now->skip)-1);
		return Find(now->array[t],key,cur-now->skip);
}
inline void bit_reverse(unsigned &v)
{
		v = ((v >> 1) & 0x55555555) | ((v & 0x55555555) << 1);
		v = ((v >> 2) & 0x33333333) | ((v & 0x33333333) << 2);
		v = ((v >> 4) & 0x0F0F0F0F) | ((v & 0x0F0F0F0F) << 4);
		v = ((v >> 8) & 0x00FF00FF) | ((v & 0x00FF00FF) << 8);
		v = ( v >> 16             ) | ( v               << 16);
}

int main()
{
		freopen("input.txt","r",stdin);
		freopen("output.txt","w",stdout);
		int n,m;
		node *troot = NULL;
		readInt(n);
		//scanf("%d",&n);
		while (n--)
		{
				int opt;
				unsigned x,y;
				readInt(opt);
				if (opt==1)
				{
						readInt(x);
						readInt(y);
						bit_reverse(x);
						Insert(troot,x,y);
						if (expand_ptr)
						{
								Expand(expand_ptr);
								//cout<<expand_ptr<<endl;
						}
						expand_ptr = NULL;
				}else
				{
						readInt(x);
						bit_reverse(x);
						printf("%d\n",Find(troot,x));
				}
		}
		cerr<<topt<<endl;
		cerr<<totmem<<endl;
}
