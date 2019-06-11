#include <vector>
#include <algorithm>
#include <utility>
#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <cstring>
#define rep(i,n) for(int i=0;i<n;i++)
#define pb push_back
const int inf=~0U>>1,maxn=10,maxd=15;
using namespace std;
typedef long long ll;
ll A[maxn],C[maxn],Pow[maxd],Pre[maxn];
int N[maxd],n;
void Dfs(int p)
{
	int t=N[p];
	if(p<0)
	{
		rep(j,10)C[j]+=Pre[j];
		return;
	}
	rep(i,t)
	{
		ll num=Pow[p];
		if(p==n-1&&i==0)
		{
			rep(j,10)C[j]+=num/10*p;
			rep(j,p+1)
			{
				C[0]-=(Pow[p-j]-Pow[p-j]/10)*j;
			}
		}
		else
		{
			Pre[i]++;
			rep(j,10)C[j]+=Pre[j]*num;
			Pre[i]--;num/=10;
			rep(j,10)C[j]+=p*num;
		}
	}
	Pre[t]++;Dfs(p-1);
}
void Cal(ll x)
{
	for(n=0;x;x/=10,n++)N[n]=x%10;
	memset(C,0,sizeof(C));
	memset(Pre,0,sizeof(Pre));
	Dfs(n-1);
}
int main()
{
	//freopen("in","r",stdin);
	//freopen("out","w",stdout);
	ll a,b;cin>>a>>b;Pow[0]=1;rep(i,maxd-1)Pow[i+1]=Pow[i]*10;
	Cal(b);rep(i,10)A[i]=C[i];
	Cal(a-1);rep(i,10)A[i]-=C[i];
	rep(i,10)cout<<A[i]<<" ";
	cout << endl;
}
