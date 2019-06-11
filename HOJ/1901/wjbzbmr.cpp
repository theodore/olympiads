#include <vector>
#include <algorithm>
#include <utility>
#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#define rep(i,n) for(int i=0;i<n;i++)
#define For(i,l,r) for(int i=l;i<=r;i++)
#define pb push_back
const int inf=~0U>>1,maxn=10000,size=100;
int T[size][size],N[size]={},A[maxn],n,m,t,d=1<<6;
using namespace std;
void init()
{
    scanf("%d%d",&n,&m);rep(i,n)scanf("%d",A+i),T[i/size][N[i/size]++]=A[i];
    t=1+(n-1)/size;rep(i,t)sort(T[i],T[i]+N[i]);
}
int get(int*A,int s,int x)
{
    int i,l;
    for(i=s,l=d;l;l>>=1)
        if(i-l>=0&&A[i-l]>=x)i-=l;
    return i;
}
int Count(int l,int r,int x)
{
    int a=l/size,b=r/size,s=0;;
    if(a==b){For(i,l,r)s+=A[i]<x;return s;}
    For(i,l,(a+1)*size-1)s+=A[i]<x;
    For(i,b*size,r)s+=A[i]<x;a++;b--;
    For(i,a,b)s+=get(T[i],N[i],x);
    return s;
}
int kth(int l,int r,int k)
{
    #define C(x) (Count(l,r,x))
    int i,d;
    for(i=0,d=1<<30;d;d>>=1)
        if(C(i+d)<k)i+=d;
    return i;
}
void Change(int p,int x)
{
    int a=p/size;int t=A[p];A[p]=x;
    t=lower_bound(T[a],T[a]+N[a],t)-T[a];
    T[a][t]=x;sort(T[a],T[a]+N[a]);
}
int main()
{
    //freopen("in","r",stdin);
    init();char c;int i,j,k;
    while(m--)
    {
        scanf("\n%c",&c);
        if(c=='C')scanf("%d%d",&i,&j),Change(i-1,j);
        else scanf("%d%d%d",&i,&j,&k),printf("%d\n",kth(i-1,j-1,k));
    }
}
