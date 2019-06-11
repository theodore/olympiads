#include <cstdio>
#include <cstring>
#include <algorithm>

const int maxn = 100000;
const int maxm = 200000;
int n, m;
bool black[maxn];
int start[maxn], to[maxm], next[maxm], leng[maxm], edge;
int f[maxn];

void dfs(const int x, const int fa, const int dist, const int cnt)
{
	for (int e = start[x]; e; e = next[e])
		if (to[e] != fa)
		{
			int t = cnt + black[to[e]];
			f[t] = std::max(f[t], dist + leng[e]);
			dfs(to[e], x, dist + leng[e], t);
		}
}

int answer(const int x)
{
	memset(f, 0, sizeof f);
	dfs(x, 0, 0, black[x]);
	for (int i = 1; i <= m; ++i)
		f[i] = std::max(f[i - 1], f[i]);
	return f[m];
}

void add(const int a, const int b, const int c)
{
	to[++edge] = b;
	leng[edge] = c;
	next[edge] = start[a];
	start[a] = edge;
}

int main()
{
	int _;
	scanf("%d%d%d", &n, &m, &_);
	for (int x; _--; )
	{
		scanf("%d", &x);
		black[x] = true;
	}
	for (int i = 1, a, b, c; i < n; ++i)
	{
		scanf("%d%d%d", &a, &b, &c);
		add(a, b, c);
		add(b, a, c);
	}
	int ans = 0;
	for (int i = 1; i <= n; ++i)
		ans = std::max(ans, answer(i));
	printf("%d\n", ans);
}
