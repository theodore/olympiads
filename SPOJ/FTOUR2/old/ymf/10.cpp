/*
 * $File: tim.cpp
 * $Date: Mon Dec 27 13:42:30 2010 CST
 * $Author: Tim
 * $Prob: SPOJ 1825 Free Tour II
 */

#define INPUT		"ftour2.in"
#define OUTPUT		"ftour2.out"

#include <cstdio>
#include <algorithm>
#include <cstring>

namespace Solve
{
	const int N_MAX = 200005,
		  M_MAX = N_MAX * 2,
		  INFINITE = 2000000000;
	int Count;
	int begin[N_MAX + 1], end[M_MAX + 1], next[M_MAX + 1], cost[M_MAX + 1];
	int color[N_MAX + 1];

	inline void AddEdge(int a, int b, int c)
	{
		Count ++;
		next[Count] = begin[a];
		begin[a] = Count;
		end[Count] = b;
		cost[Count] = c;
	}

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

	class Son 
	{
		public:
			int vtx, bnode_max;
			void set(int a_, int b_)
			{
				vtx = a_, bnode_max = b_;
			}
	};

	Son son[N_MAX + 1];
	int f[N_MAX + 1];
	int pcost[N_MAX + 1];
	inline bool cmpson(const Son &a, const Son &b)
	{return a.bnode_max < b.bnode_max;}

	int K;
	bool hash[N_MAX + 1];
	int ans = -INFINITE;

	void solve(FILE *fin, FILE *fout);

	void calc(int vtx);

	int calc_black_node(int vtx, int black_node_max);

	int find_center(int vtx);
}

void Solve::calc(int vtx)
{
	vtx = find_center(vtx);
	int cnt = 0;
	hash[vtx] = true;

	int ch_bnode_max = K - color[vtx], bnode_max = 0;
	for (int now = begin[vtx], ch; now; now = next[now])
	{
		if (hash[ch = end[now]])
			continue;
		int t = calc_black_node(ch, ch_bnode_max);
		if (t != -1)
			son[cnt ++].set(ch, t);
		bnode_max = MAX(bnode_max, t);
		pcost[ch] = cost[now];
	}

	static int G[N_MAX + 1], H[N_MAX + 1];
	int *g = G, *h = H;
	if (!cnt)
		goto deepin;

	std::sort(son, son + cnt, cmpson);

	for (int i = 0; i <= bnode_max; i ++)
		g[i] = h[i] = -INFINITE;

	calc_black_node(son[0].vtx, ch_bnode_max);

	for (int i = 0; i <= son[0].bnode_max; i ++)
	{
		g[i] = f[i] + pcost[son[0].vtx];
		if (i) g[i] = MAX(g[i], g[i - 1]);
		if (g[i] < -INFINITE)
			g[i] = -INFINITE;
		ans = MAX(ans, g[i]);
	}


	for (int i = 1; i < cnt; i ++)
	{
		std::swap(g, h);
		int m = son[i].bnode_max;
		calc_black_node(son[i].vtx, ch_bnode_max);
		for (int j = 0; j <= m; j ++)
		{
			int t = K - j - color[vtx];
			t = MIN(t, son[i - 1].bnode_max);
			int c = f[j] + pcost[son[i].vtx];
			c = MAX(c, -INFINITE);
			if (t >= 0 && ((long long)c + h[t] >= -INFINITE))
				ans = MAX(ans, c + h[t]);
			g[j] = MAX(h[j], c);
			if (j) g[j] = MAX(g[j], g[j - 1]);
		}
	}
	for (int i = 0; i <= son[cnt - 1].bnode_max; i ++)
		ans = MAX(ans, g[i]);

deepin:
	// Deep in
	for (int now = begin[vtx]; now; now = next[now])
		if (!hash[end[now]])
			calc(end[now]);
}


int Solve::find_center(int vtx)
{
	static int q[N_MAX + 1], p[N_MAX + 1], size[N_MAX + 1];
	int head = 0, tail = 1;
	q[1] = vtx, p[1] = 0;
	while (head != tail)
	{
		int x = q[++ head];
		for (int now = begin[x]; now; now = next[now])
			if (end[now] != p[head] && !hash[end[now]])
			{
				tail ++;
				q[tail] = end[now];
				p[tail] = x;
			}
	}
	for (int i = tail; i >= 1; i --)
		size[p[i]] += (++ size[q[i]]);
	int v = N_MAX;
	for (int i = 1; i <= tail; i ++)
	{
		int x = q[i], t = 0;
		for (int now = begin[x]; now; now = next[now])
			if (end[now] != p[i])
				t = MAX(t, size[end[now]]);
		t = MAX(t, tail - size[x]);
		if (t < v)
			v = t, vtx = q[i];
	}
	for (int i = tail; i >= 1; i --)
		size[p[i]] = 0;
	return vtx;
}


int Solve::calc_black_node(int vtx, int black_node_max)
{
	static int q[N_MAX + 1], p[N_MAX + 1], bnode[N_MAX + 1], v[N_MAX + 1];
	static int last_bnode_max = 0;
	if (black_node_max < color[vtx])
		return -1;
	for (int i = 0; i <= last_bnode_max; i ++)
		f[i] = -INFINITE;
	int ret = color[vtx];
	int head = 0, tail = 1;
	q[1] = vtx, p[1] = 0, bnode[1] = color[vtx],  v[1] = 0, f[color[vtx]] = 0;
	while (head != tail)
	{
		int x = q[++ head];
		for (int now = begin[x], ch; now; now = next[now])
			if (!hash[ch = end[now]] && ch != p[head])
			{
				int bn = bnode[head] + color[ch];
				if (bn > black_node_max)
					continue;
				tail ++;
				q[tail] = ch;
				p[tail] = x;
				bnode[tail] = bn;
				ret = MAX(ret, bn);
				v[tail] = v[head] + cost[now];
				f[bn] = MAX(f[bn], v[tail]);
			}
	}
	last_bnode_max = ret;
	return ret;
}

void Solve::solve(FILE *fin, FILE *fout)
{
	int n, m;
	fscanf(fin, "%d%d%d", &n, &K, &m);
	for (int t; m --; )
	{
		fscanf(fin, "%d", &t);
		color[t] = true;
	}
	for (int i = 0; i <= n; i ++)
		f[i] = -INFINITE;
	for (int a, b, c; -- n; )
	{
		fscanf(fin, "%d%d%d", &a, &b, &c);
		AddEdge(a, b, c);
		AddEdge(b, a, c);
	}

	calc(1);
	ans = MAX(0, ans);
	fprintf(fout, "%d\n", ans);
}

int main()
{
#ifdef STDIO
	Solve::solve(stdin, stdout);
#else
	FILE *fin = stdin,
		 *fout = stdout;
	Solve::solve(fin, fout);
	fclose(fin);
	fclose(fout);
#endif
	return 0;
}
