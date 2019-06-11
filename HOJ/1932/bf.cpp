#include <cstdio>
#include <string>
#include <stack>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

typedef vector<string> vs;
stack<vs> s;

/*
void mix_push(const vs& a, const vs& b)
{
	vs c;
	size_t i, j;
	for (i = j = 0; i < a.size() && j < b.size(); )
	{
		if (a[i] == b[j])
			++i;
		c.push_back(a[i] < b[j] ? a[i++] : b[j++]);
	}
	while (i < a.size())
		c.push_back(a[i++]);
	while (j < b.size())
		c.push_back(b[j++]);
	s.push(c);
}
*/

void mix_push(const vs& a, const vs& b)
{
	vs c = b;
	for (size_t i = 0; i < a.size(); ++i)
	{
		for (size_t j = 0; j < b.size(); ++j)
			if (a[i] == b[j])
				goto next;
		c.push_back(a[i]);
next:;
	}
	sort(c.begin(), c.end());
	s.push(c);
}

void mix()
{
	const vs a = s.top(); s.pop();
	const vs b = s.top(); s.pop();
	mix_push(a, b);
}

void add()
{
	const vs& v = s.top();
	string t = "{";
	for (size_t i = 0; i < s.top().size(); ++i)
		t += v[i];
	t += "}";
	s.pop();
	vs a;
	a.push_back(t);
	const vs b = s.top(); s.pop();
	mix_push(a, b);
}

/*
void intersect()
{
	const vs a = s.top(); s.pop();
	const vs b = s.top(); s.pop();
	vs c;
	const size_t n = a.size(), m = b.size();
	for (size_t i = 0, j = 0; i < n && j < m; ++j)
	{
		while (i < n && a[i] < b[j])
			++i;
		if (i < n && a[i] == b[j])
		{
			c.push_back(a[i]);
			++i;
		}
	}
	s.push(c);
}
*/

void intersect()
{
	const vs a = s.top(); s.pop();
	const vs b = s.top(); s.pop();
	vs c;
	for (size_t i = 0; i < a.size(); ++i)
		for (size_t j = 0; j < b.size(); ++j)
			if (a[i] == b[j])
			{
				c.push_back(a[i]);
				break;
			}
	sort(c.begin(), c.end());
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
			case 'P': s.push(vs()); break;
			case 'D': s.push(s.top()); break;
			case 'U': mix(); break;
			case 'I': intersect(); break;
			case 'A': add(); break;
		}
		printf("%d\n", s.top().size());
#ifdef DB
		if (s.top().size())
			cerr << s.top()[0] << endl;
		//const vll a = s.top();
		//for (size_t i = 0; i < a.size(); ++i)
		//fprintf(stderr, "%lld ", a[i]);
		//fprintf(stderr, "\n");
#endif
	}
}
