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
const int dlen = 23;
const int hlen = 32;
struct node
{
		node *lch,*rch;
		int value,weight,key;
}treap[maxn];
node *troot[1<<dlen];
int topt=0;
inline void l_rotate(node *&now)
{
		register node* t=now->rch;
		now->rch=t->lch;
		t->lch=now;
		now=t;
}
inline void r_rotate(node *&now)
{
		register node* t=now->lch;
		now->lch=t->rch;
		t->rch=now;
		now=t;
}
static unsigned long next = 1;

/* RAND_MAX assumed to be 32767 */
int myrand(void) {
		    next = next * 1103515245 + 12345;
			    return((unsigned)(next/65536) % 32768);
}

void mysrand(unsigned seed) {
		    next = seed;
}

void Insert(node *&now,int k,int v)
{
		if (!now)
		{
				now=treap+(++topt);
				now->weight=myrand();
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
node** stack[dlen];
int tops=-1;
void Insert2(node **now,int k,int v)
{
		while (*now)
		{
				stack[++tops]=now;
				if ((*now) -> key == k)
				{
						(*now) ->value = v;
						tops=-1;
						return ;
				}
				if (k < (*now)->key)
						now = &((*now) -> lch);
				else
						now = &((*now) -> rch);
		}
		(*now)=treap+(++topt);
		(*now)->weight=myrand();
		(*now)->key=k;
		(*now)->value=v;
		while (~tops)
		{
				now=stack[tops--];
				if ((*now)->lch && (*now)->lch->weight>(*now)->weight)
						r_rotate(*now);
				if ((*now)->rch && (*now)->rch->weight>(*now)->weight)
						l_rotate(*now);
		}
}
int Find(node* now,int k)
{
		if (!now)return -1;
		if (now->key==k)return now->value;
		if (k<now->key)
				return Find(now->lch,k);
		else
				return Find(now->rch,k);

}
int Find2(node* now,int k)
{
		while (now)
		{
				if (now->key == k)return now->value;
				if (k < now->key)
						now = now->lch;
				else
						now = now->rch;
		}
		return -1;
}
char wbuf[30];
inline void writeInt(register int x)
{
		register char* wcur= wbuf+28;
		register bool flag=false;
		if (x<0)x=-x,flag=true;
		if (!x)*(wcur--)='0';
		while (x)
		{
				*(wcur--)=x%10+'0';
				x/=10;
		}
		if (flag)*(wcur--)='-';
		puts(wcur+1);
}

int main()
{
		freopen("input.txt","r",stdin);
		freopen("output.txt","w",stdout);
		int n,m;
		n=10000000;
		//readInt(n);
		//scanf("%d",&n);
		while (n--)
		{
				//if (rand()%100000==0)cerr<<topt<<endl;
				int opt;
				int x,y;
				opt=myrand()%2+1;
				//readInt(opt);
				if (opt==1)
				{
						x=myrand()*myrand();
						y=myrand()*myrand();
					//	readInt(x);
					//	readInt(y);
						//Insert(troot[x&((1u<<dlen)-1)],x>>dlen,y);
						Insert2(&troot[x&((1u<<dlen)-1)],x>>dlen,y);
				}else
				{
						x=myrand()*myrand();
						//readInt(x);
						//printf("%d\n",Find(troot[x&((1u<<dlen)-1)],x>>dlen));
						//writeInt(Find(troot[x&((1u<<dlen)-1)],x>>dlen));
						//writeInt(Find2(troot[x&((1u<<dlen)-1)],x>>dlen));
						Find2(troot[x&((1u<<dlen)-1)],x>>dlen);
				}
		}
}
