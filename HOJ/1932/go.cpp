#include <cstdio>
#include <stack>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;
typedef vector<ll> vll;
stack<vll> s;

ll hash(const vll& a)
{
	static const ll seed = 155621537;
	ll r = 23153;
	for (vll::const_iterator i = a.begin(); i != a.end(); ++i)
	{
		r *= seed;
		r += *i;
		continue;
	}
	return r;
}

void mix()
{
	const vll a = s.top(); s.pop();
	const vll b = s.top(); s.pop();
	vll c(a.size() + b.size());
	c.resize(set_union(a.begin(), a.end(), b.begin(), b.end(), c.begin()) - c.begin());
	s.push(c);
}

void add()
{
	vll a;
	a.push_back(hash(s.top()));
	s.pop();
	const vll b = s.top(); s.pop();
	vll c(a.size() + b.size());
	c.resize(set_union(a.begin(), a.end(), b.begin(), b.end(), c.begin()) - c.begin());
	s.push(c);
}

void intersect()
{
	const vll a = s.top(); s.pop();
	const vll b = s.top(); s.pop();
	vll c(max(a.size(), b.size()));
	c.resize(set_intersection(a.begin(), a.end(), b.begin(), b.end(), c.begin()) - c.begin());
	s.push(c);
}

int main()
{
	int n;
	for (scanf("%d", &n); n--; )
	{
		char st[13];
		scanf("%s", st);
		switch (st[0])
		{
			case 'P': s.push(vll()); break;
			case 'D': s.push(s.top()); break;
			case 'U': mix(); break;
			case 'I': intersect(); break;
			case 'A': add(); break;
		}
		printf("%d\n", s.top().size());
	}
}
