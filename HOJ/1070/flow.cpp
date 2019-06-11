#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>

#define OP(x) ((((x) - 1) ^ 1) + 1)

const int maxn = 4333;
const int maxm = 74003;
const int mul = 61;
int n, m, S, T;
int start[maxn], to[maxm], next[maxm], cap[maxm], cost[maxm], edge;

void add(const int a, const int b, const int c, const int d)
{
    to[++edge] = b;
    cap[edge] = c;
    cost[edge] = d;
    next[edge] = start[a];
    start[a] = edge;
}

void init()
{
    scanf("%d%d", &n, &m);
    S = (n + m) * mul + 1;
    T = S + 1;
    for (int i = 0; i < n * mul; i += mul)
    {
	add(S, i, mul, 0);
	add(i, S, 0, 0);
	for (int j = i + 1; j < i + mul; ++j)
	{
	    add(i, j, 1, 0);
	    add(j, i, 0, 0);
	}
    }
    for (int i = n * mul; i < (n + m) * mul; i += mul)
    {
	add(i, T, 1, 0);
	add(T, i, 0, 0);
	for (int j = i + 1; j < i + mul; ++j)
	{
	    add(j, i, 1, 0);
	    add(i, j, 0, 0);
	}
    }
    for (int i = n * mul; i < (n + m) * mul; i += mul)
	for (int j = 0, x; j < n * mul; j += mul)
	{
	    scanf("%d", &x);
	    for (int k = 1; k < mul; ++k)
	    {
		add(j + k, i + k, 1, x * k);
		add(i + k, j + k, 0, -x * k);
	    }
	}
}

std::queue<int> q;
int dist[maxn], flow[maxn], pre[maxn];
bool in[maxn];

bool spfa()
{
    static const int inf = 0x3f3f3f3f;
    memset(dist, inf, sizeof dist);
    dist[S] = 0;
    flow[S] = inf;
    q.push(S);
    while (!q.empty())
    {
	int x = q.front();
	q.pop();
	in[x] = false;
	for (int e = start[x]; e; e = next[e])
	    if (cap[e] && dist[x] + cost[e] < dist[to[e]])
	    {
		dist[to[e]] = dist[x] + cost[e];
		flow[to[e]] = std::min(flow[x], cap[e]);
		pre[to[e]] = e;
		if (!in[to[e]])
		{
		    in[to[e]] = true;
		    q.push(to[e]);
		}
	    }
    }
    return dist[T] != inf;
}

double cost_flow()
{
    int rtn = 0;
    while (spfa())
    {
#ifdef DB
	fprintf(stderr, "%d %d\n", dist[T], flow[T]);
#endif
	rtn += dist[T] * flow[T];
	for (int i = T; i != S; i = to[OP(pre[i])])
	{
	    cap[pre[i]] -= flow[T];
	    cap[OP(pre[i])] += flow[T];
#ifdef DB
	    fprintf(stderr, " %d\n", i);
#endif
	}
    }
    return rtn;
}

int main()
{
    init();
    printf("%.2f\n", cost_flow() / m);
}
