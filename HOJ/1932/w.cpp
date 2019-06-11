#include <vector>
#include <stack>
#include <cstdio>
#include <algorithm>
#define rep(i,n) for(int i=0;i<n;i++)
#define pb push_back
#define All(x) x.begin(),x.end()
const int seed=13331;
using namespace std;
typedef unsigned long long ull;
typedef vector<ull> set;
ull Code(const set&s)
{
	ull ret=0;
	rep(i,s.size())ret*=seed,ret+=s[i]+78;
	return ret;
}
void Normal(set&s)
{
	sort(All(s));
	s.resize(unique(All(s))-s.begin());
}
stack<set> S;
int main()
{
	int n;scanf("%d",&n);char cmd[10];set a,b;
	while(n--)
	{
		scanf("%s",cmd);
		switch(cmd[0])
		{
			case 'P':S.push(set());break;
			case 'D':S.push(S.top());break;
			case 'A':a=S.top();S.pop();b=S.top();S.pop();b.pb(Code(a));
					 Normal(b);S.push(b);break;
			default:a=S.top();S.pop();b=S.top();S.pop();set c(a.size()+b.size());
					if(cmd[0]=='U')c.resize(set_union(All(a),All(b),c.begin())-c.begin());
					else c.resize(set_intersection(All(a),All(b),c.begin())-c.begin());
					Normal(c);S.push(c);break;
		}
		printf("%d\n",S.top().size());
	}
}
