/** @file job.cpp
 *  @brief SDOI2011, Round 1, Day 2, Problem 2, job.
 *  Just a cost-flow problem.
 *  @author Theodore You <theodoreyou@gmail.com>
 *  @date Mon, 11 Apr 2011 18:41:36 +0800
 */
#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>

#define OP(x) ((((x) - 1) ^ 1) + 1)

typedef long long ll;

const int maxn = 1999;
const int maxm = 760003;
const int inf = 25000011;
int n, m, N;
int S, T;
int start[maxn], to[maxm], next[maxm], cost[maxm], edge;
ll cap[maxm];
int can[257][257];

ll tot_cost;
std::queue<int> q;
bool in[maxn];
ll dist[maxn];
int pre[maxn];
ll flow[maxn];

void add(int a, int b, int c, int d)
{
    to[++edge] = b;
    cap[edge] = c;
    cost[edge] = d;
    next[edge] = start[a];
    start[a] = edge;
}

bool function()
{
    memset(dist, 0x3f, sizeof dist);
    dist[S] = 0;
    flow[S] = ~0ull >> 1;
    q.push(S);
    while (!q.empty())
    {
	int x = q.front();
	q.pop();
	in[x] = false;
	for (int e = start[x]; e; e = next[e])
	    if (cap[e] && dist[to[e]] > dist[x] + cost[e])
	    {
		dist[to[e]] = dist[x] + cost[e];
		pre[to[e]] = e;
		flow[to[e]] = std::min<ll>(flow[x], cap[e]);
		if (!in[to[e]])
		{
		    in[to[e]] = true;
		    q.push(to[e]);
		}
	    }
    }
    if (dist[T] == 0x3f3f3f3f3f3f3f3fll)
	return false;
    ll f;
    tot_cost += dist[T] * (f = flow[T]);
    for (int i = T; i != S; i = to[OP(pre[i])])
    {
	cap[pre[i]] -= f;
	cap[OP(pre[i])] += f;
    }
    return true;
}

int main()
{
#ifndef LOCAL
    freopen("job.in", "r", stdin);
    freopen("job.out", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    N = n + m;
    S = N + 1;
    T = N + 2;
    for (int i = 0, z; i < m; ++i)
    {
	scanf("%d", &z);
	add(n + i, T, z, 0);
	add(T, n + i, 0, 0);
    }
    for (int i = 0; i < n; ++i)
	for (int j = 0; j < m; ++j)
	    scanf("%d", &can[i][j]);
    for (int i = 0, s, t[7], w[7]; i < n; ++i)
    {
	scanf("%d", &s);
	for (int j = 0; j < s; ++j)
	    scanf("%d", t + j);
	t[s] = inf;
	for (int j = 0; j <= s; ++j)
	    scanf("%d", w + j);
	int z = 0;
	for (int j = 0; j <= s; ++j)
	{
	    add(S, i, t[j] - z, w[j]);
	    add(i, S, 0, -w[j]);
	    z = t[j];
	}
	    for (int k = n; k < n + m; ++k)
		if (can[i][k - n])
		{
		    add(i, k, inf, 0);
		    add(k, i, 0, 0);
		}
    }
    while (function())
	;
    printf("%lld\n", tot_cost);
}
