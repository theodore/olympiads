#include <iostream>
#include <cstdio>
#define MAXN 1100
using namespace std;
long long F[MAXN] ; int c[MAXN] ,N ;
bool move = false ;
long long a1 = 0 , a2 = 0 ;
const long long INFINITE = 1000000000000010LL;
int main()
{
    scanf("%d",&N);
    for (int i=1 ; i<=N ; i++)
    {
        scanf("%d",&c[i]);
        if (i>2 && c[i]==c[i-1] && c[i]==1)
            move = true ;
    }
    if (!move)
    {
        for (int i=1 ; i<=N ; i++)
            if (!(i&1))
            {
                if (c[i]==1) a2++ ;
                else a1++ ;
            }
        cout << a1 << endl  << a2 << endl ;
        return 0 ;
    }

    for (int i=1 ; i<=N ; i++) if (c[i]) F[i] = 1 ; else F[i] = INFINITE ;
    for (int i=1 ; i<=N ; i++)
        if (i > 2 && c[i] == c[i-1] && c[i]==1)
        {
            for (int j = i-2 ; j >= 1 ; j--)
                if (F[j] > F[j+1] + F[j+2]) F[j] = F[j+1] + F[j+2] ;
            for (int j = i+1 ; j <= N ; j++)
                if (F[j] > F[j-1] + F[j-2]) F[j] = F[j-1] + F[j-2] ;
        }
    for (int i=1 ; i<=N ; i++)
        if (!(i&1)) a2 += F[i];
    cout << 0 << endl << a2 << endl ;
    return 0 ;
}
