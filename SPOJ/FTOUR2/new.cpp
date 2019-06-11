#include <cstdio>
#include <cstring>
#include <algorithm>

namespace addict
{
	struct son_t
	{
		int size, eid, depth;
		bool operator<(const son_t&) const;
	};

	const int maxn = 200003;
	const int maxm = 400003;
	int n, m;
	bool black[maxn];
	bool vis[maxn];
	int size[maxn], tree_size;
	int q[maxn][5];
	int start[maxn], to[maxm], next[maxm], leng[maxm], edge;

	void input();
	void add(const int a, const int b, const int c);
#ifdef DB
	int dfs(int x, int d);
#else
	int dfs(int x);
#endif
	void chroot(const int r, int& ans, int& val);
	int get_size(const int x, const int fa);
	void calc(int r, int l, int& max_depth, int g[], int added);
}

bool addict::son_t::operator<(const son_t& x) const
{
	return size < x.size;
}

void addict::add(const int a, const int b, const int c)
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

void addict::input()
{
	int k;
	getint(n);
	getint(m);
	getint(k);
	for (int t; k--; )
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
}

int addict::get_size(const int x, const int fa)
{
	size[x] = 1;
	for (int e = start[x]; e; e = next[e])
		if (!vis[to[e]] && to[e] != fa)
			size[x] += get_size(to[e], x);
	return size[x];
}

void addict::chroot(const int r, int& ans, int& val)
{
	int front = 0, back = 1;
	q[0][0] = r;
	int now;
	while (front != back)
	{
		int& x = q[front][0];
		int& fa = q[front++][1];
		now = tree_size - size[x];
		for (int e = start[x]; e; e = next[e])
			if (!vis[to[e]] && to[e] != fa)
			{
				now = std::max(now, size[to[e]]);
				q[back][0] = to[e];
				q[back++][1] = x;
			}
		if (now < val)
		{
			val = now;
			ans = x;
		}
	}
}

void addict::calc(int r, int l, int& max_depth, int g[], int added)
{
	int front = 0, back = 1;
	q[0][0] = r;
	q[0][1] = 0;
	q[0][2] = l;
	q[0][3] = black[r];
	q[0][4] = added;
	while (front != back)
	{
		int& x = q[front][0];
		int& fa = q[front][1];
		int& dist = q[front][2];
		int& cnt = q[front][3];
		int& cum = q[front++][4];
		if (cum > max_depth)
			max_depth = cum;
		g[cnt] = std::max(g[cnt], dist);
		for (int e = start[x]; e; e = next[e])
			if (!vis[to[e]] && to[e] != fa)
			{
				q[back][0] = to[e];
				q[back][1] = x;
				q[back][2] = dist + leng[e];
				q[back][3] = cnt + black[to[e]];
				q[back++][4] = cum + std::max(0, leng[e]);
			}
	}
}

#ifdef DB
void tab(const int x)
{
	for (int i = 0; i < x; ++i)
		fprintf(stderr, "  ");
}

int addict::dfs(int x, int d = 0)
#else
int addict::dfs(int x)
#endif
{
#ifdef DB
	tab(d);
	fprintf(stderr, "dfs(%d)\n", x);
#endif
	int rtn = 0, cnt = 0, t;
	t = tree_size = get_size(x, 0);
	chroot(x, x, t);
#ifdef DB
	tab(d);
	fprintf(stderr, "root = %d\n", x);
#endif
	vis[x] = true;
	for (int e = start[x]; e; e = next[e])
		if (!vis[to[e]])
			++cnt;
	son_t* son;
	son = new son_t[cnt];
	cnt = 0;
	for (int e = start[x]; e; e = next[e])
		if (!vis[to[e]])
		{
			son[cnt].eid = e;
			int& s = son[cnt++].size = size[to[e]];
			if (s > size[x])
				s = tree_size - size[x];
		}
	std::sort(son, son + cnt);
#ifdef DB
	tab(d);
	for (int i = 0; i < cnt; ++i)
		fprintf(stderr, " %d", to[son[i].eid]);
	fprintf(stderr, "\n");
#endif
	static int f[maxn], g[maxn];
	memset(f, 0, sizeof (int) * size_t(size[x] + 1));
	int fs = 0;
	for (int i = 0; i < cnt; ++i)
	{
		memset(g, 0, sizeof (int) * size_t(son[i].size + 1));
		calc(to[son[i].eid], leng[son[i].eid], son[i].depth, g, 0);
		for (int j = 1; j <= son[i].size; ++j)
			g[j] = std::max(g[j - 1], g[j]);
		for (int j = 0; j <= std::min(son[i].size, m - black[x]); ++j)
		{
			t = m - black[x] - j;
			if (t > fs)
				t = fs;
			rtn = std::max(rtn, g[j] + f[t]);
		}
		f[0] = std::max(f[0], g[0]);
		for (int j = 1; j <= son[i].size; ++j)
			f[j] = std::max(std::max(f[j - 1], f[j]), g[j]);
		fs = son[i].size;
	}
#ifdef DB
	tab(d);
	for (int i = 0; i < cnt; ++i)
		fprintf(stderr, " %d", to[son[i].eid]);
	fprintf(stderr, "\n");
#endif
#if 0
	for (int i = 0; i < cnt; ++i)
#ifdef DB
		if ((t = dfs(to[son[i].eid], d + 1)) > rtn)
#else
		if ((t = dfs(to[son[i].eid])) > rtn)
#endif
			rtn = t;
#else
	for (int i = 0; i < cnt; ++i)
		if ((2 * son[i].depth > rtn || 2 * son[i].depth < 0) && (t = dfs(to[son[i].eid])) > rtn)
			rtn = t;
#endif
#ifdef DB
	tab(d);
	fprintf(stderr, "rtn = %d\n", rtn);
#endif
	return rtn;
}

int main()
{
	addict::input();
	printf("%d\n", addict::dfs(1));
}
