#include <cstdio>
#include <cmath>
#include <cstring>
#include <queue>

#define OP(x) ((((x) - 1) ^ 1) + 1)

const int maxz = 253;
const int maxn = 511;
const int maxm = 250037;
int l, w, n, S, T;
int x[maxz], y[maxz];
int start[maxn], to[maxm], next[maxm], cap[maxm], edge;

void add(const int a, const int b, const int c)
{
    to[++edge] = b;
    cap[edge] = c;
    next[edge] = start[a];
    start[a] = edge;
}

bool intsect(const int a, const int b)
{
    return hypot(x[a] - x[b], y[a] - y[b]) <= 200;
}

void mkgraph()
{
    const int inf = 0xffffff;
    for (int i = 0; i < n; ++i)
    {
	add(i * 2, i * 2 + 1, 1);
	add(i * 2 + 1, i * 2, 1);
	if (y[i] >= w - 100)
	{
	    add(S, i * 2, inf);
	    add(i * 2, S, 0);
	}
	if (y[i] <= 100)
	{
	    add(i * 2 + 1, T, inf);
	    add(T, i * 2 + 1, 0);
	}
	for (int j = i + 1; j < n; ++j)
	    if (intsect(i, j))
	    {
		add(i * 2 + 1, j * 2, inf);
		add(j * 2, i * 2 + 1, 0);
		add(j * 2 + 1, i * 2, inf);
		add(i * 2, j * 2 + 1, 0);
	    }
    }
}

int dist[maxn];

bool markup()
{
    memset(dist, 0x3f, sizeof dist);
    dist[S] = 0;
    std::queue<int> q;
    q.push(S);
    while (!q.empty())
    {
	int v = q.front();
	q.pop();
	for (int e = start[v], t; e; e = next[e])
	    if (cap[e] && dist[v] + 1 < dist[t = to[e]])
	    {
		dist[t] = dist[v] + 1;
		if (t == T)
		    return true;
		q.push(t);
	    }
    }
    return false;
}

int find(int v, int f)
{
#if DB >= 1
    fprintf(stderr, "find %d %d\n", v, f);
#endif
    if (v == T)
	return f;
    int ret = 0;
    for (int e = start[v], t; e; e = next[e])
	if (cap[e] && dist[v] + 1 == dist[to[e]])
	{
	    ret += t = find(to[e], std::min(f, cap[e]));
	    f -= t;
	    cap[e] -= t;
	    cap[OP(e)] += t;
	    if (f == 0)
		return ret;
	}
    if (ret == 0)
	dist[v] = -1;
    return ret;
}

int dinic()
{
    int ans = 0;
    while (markup())
	ans += find(S, ~0u >> 1);
    return ans;
}

int main()
{
    scanf("%d%d%d", &l, &w, &n);
    S = n * 2;
    T = n * 2 + 1;
    for (int i = 0; i < n; ++i)
	scanf("%d%d", &x[i], &y[i]);
    mkgraph();
    printf("%d\n", dinic());
}
