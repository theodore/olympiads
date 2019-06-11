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

void mix_push(const vll& a, const vll& b)
{
	vll c;
	size_t n = a.size(), m = b.size(), i, j;
	for (i = j = 0; i < n && j < m; ++j)
	{
		while (i < n && a[i] < b[j])
			c.push_back(a[i++]);
		c.push_back(b[j]);
		i += a[i] == b[j];
	}
	while (i < n)
		c.push_back(a[i++]);
	while (j < m)
		c.push_back(b[j++]);
	s.push(c);
}

void mix()
{
	const vll a = s.top(); s.pop();
	const vll b = s.top(); s.pop();
	vll c(a.size() + b.size());
	mix_push(a, b);
}

void add()
{
	vll a;
	a.push_back(hash(s.top()));
	s.pop();
	const vll b = s.top(); s.pop();
	mix_push(a, b);
}

void intersect()
{
	const vll a = s.top(); s.pop();
	const vll b = s.top(); s.pop();
	vll c;
	size_t n = a.size(), m = b.size();
	for (size_t i = 0, j = 0; i < n && j < m; ++j)
	{
		while (i < n && a[i] < b[j])
			++i;
		if (a[i] == b[j])
			c.push_back(a[i++]);
	}
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
