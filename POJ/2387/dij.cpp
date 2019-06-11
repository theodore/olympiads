#include <cstdio>
#include <cstdlib>
#include <cstring>

const int maxn(1003);
const int maxm(4003);
int n, m;
int dist[maxn];
int edge, start[maxn], next[maxm], len[maxm], to[maxm];

bool vis[maxn];
int h[maxm], hs;
void push(int);
int pop();

void push(int e)
{
	int p;
	for (p = ++hs; p != 1; p >>= 1)
		if (len[e] < len[h[p >> 1]])
			h[p] = h[p >> 1];
		else
			break;
	h[p] = e;
}

int pop()
{
	int ret(h[1]), p, next, e(h[hs--]);
	for (p = 1; (p << 1) <= hs; p = next)
	{
		next = p << 1;
		if (next < hs && len[h[next+1]] < len[h[next]])
			++next;
		if (len[h[next]] < len[e])
			h[p] = h[next];
		else
			break;
	}
	h[p] = e;
	return ret;
}

void dij()
{
	dist[1] = 0;
	vis[1] = true;
	for (int e = start[1]; e; e = next[e])
		push(e);
	for (int _ = 1, ed; _ < n; ++_)
	{
		do
		{
			ed = pop();
		}
		while (vis[to[ed]]);
		vis[to[ed]] = true;
		dist[to[ed]] = len[ed];
		if (to[ed] == n)
			return;
		for (int e = start[to[ed]]; e; e = next[e])
			if (!vis[to[e]])
			{
				len[e] += dist[to[ed]];
				push(e);
			}
	}
}

void add(int a, int b, int c)
{
	to[++edge] = b;
	len[edge] = c;
	next[edge] = start[a];
	start[a] = edge;
}

int main()
{
	scanf("%d%d", &m, &n);
	memset(dist, 0x7f, sizeof dist);
	for (int i=0, a, b, c; i<m; ++i)
	{
		scanf("%d%d%d", &a, &b, &c);
		add(a, b, c);
		add(b, a, c);
	}
	dij();
	printf("%d\n", dist[n]);
	return 0;
}

