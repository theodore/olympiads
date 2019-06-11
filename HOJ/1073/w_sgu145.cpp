#include<algorithm>
#include<vector>
#include<iostream>
#include<queue>
#include<cstring>
#define pb push_back
using namespace std;
const int maxn=100,inf=~0U>>2;
int n,m,k,vs,vt;
struct Edge
{
    int t,c;
    Edge(int _t,int _c):t(_t),c(_c){}
};
vector<Edge> E[maxn];
typedef vector<Edge>::iterator eit;
void AddEdge(int s,int t,int c)
{
    E[s].pb(Edge(t,c));
    E[t].pb(Edge(s,c));
}
int Dist[maxn];
void Spfa(int vs,vector<Edge> E[maxn])
{
    bool inq[maxn]={0};queue<int> Q;
    for(int i=0;i<n;i++) Dist[i]=inf;
    Dist[vs]=0;inq[vs]=true;Q.push(vs);
    while(Q.size())
    {
        int t=Q.front();Q.pop();inq[t]=false;
        int cost=Dist[t],ncost;
        for(eit e=E[t].begin();e!=E[t].end();++e)
            if((ncost=cost+e->c)<Dist[e->t])
            { Dist[e->t]=ncost;
                if(!inq[e->t])
                    inq[e->t]=true,Q.push(e->t);
            }
    }
}
bool vis[maxn]={0};
int Limit,Num;
void dfs(int no,int gone)
{
    vis[no]=true;
    if(Num>=k)goto end;
    if(gone+Dist[no]>Limit) goto end;
    if(no==vt){Num++;goto end;}
    for(eit e=E[no].begin();e!=E[no].end();++e)if(!vis[e->t])
    {
        dfs(e->t,gone+e->c);
        if(Num>=k) goto end;
    }
    end:
    vis[no]=false;
}
int Now[maxn];
struct Route
{
    int*A;
    int n,Len;
    Route(int _n,int _Len)
    {
        n=_n;Len=_Len;
        A=new int[n];
        memcpy(A,Now,sizeof(int)*n);
    }
    bool operator<(const Route&o)const
    {
        return Len<o.Len;
    }
    void show()const
    {
        cout<<Len<<" "<<n<<endl;
        for(int i=0;i<n-1;i++)
            cout<<A[i]+1<<" ";
        cout<<A[n-1]+1<<endl;
    }
};
vector<Route> Rs;
void Sdfs(int no,int gone,int d)
{
    vis[no]=true;
    Now[d-1]=no;
    if(gone+Dist[no]>Limit) goto end;
    if(no==vt)
    {
        Rs.pb(Route(d,gone));
        goto end;
    }
    for(eit e=E[no].begin();e!=E[no].end();++e)if(!vis[e->t])
    {
        Sdfs(e->t,gone+e->c,d+1);
    }
    end:
    vis[no]=false;
}
bool Check(int _Limit)
{
    Num=0;
    Limit=_Limit;
    dfs(vs,0);
    return Num>=k;
}
void Get(int _Limit)
{
    Limit=_Limit;
    Sdfs(vs,0,1);
    sort(Rs.begin(),Rs.end());
    Rs[k-1].show();
}
void Init()
{
    cin>>n>>m>>k;
    int s,t,c;
    while(m--)
    {
        cin>>s>>t>>c;s--;t--;
        AddEdge(s,t,c);
    }
    cin>>vs>>vt;vs--;vt--;
}
void Work()
{
    Spfa(vt,E);
    int l=0,r=inf;
    if(!Check(r))
    {
        cout<<"No"<<endl;
        return;
    }
    while(l+1<r)
    {
        int m=l+r>>1;
        if(Check(m))
            r=m;
        else
            l=m;
    }
    Get(r);
}
int main()
{
    //freopen("in","r",stdin);
    Init();
    Work();
}
