//Written By LXL
//Ratio Rotate Self Balancing Segment Tree
//Finger Tree
#include <iostream>
#include <stdio.h>
#define new_Node( s , v , m , a , b ) ( & ( * st[ cnt++ ] = Node( s , v , m , a , b ) ) )
#define merge( a , b ) new_Node( a -> size + b -> size , b -> value , 0 , a , b )
#define update( cur ) if( cur -> left -> size ) cur -> size = cur -> left -> size + cur -> right -> size , cur -> value = cur -> right -> value;
#define ratio 5

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

struct Node
{
	int size , value , num;
	Node * left , * right;
	Node( int s , int v , int m , Node * a , Node * b ) : size( s ) , value( v ) , num( m ) , left( a ) , right( b ) {}
	Node() {}
} * root , t[20000010] , * st[20000010] , * father , * null;

int cnt;

inline void rotate( bool x , register Node * cur )
{
	if( x ) cur -> left = merge( cur -> left , cur -> right -> left ) , st[ --cnt ] = cur -> right , cur -> right = cur -> right -> right;
	else cur -> right = merge( cur -> left -> right , cur -> right ) , st[ --cnt ] = cur -> left , cur -> left = cur -> left -> left;
}

inline void maintain( Node * cur )
{
	if( cur -> left -> size > cur -> right -> size * ratio ) rotate( 0 , cur );
	else if( cur -> right -> size > cur -> left -> size * ratio ) rotate( 1 , cur );
	if( cur -> left -> size > cur -> right -> size * ratio ) rotate( 1 , cur -> left ) , rotate( 0 , cur );
	else if( cur -> right -> size > cur -> left -> size * ratio ) rotate( 0 , cur -> right ) , rotate( 1 , cur );
}

int find( int x , Node * cur )
{
	if( cur -> size == 1 ) return x == cur -> value ? cur -> num : -1;
	return find( x , x > cur -> left -> value ? cur -> right : cur -> left );
}

void insert( int x , int y , Node * cur )
{
	if( cur -> size == 1 )
		if( x > cur -> value ) cur -> left = new_Node( 1 , cur -> value , cur -> num , null , null ) , cur -> right = new_Node( 1 , x , y , null , null );
		else cur -> left = new_Node( 1 , x , y , null , null ) , cur -> right = new_Node( 1 , cur -> value , cur -> num , null , null );
	else maintain( cur ) , insert( x , y , x > cur -> left -> value ? cur -> right : cur -> left );
	update( cur );
}

void erase( int x , Node * cur )
{
	if( cur -> size == 1 )
		if( cur -> value == x ) * father = cur == father -> left ? * father -> right : * father -> left;
		else return;
	else maintain( cur ) , father = cur , erase( x , x > cur -> left -> value ? cur -> right : cur -> left );
	update( cur );
}

inline void init()
{
	for( register int i = 0 ; i < 20000010 ; i++ ) st[i] = & t[i];
	null = new_Node( 0 , 0 , 0 , 0 , 0 );
	root = new_Node( 1 , 2147483647 , 0 , null , null );
}

int n , opt , x , y;

int main()
{
		freopen("input.txt","r",stdin);
		freopen("output.txt","w",stdout);
	init();
	readInt(n);
	//scanf( "%d" , &n );
	while( n-- )
	{
			readInt(opt);
			readInt(x);
		//scanf( "%d %d" , &opt , &x );
		if( opt == 1 ) 
		{
				readInt(y);
				 insert( x , y , root );
		}
		else 
		{
				printf( "%d\n" , find( x , root ) );
		}
	}
	return 0;
}
