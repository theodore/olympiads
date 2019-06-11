#include <cstdio>
#include <cstring>
#include <algorithm>

#define ever (; ; )
#define OP(x) ((((x) - 1) ^ 1) + 1)

const int maxn = 107;
const int maxm = 5230;
const int maxnr = 53;
int n, m, k, s, t;
int demand[maxnr][maxnr];
int supply[maxnr][maxnr];
int start[maxn], to[maxm], next[maxm], cost[maxm], cap[maxm], edge;
int needed_flow;

void add(const int a, const int b, const int c, const int d)
{
	to[++edge] = b;
	cap[edge] = c;
	cost[edge] = d;
	next[edge] = start[a];
	start[a] = edge;
}

void add_src(int src[])
{
	for (int i = 1; i <= m; ++i)
	{
		add(s, i, src[i], 0);
		add(i, s, 0, 0);
	}
}

void add_snk(int snk[])
{
	for (int i = 1; i <= n; ++i)
	{
		add(i + m, t, snk[i], 0);
		add(t, i + m, 0, 0);
		needed_flow += snk[i];
	}
}

int flow[maxn], pre[maxn];
int dist[maxn];
int q[maxn], head, tail;
bool in[maxn];

bool spfa()
{
	memset(dist, 0x7f, sizeof dist);
	dist[s] = 0;
	flow[s] = 0x7fffffff;
	in[s] = true;
	head = 0;
	tail = 1;
	q[0] = s;
	while (head != tail)
	{
#ifdef DB
		//fprintf(stderr, "%d, %d\n", head, tail);
#endif
		int x = q[head++];
		if (head == maxn)
			head = 0;
		in[x] = false;
		for (int e = start[x]; e; e = next[e])
			if (cap[e] && dist[to[e]] > dist[x] + cost[e])
			{
				dist[to[e]] = dist[x] + cost[e];
				pre[to[e]] = e;
				flow[to[e]] = std::min(flow[x], cap[e]);
				if (!in[to[e]])
				{
					in[to[e]] = true;
					q[tail++] = to[e];
					if (tail == maxn)
						tail = 0;
				}
			}
	}
	return dist[t] != 0x7f7f7f7f;
}

int spfa_flow()
{
	int ansf = 0, ansc = 0;
	while (spfa())
	{
#ifdef DB
		fprintf(stderr, "in while\n");
#endif
		ansf += flow[t];
		for (int i = t; i != s; i = to[OP(pre[i])])
		{
			ansc += flow[t] * cost[pre[i]];
			cap[pre[i]] -= flow[t];
			cap[OP(pre[i])] += flow[t];
		}
#ifdef DB
		fprintf(stderr, "out while\n");
		fprintf(stderr, "ansf = %d, ansc = %d\n", ansf, ansc);
		getchar();
#endif
	}
	return ansf == needed_flow ? ansc : -1;
}

int main()
{
	for ever
	{
		scanf("%d%d%d", &n, &m, &k);
		if (!n && !m && !k)
			break;
		for (int i = 1; i <= n; ++i)
			for (int j = 0; j < k; ++j)
				scanf("%d", &demand[j][i]);
		for (int i = 1; i <= m; ++i)
			for (int j = 0; j < k; ++j)
				scanf("%d", &supply[j][i]);
		s = n + m + 1;
		t = s + 1;
        int ans = 0;
		for (int i = 0, tt = 0; i < k; ++i)
		{
#ifdef DB
			fprintf(stderr, "tt = %d\n", tt);
#endif
			if (~tt)
			{
				memset(start, 0, sizeof start);
				edge = 0;
				needed_flow = 0;
				add_src(supply[i]);
				add_snk(demand[i]);
#ifdef DB
				fprintf(stderr, "edge = %d\n", edge);
#endif
				for (int x = 1, r; x <= n; ++x)
					for (int y = 1; y <= m; ++y)
					{
						scanf("%d", &r);
						add(y, x + m, 1000, r);
						add(x + m, y, 0, -r);
					}
				tt = spfa_flow();
				if (tt == -1)
					ans = tt;
				else
					ans += tt;
			}
			else
				for (int x = 1, r; x <= n; ++x)
					for (int y = 1; y <= m; ++y)
						scanf("%d", &r);
		}
		printf("%d\n", ans);
	}
}
