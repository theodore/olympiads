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
#define printTime cout<<"Time:"<<pre-clock()<<endl;pre=clock();
const int inf=~0U>>1;
using namespace std;
typedef long long ll;
int Moves[6][2],n;

bool init()
{
    if (!(cin>>n))
	return false;
    memset(Moves, 0, sizeof Moves);
    char a;
    rep(i,6)
    {
        scanf(" ");
        rep(j,2)cin>>a,Moves[i][j]=a-'A';
    }
    return true;
}

int Stupid_Cal(int n)
{
    vector<int> Stack[3];
    for(int i=n;i>=1;i--)Stack[0].pb(i);
    int last=0;
    for(int num=0;;)
    {
        if(Stack[1].size()==n||Stack[2].size()==n)
            return num;
        rep(i,6)
        {
            int from=Moves[i][0],to=Moves[i][1];
                if(Stack[from].size()&&Stack[from].back()!=last)
                    if(Stack[to].size()==0||Stack[from].back()<Stack[to].back())
                    {
                        last=Stack[from].back();
                        Stack[from].pop_back();
                        Stack[to].pb(last);
                        num++;
                        break;
                    }
        }
    }
}

void Solve()
{
    if(n<=3){cout<<Stupid_Cal(n)<<endl;return;}
    int a2=Stupid_Cal(2),a3=Stupid_Cal(3);
    int a=a3/a2,b=a3-a*a2;
    ll ans=a3;
    for(int i=4;i<=n;i++)
        ans=ans*a+b;
    cout<<ans<<endl;
}

int main()
{
    while (init())
	Solve();
}
