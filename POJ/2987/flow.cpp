#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>

#define OP(x) ((((x) - 1) ^ 1) + 1)

typedef long long ll;
const ll INF = 53000000007ll;
const int maxn = 5007;
const int maxm = 130017;
int n, m, s, t;
int start[maxn], to[maxm], next[maxm], edge;
ll cap[maxm];

void add(int a, int b, ll c)
{
	to[++edge] = b;
	cap[edge] = c;
	next[edge] = start[a];
	start[a] = edge;
}

ll sap()
{
	static int dist[maxn], pre[maxn], cur[maxn], cnt[maxn];
	static ll flow[maxn];
	ll ans = 0;
	cnt[0] = n;
	memcpy(cur, start, sizeof(int) * size_t(n + 1));
	for (int i = s; dist[s] < n; )
	{
#ifdef DB
		fprintf(stderr, "i = %d\n", i);
#endif
		if (i == s)
		{
			flow[i] = INF;
		}
		bool found = false;
		for (int e = cur[i]; e; e = next[e])
			if (cap[e] && dist[i] == dist[to[e]] + 1)
			{
				found = true;
				flow[to[e]] = std::min(cap[e], flow[i]);
				cur[i] = e;
				i = to[e];
				pre[i] = e;
				break;
			}
		if (i == t)
		{
#ifdef DB
			fprintf(stderr, "i == t, flow = %lld\n", flow[t]);
#endif
			for (ans += flow[t]; i != s; i = to[OP(pre[i])])
			{
				cap[pre[i]] -= flow[t];
				cap[OP(pre[i])] += flow[t];
			}
			continue;
		}
		else if (!found)
		{
			if (--cnt[dist[i]] == 0)
				break;
			dist[i] = n;
			for (int e = start[i], d; e; e = next[e])
				if (cap[e] && (d = dist[to[e]] + 1) < dist[i])
				{
					dist[i] = d;
					cur[i] = e;
				}
			++cnt[dist[i]];
			if (i != s)
				i = to[OP(pre[i])];
		}
	}
	return ans;
}

int dfs(const int x, const int fa = 0)
{
	int r = 1;
	for (int e = start[x]; e; e = next[e])
		if (cap[e] && to[e] != fa)
			r += dfs(to[e], x);
	return r;
}

int number()
{
	static std::queue<int> q;
	static bool vis[maxn];
	q.push(s);
	vis[s] = true;
	int r = 0;
	while (!q.empty())
	{
		int x = q.front();
		q.pop();
		for (int e = start[x]; e; e = next[e])
			if (cap[e] && !vis[to[e]])
			{
				++r;
				q.push(to[e]);
				vis[to[e]] = true;
			}
	}
	return r;
}

int main()
{
	scanf("%d%d", &n, &m);
	s = n + 1;
	t = n + 2;
	ll ans = 0;
	for (int i = 1, x; i <= n; ++i)
	{
		scanf("%d", &x);
		if (x > 0)
		{
			ans += x;
			add(s, i, x);
			add(i, s, 0);
		}
		else if (x < 0)
		{
			add(i, t, -x);
			add(t, i, 0);
		}
	}
	n += 2;
	for (int i = 0, a, b; i < m; ++i)
	{
		scanf("%d%d", &a, &b);
		add(a, b, INF);
		add(b, a, 0);
	}
	ans -= sap();
	std::cout << number() << ' ' << ans << std::endl;
}
