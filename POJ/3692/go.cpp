#include <cstdio>
#include <cstring>

const int maxn = 403;
const int maxm = 40003;
int n, m;
int start[maxn], to[maxm], next[maxm];
int& edge = start[0];

void add(const int a, const int b)
{
#ifdef DB
	fprintf(stderr, "add %d %d\n", a, b);
#endif
	to[++edge] = b;
	next[edge] = start[a];
	start[a] = edge;
}

bool vis[maxn];
int match[maxn];

bool find_aug(const int x)
{
	if (x == 0)
		return true;
	for (int e = start[x], t; e; e = next[e])
		if (!vis[t = to[e]])
		{
			vis[t] = true;
			if (find_aug(match[to[e]]))
			{
				match[to[e]] = x;
				return true;
			}
		}
	return false;
}

int hungarian()
{
	memset(match, 0, sizeof match);
	int ret = 0;
	for (int i = 1; i <= n; ++i)
	{
		memset(vis, 0, sizeof vis);
		ret += find_aug(i);
#ifdef DB
		fprintf(stderr, "ret = %d, i = %d\n", ret, i);
#endif
	}
	return ret;
}

int main()
{
	for (int _ = 1, k; ; ++_)
	{
		scanf("%d%d%d", &n, &m, &k);
		if (!(n | m | k))
			break;
		static bool map[maxn][maxn];
		memset(map, 0, sizeof map);
		for (int i = 0, a, b; i < k; ++i)
		{
			scanf("%d%d", &a, &b);
			map[a][b + n] = true;
		}
		memset(start, 0, sizeof start);
		for (int i = 1; i <= n; ++i)
			for (int j = n + 1; j <= n + m; ++j)
				if (!map[i][j])
				{
					add(i, j);
					add(j, i);
				}
		printf("Case %d: %d\n", _, n + m - hungarian());
	}
}
