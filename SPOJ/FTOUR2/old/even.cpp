#include <cstdio>
#include <cstring>
#include <algorithm>

const int maxn = 200003;
const int maxm = 400003;
int n, m;
bool black[maxn];
bool vis[maxn];
int size[maxn], tree_size;
int start[maxn], to[maxm], next[maxm], leng[maxm], edge;

int get_size(const int x, const int fa)
{
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
			now = std::max(now, size[to[e]]);
		}
	if (now < val)
	{
		val = now;
		root = x;
	}
}

void calc(const int x, const int fa, const int dist, const int cnt, int f[], int& max_depth)
{
	if (dist > max_depth)
		max_depth = dist;
	for (int e = start[x]; e; e = next[e])
		if (!vis[to[e]] && to[e] != fa)
		{
			int t = cnt + black[to[e]];
			f[t] = std::max(f[t], dist + leng[e]);
			calc(to[e], x, dist + leng[e], t, f, max_depth);
		}
}

struct son_t
{
	int id, size, leng, depth;
	bool operator<(const son_t& x) const
	{
		return size < x.size;
	}
};

son_t son[maxn];
int f[maxn], g[maxn];

int dfs(int x)
{
	{
		int t = tree_size = get_size(x, 0);
		change_root(x, 0, x, t);
	}
	vis[x] = true;
	int rtn = 0, cnt = 0;

	for (int* e = &start[x]; *e; )
		if (vis[to[*e]])
			*e = next[*e];
		else
		{
			son[cnt].id = to[*e];
			son[cnt].leng = leng[*e];
			int& t = son[cnt++].size = size[to[*e]];
			if (t > size[x])
				t = tree_size - size[x];
			e = &next[*e];
		}

	std::sort(son, son + cnt);
	memset(f, 0, sizeof (int) * (std::max(m, son[x].size) + 1));
	int ss = 0;
	for (int i = 0; i < cnt; ++i)
	{
		memset(g, 0, sizeof (int) * (son[i].size + 1));
		g[black[son[i].id]] = son[i].leng;
		calc(son[i].id, 0, son[i].leng, black[son[i].id], g, son[i].depth);
		for (int j = 1; j <= son[i].size; ++j)
			g[j] = std::max(g[j], g[j - 1]);
		for (int j = 0; j <= std::min(son[i].size, m - black[x]); ++j)
		{
			int h = m - black[x] - j;
			if (h > ss)
				h = ss;
			rtn = std::max(rtn, g[j] + f[h]);
		}
		f[0] = std::max(f[0], g[0]);
		for (int j = 1; j <= son[i].size; ++j)
			f[j] = std::max(std::max(f[j - 1], f[j]), g[j]);
		ss = son[i].size;
	}
	for (int i = 0, t; i < cnt; ++i)
		if (2 * son[i].depth > rtn && (t = dfs(son[i].id)) > rtn)
			rtn = t;
	return rtn;
}

void add(const int a, const int b, const int c)
{
	to[++edge] = b;
	leng[edge] = c;
	next[edge] = start[a];
	start[a] = edge;
}

const int BUFS = 1 << 20;
char buf[BUFS], *p = buf + BUFS;

#define read() \
	do { \
		if (p == buf + BUFS) \
			fread(p = buf, 1, BUFS, stdin); \
	} while (0)

void getint(int& x)
{
	read();
	x = 0;
	bool neg = false;
	while ((*p < '0' || *p > '9') && *p != '-')
	{
		++p;
		read();
	}
	if (*p == '-')
	{
		neg = true;
		++p;
		read();
	}
	while (*p >= '0' && *p <= '9')
	{
		x = x * 10 + *p - '0';
		++p;
		read();
	}
	if (neg)
		x = -x;
#ifdef DB
	fprintf(stderr, "%d read\n", x);
#endif
}

int main()
{
	int _;
	getint(n);
	getint(m);
	getint(_);
	for (int t; _--; )
	{
		getint(t);
		black[t] = true;
	}
	for (int i = 1, a, b, c; i < n; ++i)
	{
		getint(a);
		getint(b);
		getint(c);
		add(a, b, c);
		add(b, a, c);
	}
	printf("%d\n", dfs(1));
}
