#include<cstdio>
#include <bits/stdc++.h>
#include<queue>
#include<algorithm>
#include<iostream>
#define rep(i,n) for(int i=0;i<n;i++)
using namespace std;
const int maxn=300+20;
struct Edge
{
    int t,c;
    Edge(int _t,int _c,Edge* _next):
        t(_t),next(_next),c(_c){}
    Edge*next,*op;
}*E[maxn]={0};
int n,vs,vt;
int h[maxn],vh[maxn],v;
void InsEdge(int s,int t,int c)
{
    //cout<<s<<" "<<t<<" "<<c<<endl;
    E[s]=new Edge(t,c,E[s]);
    E[t]=new Edge(s,0,E[t]);
    E[s]->op=E[t];E[t]->op=E[s];
}
const int All=0,Like=1,DontLike=2,inf=1<<20;
inline int Boy(int x,int type){return x*3+type;}
inline int Girl(int x,int type){return (n+x)*3+type;}
void Init()
{
    int k;char x;
    scanf("%d %d\n",&n,&k);
    v=n*6+2;vs=v-1;vt=v-2;
    rep(i,n)rep(j,n)
    {
        scanf("%c\n",&x);
        int t=x=='Y'?Like:DontLike;
        InsEdge(Boy(i,t),Girl(j,t),1);
    }
    rep(i,n)
    {
        InsEdge(vs,Boy(i,All),0);
        InsEdge(Boy(i,All),Boy(i,Like),inf);
        InsEdge(Boy(i,All),Boy(i,DontLike),k);
        InsEdge(Girl(i,All),vt,0);
        InsEdge(Girl(i,Like),Girl(i,All),inf);
        InsEdge(Girl(i,DontLike),Girl(i,All),k);
    }
}
int aug(int no,int m)
{
    if(no==vt) return m;
    int l=m;
    for(Edge*i=E[no];i;i=i->next)if(i->c&&h[no]==h[i->t]+1)
    {
        int d=aug(i->t,min(l,i->c));
        i->c-=d,i->op->c+=d,l-=d;
        if(!l||h[vs]>=v) return m-l;
    }
    int minh=v;
    for(Edge*i=E[no];i;i=i->next)if(i->c)
        minh=min(minh,h[i->t]+1);
    if(!--vh[h[no]]) h[vs]=v;
    vh[h[no]=minh]++;
    return m-l;
}
int CalFlow()
{
    memset(h,0,sizeof(h));
    memset(vh,0,sizeof(vh));
    vh[0]=v;int flow=0;
    while(h[vs]<v) flow+=aug(vs,inf);
    return flow;
}
void Work()
{
    int Flow=0;
    for(int i=1;;i++)
    {
        for(Edge*e=E[vs];e;e=e->next)e->c++;
        for(Edge*e=E[vt];e;e=e->next)e->op->c++;
        Flow+=CalFlow();
        if(Flow!=i*n)
        {
            cout<<i-1<<endl;
            break;
        }
    }
}
int main()
{
    //freopen("in","r",stdin);
    Init();
    Work();
}
