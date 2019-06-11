#include <iostream>
#include <cstring>
using namespace std;
 
const int bin[10]={0,1,3,7,15,31,63,127,255,511};
long long f[2][512];
int n,m,k;
 
void dfs(int p,int ul,int ll,int ub,int lb)
{
    if (p>m)
    {
        if (!ub && !lb) f[k][ll]+=f[!k][(~ul)&bin[m]];
        return;
    }
    if (!ub && !lb)
    {
        dfs(p+1,ul<<1|1,ll<<1|1,0,0);
        //dfs(p+1,ul<<1|1,ll<<1|1,1,1);
        dfs(p+1,ul<<1|1,ll<<1|1,0,1);
        dfs(p+1,ul<<1|1,ll<<1|1,1,0);
    }
    if (!ub)
    {
        //dfs(p+1,ul<<1|1,ll<<1|lb,1,0);
        dfs(p+1,ul<<1|1,ll<<1|lb,1,1);
    }
    if (!lb)
    {
        dfs(p+1,ul<<1|ub,ll<<1|1,0,1);
        dfs(p+1,ul<<1|ub,ll<<1|1,1,1);
    }
    dfs(p+1,ul<<1|ub,ll<<1|lb,0,0);
    return;
}
 
int main()
{
    cin>>n>>m;
    if (m<n) swap(n,m);
    f[0][bin[m]]=1; k=1;
    for (int i=1;i<=n;++i,k^=1)
    {
        memset(f[k],0,sizeof(f[k]));
        dfs(1,0,0,0,0);
    }
    cout<<f[n&1][bin[m]] << endl;
    return 0;
}
