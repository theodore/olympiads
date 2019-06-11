#include <cstdio>
#include <cstring>

const int maxn(10003);
const int maxN(1010007);
const int maxm(2010017);
int n;
int start[maxN], to[maxm], next[maxm], edge;

void add(int a, int b)
{
	to[++edge] = b;
	next[edge] = start[a];
	start[a] = edge;
}

int match[maxN];
bool vis[maxn];

bool find_aug_path(const int x)
{
	vis[x] = true;
	for (int e = start[x]; e; e = next[e])
	{
		int u = to[e];
		if (!match[u])
		{
			match[u] = x;
			match[x] = u;
			return true;
		}
		else if (!vis[match[u]] && find_aug_path(match[u]))
		{
			match[u] = x;
			match[x] = u;
			return true;
		}
	}
	return false;
}

int main()
{
	int m;
	scanf("%d", &m);
	for (int i = 0, a, b; i < m; ++i)
	{
		scanf("%d%d", &a, &b);
		add(a, i + maxn);
		add(i + maxn, a);
		add(b, i + maxn);
		add(i + maxn, b);
	}
	for (int i = 1; ; ++i)
	{
		memset(vis, 0, sizeof vis);
		if (!find_aug_path(i))
		{
			printf("%d\n", i - 1);
			return 0;
		}
	}
	return 0;
}
