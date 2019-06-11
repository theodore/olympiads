#include <iostream>
#include <cstdio>
#include <cstring>
#define MAXN 200
#define MAXM MAXN*MAXN

using namespace std;

#define BUFSIZE 100000*100
char buf[BUFSIZE+1], *pt = buf;
#define scan_int(t) \
{  \
    t = 0;  \
    while ((!((*pt) >= '0' && (*pt) <= '9')) && (*pt)!='-') pt++;  \
    while (((*pt) >= '0' && (*pt) <= '9')) t = t * 10 + (*(pt++)) - '0';  \
}



int n;
int Count = 0;
int begin[MAXN+1], end[MAXM+1], next[MAXM+1];
void AddEdge(int a,int b){
    Count++;
    next[Count] = begin[a];
    begin[a] = Count;
    end[Count] = b;
}
int Link[MAXN+1];
bool hash[MAXN+1];
bool dfs(int x){
    for (int now = begin[x]; now; now = next[now])
        if (!hash[end[now]]){
            hash[end[now]] = true;
            if (!Link[end[now]] || dfs(Link[end[now]])){
                Link[end[now]] = x;
                return true;
            }
        }
    return false;
}
void Solve(){
    Count = 0;
    memset(begin,0,sizeof(begin));
    //scanf("%d",&n);
    scan_int(n);
    int t;
    for (int i = 1; i<=n; i++)
        for (int j = 1; j<=n; j++){
            //scanf("%d",&t);
            scan_int(t);
            if (t) AddEdge(i,j);
        }
    memset(Link,0,sizeof(Link));
    for (int i = 1; i<=n; i++){
        memset(hash,0,sizeof(hash));
        if (!dfs(i)){
            printf("No\n");
            return;
        }
    }
    printf("Yes\n");
}
int main(){
    int t;
    scanf("%d",&t);
    fread(buf, 1, BUFSIZE, stdin);
    while (t--)
        Solve();
    return 0;
}
