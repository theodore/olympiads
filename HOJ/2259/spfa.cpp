#include <cstdio>
#include <cstring>
#include <queue>

const int maxn = 1000007;
int dist[maxn];
int g[maxn];
bool in[maxn];
int n;

int main()
{
    scanf("%d", &n);
    for (int i = 0, x; i < n; ++i)
    {
	scanf("%d", &x);
	g[i] = i + 1 + x;
    }
    memset(dist, 0x3f, sizeof dist);
    dist[0] = 0;
    in[n] = true;
    std::queue<int> q;
    q.push(0);
    while (!q.empty())
    {
	const int x = q.front();
	q.pop();
	in[x] = false;
	if (x && dist[x + 1] > dist[x] + 1)
	{
	    dist[x + 1] = dist[x] + 1;
	    if (!in[x + 1])
		q.push(x + 1);
	}
	if (x && dist[x - 1] > dist[x] + 1)
	{
	    dist[x - 1] = dist[x] + 1;
	    if (!in[x - 1])
		q.push(x - 1);
	}
	int t = std::min(g[x], n);
	if (dist[t] > dist[x] + g[x] - t)
	{
	    dist[t] = dist[x] + g[x] - t;
	    if (!in[t])
		q.push(t);
	}
    }
    printf("%d\n", dist[n]);
}
