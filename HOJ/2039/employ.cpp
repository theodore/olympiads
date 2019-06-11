#include <cstdio>
#include <iostream>
#include <algorithm>

#ifdef DB
# define output(x) \
	std::cerr << #x << ":"; \
	for (int i = 0; i <= t; ++i) std::cerr << " " << x[i]; \
	std::cerr << std::endl;
#endif

#define OP(x) ((((x) - 1) ^ 1) + 1)

typedef long long ll;

const int maxn = 1003;
const int maxm = 1004003;
const int s = 0;
int n, t;
int start[maxn], to[maxm], next[maxm], edge;
ll cap[maxm];

void getint(int& x)
{
	static int ch;
	while ((ch = getchar()) < '0' || ch > '9')
		;
	x = ch - '0';
	while ((ch = getchar()) >= '0' && ch <= '9')
		x = x * 10 + ch - '0';
}

void add(const int a, const int b, const ll c)
{
	to[++edge] = b;
	cap[edge] = c;
	next[edge] = start[a];
	start[a] = edge;
}

ll input()
{
	getint(n);
	t = n + 1;
	for (int i = 1, x; i <= n; ++i)
	{
		getint(x);
		add(i, t, x);
		add(t, i, 0);
	}
	ll rtn = 0;
	for (int i = 1; i <= n; ++i)
	{
		ll sum = 0;
		for (int j = 1, x; j <= n; ++j)
		{
			getint(x);
			sum += x;
			if (j > i)
			{
				add(i, j, 2 * ll(x));
				add(j, i, 2 * ll(x));
			}
		}
		rtn += sum;
		add(s, i, sum);
		add(i, s, 0);
	}
	return rtn;
}

const ll INF = -1ull >> 1;
ll flow[maxn];
int cur[maxn], cnt[maxn];
int dist[maxn];
int pre[maxn];

ll sap()
{
	ll rtn = 0;
	int x = s;
	n += 2;
	cnt[0] = n;
	for (int i = 0; i < t; ++i)
		cur[i] = start[i];
	flow[0] = INF;
	while (dist[s] < n)
	{
#ifdef DB
		fprintf(stderr, "x = %d\n", x);
		output(dist);
		output(flow);
#endif
		bool found = false;
		for (int e = cur[x]; e; e = next[e])
			if (cap[e] && dist[to[e]] + 1 == dist[x])
			{
				found = true;
				cur[x] = e;
				flow[to[e]] = std::min(cap[e], flow[x]);
				pre[x = to[e]] = e;
				break;
			}
		if (x == t)
		{
			for (rtn += flow[t]; x != s; x = to[OP(pre[x])])
			{
				cap[pre[x]] -= flow[t];
				cap[OP(pre[x])] += flow[t];
			}
			continue;
		}
		if (!found)
		{
			if (--cnt[dist[x]] == 0)
				break;
			dist[x] = n;
			for (int e = start[x]; e; e = next[e])
				if (cap[e] && dist[to[e]] + 1 < dist[x])
				{
					dist[x] = dist[to[e]] + 1;
					cur[x] = e;
				}
			++cnt[dist[x]];
			if (x != s)
				x = to[OP(pre[x])];
		}
	}
#ifdef DB
	fprintf(stderr, "%lld\n", rtn);
#endif
	return rtn;
}

int main()
{
	std::cout << input() - sap() << std::endl;
}
