#include <cstdio>
#include <cstring>
#include <algorithm>

#define OP(x) ((((x) - 1) ^ 1) + 1)

const int maxn = 307;
const int maxm = 200003;
int n, m, s, t;
int start[maxn], to[maxm], next[maxm], cap[maxm], edge;

void add(const int a, const int b, const int c)
{
#ifdef DB
    fprintf(stderr, "%d -> %d : %d\n", a, b, c);
#endif
    to[++edge] = b;
    cap[edge] = c;
    next[edge] = start[a];
    start[a] = edge;
}

int sap()
{
    static const int inf = -1u >> 1;
    static int dist[maxn];
    static int cur[maxn];
    static int flow[maxn];
    static int cnt[maxn];
    static int pre[maxn];
    memcpy(cur, start, sizeof cur[0] * size_t(n + 1));
    cnt[0] = n;
    int rtn = 0;
    int i = s;
    while (dist[s] < n)
    {
#ifdef DB
	fprintf(stderr, "%d %d %d\n", i, dist[i], flow[i]);
	getchar();
#endif
	if (i == s)
	    flow[i] = inf;
	bool found = false;
	for (int e = cur[i]; e; e = next[e])
	    if (cap[e] && dist[to[e]] + 1 == dist[i])
	    {
		found = true;
		cur[i] = e;
		flow[to[e]] = std::min(flow[i], cap[e]);
		i = to[e];
		pre[i] = e;
		break;
	    }
#ifdef DB
	fprintf(stderr, "%d\n", __LINE__);
#endif
	if (i == t)
	{
	    rtn += flow[i];
	    do
	    {
		cap[pre[i]] -= flow[t];
		cap[OP(pre[i])] += flow[t];
		i = to[OP(pre[i])];
	    } while (i != s);
	}
#ifdef DB
	fprintf(stderr, "%d\n", __LINE__);
#endif
	if (!found)
	{
	    if (--cnt[dist[i]] == 0)
		break;
	    dist[i] = n;
	    for (int e = start[i]; e; e = next[e])
		if (cap[e] && dist[to[e]] + 1 < dist[i])
		{
		    dist[i] = dist[to[e]] + 1;
		    cur[i] = e;
		}
	    ++cnt[dist[i]];
	    if (i != s)
		i = to[OP(pre[i])];
	}
    }
    return rtn;
}

int main()
{
    scanf("%d%d", &n, &m);
    s = n + 1;
    t = n + 2;
    for (int i = 1, x; i <= n; ++i)
    {
	scanf("%d", &x);
	if (x)
	{
	    add(s, i, 1);
	    add(i, s, 0);
	}
	else
	{
	    add(i, t, 1);
	    add(t, i, 0);
	}
    }
    n += 2;
    for (int a, b; m--; )
    {
	scanf("%d%d", &a, &b);
	add(a, b, 1);
	add(b, a, 1);
    }
    printf("%d\n", sap());
}
