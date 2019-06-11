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
#define rep(i,n) for(int i=0;i<n;i++)
#define pb push_back
#define Debug(x) cout<<#x<<"="<<x<<endl;
#define For(i,l,r) for(int i=l;i<=r;i++)
const int inf=~0U>>1,maxn=57;
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
int Mem[maxn][maxn][27],A[maxn],n;
char C[maxn+10];
int Dp(int l,int r,int ch)
{
    int&x=Mem[l][r][ch];if(x!=-1)return x;
    x=inf;
    if(l>r)return x=0;
    if(A[l]==ch)return x=Dp(l+1,r,ch);
    if(A[r]==ch)return x=Dp(l,r-1,ch);
    int t=A[l];
    for(int k=l;k<=r;k++)
        x=min(x,Dp(l,k,t)+Dp(k+1,r,ch)+1);
    return x;
}
int main()
{
    //freopen("in","r",stdin);
    gets(C);n=strlen(C);
    rep(i,n)A[i]=C[i]-'A';
    memset(Mem,-1,sizeof Mem);
    cout<<Dp(0,n-1,26)<<endl;
}
