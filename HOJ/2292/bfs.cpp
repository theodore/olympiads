#include <cstdio>
#include <cstring>
#include <queue>

const int maxn = 1100003;
const int maxm = 2000003;
int n, m, nn;
int start[maxn], to[maxm], next[maxm], edge;

void add(int a, int b)
{
    to[++edge] = b;
    next[edge] = start[a];
    start[a] = edge;
}

int spfa()
{
    static int dist[maxn];
    std::queue<int> q;
    memset(dist, 0x3f, sizeof dist[0] * (nn + 1));
    dist[1] = 0;
    q.push(1);
    while (!q.empty())
    {
	int x = q.front();
	q.pop();
	for (int e = start[x]; e; e = next[e])
	    if (dist[x] + 1 < dist[to[e]])
	    {
		dist[to[e]] = dist[x] + 1;
		if (to[e] == n)
		    return dist[to[e]];
		q.push(to[e]);
	    }
    }
    return -1;
}

int main()
{
    for (scanf("%d%d", &n, &m), nn = n; m--; )
    {
	int a, b, c;
	scanf("%d%d%d", &a, &b, &c);
	if (c == 1)
	    add(a, b);
	else
	    add(a, ++nn), add(nn, b);
    }
    printf("%d\n", spfa());
}
