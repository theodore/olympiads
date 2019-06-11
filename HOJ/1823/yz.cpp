#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define maxm 2003
#define maxn 203
using namespace std;
int t , n , m ;
int pre[maxm] , now[maxn] , y[maxm] , tot = 0 ;
int dfn[maxn] , low[maxn] , stack[maxn] , top = 0 , belong[maxn] , step = 0;
bool instack[maxn] ;
int Cnt = 0 ;

void addedge(int u,int v)
{
    tot++ ; pre[tot] = now[u] ; now[u] = tot ; y[tot] = v ;
}
void tarjan(int u)
{
    low[u] = dfn[u] = ++ step ;
    instack[u] = true ;
    stack[++top] = u ;
    for (int mark = now[u] ; mark > 0 ; mark = pre[mark])
    {
        int v = y[mark];
        if (!dfn[v])
        {
            tarjan(v);
            if (low[u] > low[v])
                low[u] = low[v];
        }
        else
        {
            if (instack[v] && dfn[v] < low[u])
                low[u] = dfn[v] ;
        }
    }
    if (low[u] == dfn[u])
    {
        int j ;
        Cnt++ ;
        do
        {
            j = stack[top--];
            belong[j] = Cnt ;
            instack[j] = false ;
        }
        while (j != u);
    }
}
void solve()
{
    scanf("%d%d\n",&n,&m);
    tot = 0 ;
    memset(now,0,sizeof(now));
    for (int i = 1 ; i <= m ; i++)
    {
        int t1 , t2 , h1 , h2;
        char ch1 , ch2 ;
        scanf("%c%d %c%d\n",&ch1,&h1,&ch2,&h2);
        t1 = (ch1 == 'h');
        t2 = (ch2 == 'h');
        addedge((1-t1)*n+h1,t2*n+h2);
        addedge((1-t2)*n+h2,t1*n+h1);
    }
    step = 0 ;
    top = 0 ;
    Cnt = 0 ;
    memset(instack,false,sizeof(instack));
    memset(dfn,0,sizeof(dfn));
    for (int i = 1 ; i <= 2 * n ; i++)
        if (!dfn[i]) tarjan(i);
    //for (int i = 1 ; i <= 2 * n ; i++)
    //    cout << belong[i] << endl ;
    for (int i = 1 ; i <= n ; i++)
        if (belong[i] == belong[i + n])
        {
            printf("%s\n","BAD");
            return ;
        }
    printf("%s\n","GOOD");
    return ;
}
int main()
{
    scanf("%d",&t);
    while (t--) solve();
    return 0 ;
}
