#include <cstdio>
#include <cstring>
#include <queue>

const int maxn = 100003;
const int maxm = 1000003;
int n, m;
int start[maxn], to[maxm], next[maxm], edge, len[maxm];

void add(int a, int b, int c)
{
    to[++edge] = b;
    len[edge] = c;
    next[edge] = start[a];
    start[a] = edge;
}

int spfa()
{
    static int dist[maxn];
    static bool in[maxn];
    std::queue<int> q;
    memset(dist, 0x3f, sizeof dist[0] * (n + 1));
    dist[1] = 0;
    q.push(1);
    while (!q.empty())
    {
	int x = q.front();
	q.pop();
	in[x] = false;
	for (int e = start[x]; e; e = next[e])
	    if (dist[x] + len[e] < dist[to[e]])
	    {
		dist[to[e]] = dist[x] + len[e];
		if (!in[to[e]])
		    in[to[e]] = true, q.push(to[e]);
	    }
    }
    return dist[n];
}

int main()
{
    for (scanf("%d%d", &n, &m); m--; )
    {
	int a, b, c;
	scanf("%d%d%d", &a, &b, &c);
	add(a, b, c);
    }
    printf("%d\n", spfa());
}
