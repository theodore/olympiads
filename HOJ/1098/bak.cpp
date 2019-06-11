#include <vector>
#include <algorithm>
#include <utility>
#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <set>
#include <map>
#include <cstring>
#include <time.h>
#define rep(i,n) for(int i=0;i<n;i++)
#define pb push_back
#define Debug(x) cout<<#x<<"="<<x<<endl;
#define For(i,l,r) for(int i=l;i<=r;i++)
#define tr(e,x) for(typeof(x.begin()) e=x.begin();e!=x.end();e++)
#define printTime cout<<"Time:"<<clock()-pre<<endl;pre=clock();
const int inf=~0U>>1,maxn=100000,maxm=2000000*2;
using namespace std;
int n,m;
int head[maxn],out[maxn]={},nxt[maxm],t[maxm],mnt=0;
void AddEdge(int s,int _t)
{
    t[mnt]=_t;nxt[mnt]=head[s];head[s]=mnt++;
    out[s]++;
}
void InsEdge(int s,int t)
{
    AddEdge(s,t);
    AddEdge(t,s);
}
void scan(int&t)
{
    static char c;
    while(c=getchar(),c<'0'||c>'9');t=c-'0';
    while(c=getchar(),c>='0'&&c<='9')t=t*10+c-'0';
}
void Init()
{
    memset(head,-1,sizeof head);
    scan(n);scan(m);int s,t;
    rep(i,m)
    {
        scan(s);scan(t);
        InsEdge(s-1,t-1);
    }
}
bool Merge[maxn];
const int maxv=3000;
int Size[maxv],v,Vet[maxv];
bool E[maxv][maxv];
int Ind[maxn];
void BuildGraph()
{
    int Mi=0;
    rep(i,n)
    {
        Merge[i]=true;
        if(out[i]<out[Mi])
            Mi=i;
    }
    for(int e=head[Mi];e!=-1;e=nxt[e])
        Merge[t[e]]=false;
    v=1;
    rep(i,n)
        if(Merge[i])
        {
            Size[0]++;
            Ind[i]=0;
        }
        else
        {
            Ind[i]=v;
            Size[v]=1;
            Vet[v]=i;
            v++;
        }
    rep(i,v)rep(j,v)E[i][j]=true;
    //get E for 1..v-1
    for(int i=1;i<v;i++)
    {
        int x=Vet[i],cnt=0;
        for(int e=head[x];e!=-1;e=nxt[e])
            if(!Merge[t[e]])
            {
                E[i][Ind[t[e]]]=false;
            }
            else
            {
                cnt++;
            }
        if(cnt==Size[0])
        {
            E[0][i]=E[i][0]=false;
        }
    }
}
int nSize;
bool Vis[maxv]={};
void Dfs(int x)
{
    Vis[x]=true;
    nSize+=Size[x];
    rep(i,v)if(E[x][i]&&!Vis[i])
        Dfs(i);
}
int Ans[maxv],cnt=0;
void Solve()
{
    rep(i,v)if(!Vis[i])
    {
        nSize=0;
        Dfs(i);
        Ans[cnt++]=nSize;
    }
    sort(Ans,Ans+cnt);
    printf("%d\n",cnt);
    rep(i,cnt)
    {
        printf("%d ",Ans[i]);
    }
}
int main()
{
    //freopen("in","r",stdin);
    Init();
    BuildGraph();
    Solve();
}
