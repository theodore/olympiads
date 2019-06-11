#include <cstdio>
#include <cstring>
#include <algorithm>

#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))

const int maxn = 200003;
const int maxm = 400003;
int n, m;
bool black[maxn];
bool vis[maxn];
int size[maxn], tree_size;
int start[maxn], to[maxm], next[maxm], leng[maxm], edge;

#ifdef DB
//int get_size_cnt;
#endif

int get_size(const int x, const int fa)
{
#ifdef DB
	//++get_size_cnt;
#endif
	size[x] = 1;
	for (int e = start[x]; e; e = next[e])
		if (!vis[to[e]] && to[e] != fa)
			size[x] += get_size(to[e], x);
	return size[x];
}

void change_root(const int x, const int fa, int& root, int& val)
{
	int now = tree_size - size[x];
	for (int e = start[x]; e; e = next[e])
		if (!vis[to[e]] && to[e] != fa)
		{
			change_root(to[e], x, root, val);
			now = max(now, size[to[e]]);
		}
	if (now < val)
	{
		val = now;
		root = x;
	}
}

void change_root(int& x)
{
	tree_size = get_size(x, 0);
	int t = tree_size;
	change_root(x, 0, x, t);
}

void calc(const int x, const int fa, const int dist, const int cnt, int f[])
{
	for (int e = start[x]; e; e = next[e])
		if (!vis[to[e]] && to[e] != fa)
		{
			int t = cnt + black[to[e]];
			f[t] = max(f[t], dist + leng[e]);
			calc(to[e], x, dist + leng[e], t, f);
		}
}

struct son_t
{
	int id, size, leng;
	bool operator<(const son_t& x) const
	{
		return size < x.size;
	}
};

son_t son[maxn];
int f[maxn], g[maxn];

#ifdef DB
void tab(const int x)
{
	for (int i = 0; i < x; ++i)
		fprintf(stderr, "  ");
}

int dfs(int x, const int d = 0)
#else
int dfs(int x)
#endif
{
	change_root(x);
#ifdef DB
	//fprintf(stderr, "\n");
	//tab(d);
	//fprintf(stderr, "root = %d\n", x);
#endif
	vis[x] = true;
	int rtn = 0, cnt = 0;
	for (int e = start[x]; e; e = next[e])
		if (!vis[to[e]])
		{
			son[cnt].id = to[e];
			son[cnt].leng = leng[e];
			int& t = son[cnt++].size = size[to[e]];
			if (t > size[x])
				t = tree_size - size[x];
			//son[cnt++].size = get_size(to[e], 0);
		}
	std::sort(son, son + cnt);
#ifdef DB
	for (int i = 0; i < cnt; ++i)
		fprintf(stderr, "%d ", son[i].size);
	fprintf(stderr, "\n");
#endif
	memset(f, 0, sizeof f);
	for (int i = 0; i < cnt; ++i)
	{
		memset(g, 0, sizeof g);
		g[black[son[i].id]] = son[i].leng;
		calc(son[i].id, 0, son[i].leng, black[son[i].id], g);
		for (int j = 1; j <= son[i].size; ++j)
			g[j] = max(g[j], g[j - 1]);
		int abcdefg = min(son[i].size, m - black[x]);
		for (int j = 0; j <= abcdefg; ++j)
			rtn = max(rtn, g[j] + f[m - black[x] - j]);
		f[0] = max(f[0], g[0]);
		for (int j = 1; j <= son[i].size; ++j)
		{
			f[j] = max(f[j - 1], f[j]);
			f[j] = max(f[j], g[j]);
		}
#ifdef DB
		if (0)
		{
			fprintf(stderr, "%d:\n", son[i].id);
			for (int j = 0; j <= son[i].size; ++j)
				fprintf(stderr, " %d", g[j]);
			fprintf(stderr, "\n");
			for (int j = 0; j <= son[i].size; ++j)
				fprintf(stderr, " %d", f[j]);
			fprintf(stderr, "\n");
		}
		//tab(d);
		//fprintf(stderr, "rtn = %d\n", rtn);
#endif
	}
	for (int e = start[x], t; e; e = next[e])
		if (!vis[to[e]])
			if ((t = dfs(to[e])) > rtn)
				rtn = t;
#if 0
#ifndef DB
			rtn = max(rtn, dfs(to[e]));
#else
			rtn = max(rtn, dfs(to[e], d + 1));
#endif
#endif
	return rtn;
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
	for (int t; _--; )
	{
		scanf("%d", &t);
		black[t] = true;
	}
	for (int i = 1, a, b, c; i < n; ++i)
	{
		scanf("%d%d%d", &a, &b, &c);
		add(a, b, c);
		add(b, a, c);
	}
	printf("%d\n", dfs(1));
#ifdef DB
	//fprintf(stderr, "get size cnt: %d\n", get_size_cnt);
#endif
}
