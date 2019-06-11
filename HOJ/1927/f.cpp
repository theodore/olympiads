#include <cstdio>
#include <cstring>
#define N ( 2 + n + n )

int n , m , g[ 2000 ] , pos[ 2000 ] , dist[ 2000 ] , pre[ 2000 ] , head , tail , ret = 0 , len = 0;
int queue[ 2000 ];
bool state[ 2000 ];
struct rec
{
	int c , e , next;
}edge[ 80000 ];
void addline( int x , int y , int z )
{
	edge[ ++len ].e = y;
	edge[ len ].c = z;
	edge[ len ].next = g[ x ];
	g[ x ] = len;
}

void init()
{
	scanf( "%d%d" , &n , &m );
	int t , a , b;
	for ( int i = 1 ; i <= n ; i++ )
	{
		scanf( "%d" , &t );
		addline( 1 , 1 + n + i , t );
		addline( 1 , 1 + i , 0 );
		addline( 1 + n + i , N , 0 );
	}
	for ( int i = 1 ; i <= m ; i++ )
	{
		scanf( "%d%d" , &a , &b );
		if ( a > b )
		{
			t = a;
			a = b;
			b = t;
		}
		scanf( "%d" , &t );
		addline( 1 + a , 1 + n + b , t );
	}
}

void solve()
{
	for ( int p = 1 ; p <= n ; p++ )
	{
		memset( dist , 0x3f , sizeof( dist) );
		memset( state , 0 , sizeof( state) );
		memset( pre , 0 , sizeof( pre ) );
		memset( pos , 0 , sizeof( pos ) );
		dist[ 1 ] = 0;
		head = tail = 1;
		queue[ 1 ] = 1;
		state[ 1 ] = 1;
		while( state[ queue[ head] ] == 1 )
		{
			int v = queue[ head];
			int j = g[ v ];
			while ( j > 0 )
			{
				if ( dist[ v ] + edge[ j ].c < dist[ edge[ j ].e ] )
				{
					dist[ edge[ j ].e ] = dist[ v ] + edge[ j ].c;
					pre[ edge[ j ].e ] = v;
					pos[ edge[ j ].e ] = j;
					if ( !state[ edge[ j ].e ] )
					{
						state[ edge[ j ].e ] = 1;
						tail = ( tail + 1 ) % 2000;
						queue[ tail ] = edge[ j ].e;
					}
				}
				j = edge[ j ].next;
			}
			state[ queue[ head] ] = 0;
			head = ( head + 1 ) % 2000;	
		}
		ret += dist[ N ];
		int t = N;
		while ( t != 1 )
		{
			addline( t , pre[ t ] , -edge[ pos[ t ] ].c );
			edge[ pos[ t ] ].c = 0x3f3f3f3f;
			t = pre[ t ];
		}
	}
}

void print()
{
	printf( "%d\n" , ret );
}

int main()
{
	init();
	solve();
	print();
}
