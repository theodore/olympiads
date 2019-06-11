#include <cstdio>
#include <cstring>
#include <algorithm>

const int MaxN = 10003;
const int MaxE = 20003;
int n, m;
int start[MaxN], to[MaxE], next[MaxE], leng[MaxE], edge;

void add(const int a, const int b, const int c)
{
	to[++edge] = b;
	leng[edge] = c;
	next[edge] = start[a];
	start[a] = edge;
}

void input()
{
	edge = 0;
	memset(start, 0, sizeof start);
	for (int i = 1, a, b, c; i < n; ++i)
	{
		scanf("%d%d%d", &a, &b, &c);
		add(a, b, c);
		add(b, a, c);
	}
}

bool vis[MaxN];
int size[MaxN];
int tree_size;

int get_size(const int x, const int fa)
{
	size[x] = 1;
	for (int e = start[x]; e; e = next[e])
		if (to[e] != fa && !vis[to[e]])
			size[x] += get_size(to[e], x);
	return size[x];
}

void change_root(const int x, const int fa, int& rtn, int& val)
{
	int here = tree_size - size[x];
	for (int e = start[x]; e; e = next[e])
		if (to[e] != fa && !vis[to[e]])
			here = std::max(here, size[to[e]]);
	if (here < val)
	{
		val = here;
		rtn = x;
	}
	for (int e = start[x]; e; e = next[e])
		if (to[e] != fa && !vis[to[e]])
			change_root(to[e], x, rtn, val);
}

void get_root(int& x)
{
	tree_size = get_size(x, 0);
	int t = tree_size;
	change_root(x, 0, x, t);
}

int list[MaxN], lc;

void dfs_list(const int x, const int fa)
{
	const int& now = list[lc - 1];
	for (int e = start[x]; e; e = next[e])
		if (to[e] != fa && !vis[to[e]])
		{
			list[lc++] = now + leng[e];
			dfs_list(to[e], x);
		}
}

void get_list(int x)
{
	lc = 1;
	list[0] = 0;
	dfs_list(x, 0);
	std::sort(list, list + lc);
}

#ifdef DB
void tab(int x)
{
	for (int i = 0; i < 2 * x; ++i)
		fprintf(stderr, " ");
}

int dfs(int x, int d = 0)
#else
int dfs(int x)
#endif
{
	int rtn = 0;
	get_root(x);
#ifdef DB
	tab(d);
	fprintf(stderr, "root = %d\n", x);
#endif
	vis[x] = true;
	get_list(x);
	for (int i = 0, j = lc - 1; i < j; ++i)
	{
		while (i < j && list[i] + list[j] > m)
			--j;
		rtn += j - i;
	}
	for (int e = start[x]; e; e = next[e])
		if (!vis[to[e]])
		{
			get_list(to[e]);
			for (int i = 0, j = lc - 1; i < j; ++i)
			{
				while (i < j && list[i] + list[j] > m - 2 * leng[e])
					--j;
				rtn -= j - i;
			}
		}
	for (int e = start[x]; e; e = next[e])
		if (!vis[to[e]])
#ifdef DB
			rtn += dfs(to[e], d + 1);
#else
			rtn += dfs(to[e]);
#endif
	vis[x] = false;
#ifdef DB
	tab(d);
	fprintf(stderr, "%d, rtn %d\n", x, rtn);
#endif
	return rtn;
}

int main()
{
	while (scanf("%d%d", &n, &m), n | m)
	{
		input();
		printf("%d\n", dfs(1));
	}
}
