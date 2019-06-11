#include <cstdio>
#include <cstring>
#include <queue>

int n, m;
int dist[1010];
int edge, start[1010], next[4010], length[4010], to[4010];
std::queue <int> q;
bool hash[1010];

void spfa()
{
	hash[1] = true;
	dist[1] = 0;
	q.push(1);
	while (!q.empty()) {
		int now = q.front();
		q.pop();
		hash[now] = false;

		for (int e=start[now]; e; e=next[e])
			if (dist[to[e]] > dist[now] + length[e]) {
				dist[to[e]] = dist[now] + length[e];
				if (!hash[to[e]]) {
					hash[to[e]] = true;
					q.push(to[e]);
				}
			}
	}
}

void add(int a, int b, int c)
{
	to[++edge] = b;
	length[edge] = c;
	next[edge] = start[a];
	start[a] = edge;
}

int main()
{
	scanf("%d%d", &m, &n);
	memset(dist, 0xf, sizeof dist);
	for (int i=0, a, b, c; i<m; ++i)
	{
		scanf("%d%d%d", &a, &b, &c);
		add(a, b, c);
		add(b, a, c);
	}
	spfa();
	printf("%d\n", dist[n]);
	return 0;
}

