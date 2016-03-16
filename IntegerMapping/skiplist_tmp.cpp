#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int inf = 0x3f3f3f3f;
const int maxlevel = 50;
const int maxlength = 10000000;
const int skiprate = 70;
struct node
{
		node *down,*up;
		node *next;
		int key,value,size;
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
				hbuffer[i].size=0;
		}
		int x = maxlength;
		for (int i=0;i<maxlevel;i++)
		{
				rbuffer[i] = (node*)malloc(x*sizeof(node));
				x=x*2/3;
		}
}
int cnt;
void insert(int key,int value)
{
		cnt=0;
		node *cur = &hbuffer[tophead];
		while (cur->down || (cur->next && cur->next->key<=key))
		{
				while (cur->next && cur->next->key<=key)
				{
						cur = cur->next;
						cnt++;
				}
				if (cur->down)
				{
						cnt++;
						cur = cur->down;
				}
		}
		if (cur->key == key)
		{
				while (cur->key == key)
				{
						cnt++;
						cur->value = value;
						if (!cur->up)break;
						cur=cur->up;
				}
		}
		else
		{
				cnt+=5;
				node *tmp = (rbuffer[0]++);
				tmp->key = key, tmp->value = value;
				tmp->up = cur->up;
				tmp->next = cur->next;
				cur->next = tmp;
				tmp->size = 1;
				int t=0;
				while (rand()%100<skiprate)
				{
						cnt+=5;
						cur = cur->up;
						node *tmp2 = (rbuffer[++t]++);
						tmp2->key = key, tmp2->value = value;
						tmp2->size = 1;
						tmp2->down = tmp;
						tmp->up = tmp2;
						tmp2->next = cur->next;
						cur->next = tmp2;
						tmp2->up = cur->up;
						tmp=tmp2;
				}
				tophead=max(tophead,t);
				while (tmp->up)
				{
						cnt++;
						tmp = tmp->up;
						tmp->size++;
				}
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
				return 0;
}

int main()
{
		freopen("input.txt","r",stdin);
		freopen("output.txt","w",stdout);
		int n,m;
		init();
		scanf("%d",&n);
		while (n--)
		{
				int opt;
				int x,y;
				//if (n%1000==0)cerr<<n<<tophead<<endl;
				scanf("%d",&opt);
				if (opt==1)
				{
						scanf("%d%d",&x,&y);
						if (cnt>1000)
								--++cnt;
						insert(x,y);
						cerr<<cnt<<endl;
				}else
				{
						scanf("%d",&x);
						printf("%d\n",search(x));
				}
		}
}
