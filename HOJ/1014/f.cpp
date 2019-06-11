#include <cstdio>
#include <cstring>
#include <cstdlib>
#undef NULL
#define NULL Node::NIL
#define MAXN 100100
 
char St[ MAXN ];
unsigned int Ph[ MAXN ];
 
namespace spa
{
 
    struct Node
    {
        unsigned int Num , Hash;
        int Size;
        Node *Son[ 2 ] , *Par;
        static Node *NIL;
        Node() { Son[ 0 ] = Son[ 1 ] = Par = NULL; }
    } *Root , Tree[ MAXN ] , *Tptr = Tree;
    Node NIL_INS;
    Node *NULL = &NIL_INS;
 
    void UpDate( Node *pos )
    {
        Node *L = pos -> Son[ 0 ] , *R = pos -> Son[ 1 ];
        pos -> Size = L -> Size + R -> Size + 1;
        unsigned int t = L -> Hash;
        t = t * 257 + pos -> Num;
        t *= Ph[ R -> Size ];
        t += R -> Hash;
        pos -> Hash = t;
    }
 
    void Rot( Node *pos , bool t )
    {
        Node *tptr = pos -> Son[ t ] , *tmp;
        tmp = pos -> Son[ t ] = tptr -> Son[ !t ];
        if ( tmp != NULL ) tmp -> Par = pos;
        tptr -> Son[ !t ] = pos;
        tptr -> Par = tmp = pos -> Par;
        pos -> Par = tptr;
        if ( tmp != NULL ) tmp -> Son[ tmp -> Son[ 1 ] == pos ] = tptr;
        else Root = tptr;
        UpDate( pos );
        UpDate( tptr );
    }
 
    void Splay( Node *pos , Node * &des )
    {
        Node *par , *gra;
        bool t1 , t2;
        while ( ( pos != des) && ( ( par = pos -> Par) != des ) )
        {
            gra = par -> Par;
            if ( ( t1 = ( par -> Son[ 1 ] == pos ) ) ==
                 ( t2 = ( gra -> Son[ 1 ] == par ) ) )
            { Rot( gra , t2 ); Rot( par , t1 ); }
            else
            { Rot( par , t1 ); Rot( gra , t2 ); }
        }
        if ( pos != des ) Rot( des , des -> Son[ 1 ] == pos );
    }
 
    Node *FindKth( int k , Node *pos = Root )
    {
        int l;
        bool f;
        while ( ( l = pos -> Son[ 0 ] -> Size + 1 ) != k )
        {
            f = l < k;
            pos = pos -> Son[ f ];
            if ( f ) k -= l;
        }
        return pos;
    }
 
    Node *MkTree( int l , int r )
    {
        Node *pos = Tptr ++;
        int m = ( l + r ) / 2;
        if ( m != 0 )
            pos -> Num = St[ m - 1 ] - 'a';
        else
            pos -> Num = 0;
        if ( l < m )
            ( pos -> Son[ 0 ] = MkTree( l , m - 1 ) ) -> Par = pos;
        if ( r > m )
            ( pos -> Son[ 1 ] = MkTree( m + 1 , r ) ) -> Par = pos;
        UpDate( pos );
        return pos;
    }
 
    void Opt()
    {
        char e;
         
        scanf( "%c" , &e);
        if ( e == 'Q' )
        {
            int x , y , tot = Root -> Size - 2;
            scanf( "%d%d\n" , &x , &y );
            if ( y < x )
            {
                int t = x;
                x = y;
                y = t;
            }
            int l = 0 , r = tot - y;
            unsigned int a , b;
            Splay( FindKth( x + 1 ) , Root );
            a = Root -> Num;
            Splay( FindKth( y + 1 ) , Root );
            b = Root -> Num;
            if ( a != b )
            {
                printf( "0\n" );
                return;
            }
            Splay( FindKth( x ) , Root );
            Splay( FindKth( tot + 2 - y + x ) , Root -> Son[ 1 ] );
            a = Root -> Son[ 1 ] -> Son[ 0 ] -> Hash;
            Splay( FindKth( y ) , Root );
            Splay( FindKth( tot + 2 ) , Root -> Son[ 1 ] );
            b = Root -> Son[ 1 ] -> Son[ 0 ] -> Hash;
            if ( a == b )
            {
                printf( "%d\n" , tot - y + 1 );
                return;
            }
            while ( l < r - 1 )
            {
                int t = ( l + r ) / 2;
                Splay( FindKth( x ) , Root );
                Splay( FindKth( x + 2 + t ) , Root -> Son[ 1 ] );
                a = Root -> Son[ 1 ] -> Son[ 0 ] -> Hash;
                Splay( FindKth( y ) , Root );
                Splay( FindKth( y + 2 + t ) , Root -> Son[ 1 ] );
                b = Root -> Son[ 1 ] -> Son[ 0 ] -> Hash;
                if ( a == b ) l = t;
                else r = t;
            }
            printf( "%d\n" , r );
        }
        if ( e == 'R' )
        {
            int x;
            char y;
            scanf( "%d %c\n" , &x , &y );
            Splay( FindKth( x + 1 ) , Root );
            Root -> Num = y - 'a';
            UpDate( Root );
        }
        if ( e == 'I' )
        {
            int x;
            char y;
            scanf( "%d %c\n" , &x , &y );
            Splay( FindKth( x + 1 ) , Root );
            Splay( FindKth( x + 2 ) , Root -> Son[ 1 ] );
            Node *pos = Root -> Son[ 1 ] , *tptr = Tptr ++;
            tptr -> Num = y - 'a';
            ( pos -> Son[ 0 ] = tptr ) -> Par = pos;
            UpDate( tptr );
            UpDate( pos );
            UpDate( Root );
            Splay( tptr , Root );
        }
    }
}
 
int main()
{
    //freopen( "1014.in" , "r" , stdin );
    //freopen( "1014.out" , "w" , stdout );
    scanf("%s", St);
    Ph[ 0 ] = 1;
    for ( int i = 1 ; i < MAXN ; i ++ )
        Ph[ i ] = Ph[ i - 1 ] * 257;
    spa::NULL -> Size = 0;
    spa::NULL -> Num = 0;
    spa::NULL -> Hash = 0;
    int l = strlen( St );
    St[ l ] = 'a';
    spa::Root = spa::MkTree( 0 , l + 1 );
    int M;
    scanf( "%d\n" , &M );
    for ( int i = 1 ; i <= M ; i ++ )
        spa::Opt();
}
