#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int inf = 0x3f3f3f3f;
const int maxlevel = 50;
const int maxlength = 10000000;
const int skiprate = 35;

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
		node *down,*up;
		node *next;
		int key,value;
}; 
node *head,hbuffer[maxlevel];
node *rbuffer[maxlevel];
int tophead=0;
void init()
{
		for (int i=0;i<maxlevel-1;i++)
		{
				hbuffer[i].up = &hbuffer[i+1];
				hbuffer[i+1].down = &hbuffer[i];
		}
		for (int i=0;i<maxlevel;i++)
		{
				hbuffer[i].next = NULL;
				hbuffer[i].key = hbuffer[i].value = -inf;
		}
		int x = maxlength;
		for (int i=0;i<maxlevel;i++)
		{
				rbuffer[i] = (node*)malloc(x*sizeof(node));
				x=x*0.99;
		}
}
node *stack[maxlevel];
int tops=-1;
void insert(int key,int value)
{
		tops=-1;
		node *cur = &hbuffer[tophead];
		while (cur->down || (cur->next && cur->next->key<=key))
		{
				while (cur->next && cur->next->key<=key)
						cur = cur->next;
				if (cur->down)
				{
						stack[++tops]=cur;
						cur = cur->down;
				}
		}
		stack[++tops]=cur;
		if (cur->key == key)
		{
				while (cur)
				{
						cur->value = value;
						cur=cur->up;
				}
		}
		else
		{
				cur=stack[tops--];
				node *tmp = (rbuffer[0]++);
				tmp->key = key, tmp->value = value;
				tmp->up = NULL;
				tmp->next = cur->next;
				cur->next = tmp;
				int t=0;
				while (rand()%100<skiprate)
				{
						cur=~tops?stack[tops--]:&hbuffer[t+1];
						node *tmp2 = (rbuffer[++t]++);
						tmp2->key = key, tmp2->value = value;
						tmp2->down = tmp;
						tmp->up = tmp2;
						tmp2->next = cur->next;
						cur->next = tmp2;
						tmp2->up = NULL;
						tmp=tmp2;
				}
				tophead=max(tophead,t);
		}
}
int search(int key)
{
		node *cur = &hbuffer[tophead];
		while (cur->down || (cur->next && cur->next->key<=key))
		{
				while (cur->next && cur->next->key<=key)
						cur = cur->next;
				if (cur->down)
						cur = cur->down;
		}
		if (cur->key == key)
				return cur->value;
		else
				return -1;
}

int main()
{
		freopen("input.txt","r",stdin);
		//freopen("output.txt","w",stdout);
		int n,m;
		init();
		readInt(n);
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
						insert(x,y);
				}else
				{
						readInt(x);
						printf("%d\n",search(x));
				}
		}
}
