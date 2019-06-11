#include <cstdio>
#include <cmath>
#include <cstring>
#include <queue>
#include <algorithm>

const int dx[] = {0, -1, 0, 1};
const int dy[] = {1, 0, -1, 0};
const int maxn = 33;
int n, m, t;
char map[maxn][maxn];
std::queue<int> q;
int dist[maxn][maxn];
int in[maxn][maxn];

double calc(int ox, int oy)
{
	double a = 0;
	memset(dist, 0x3f, sizeof dist);
	dist[ox][oy] = map[ox][oy] == '1';
	in[ox][oy] = true;
	q.push(ox);
	q.push(oy);
	while (!q.empty())
	{
		int x = q.front();
		q.pop();
		int y = q.front();
		q.pop();
		in[x][y] = false;
		for (int d = 0, s; d < 4; ++d)
		{
			int nx = x + dx[d];
			int ny = y + dy[d];
			if ((map[nx][ny] == '0' && (s = dist[x][y]) < dist[nx][ny]) || (map[nx][ny] == '1' && (s = dist[x][y] + 1) < dist[nx][ny]))
			{
				dist[nx][ny] = s;
				if (!in[nx][ny])
				{
					in[nx][ny] = true;
					q.push(nx);
					q.push(ny);
				}
			}
		}
	}
	double s;
	for (int x = 1; x <= n; ++x)
		for (int y = 1; y <= m; ++y)
			if (dist[x][y] <= t && (s = hypot(x - ox, y - oy)) > a)
				a = s;
	return a;
}

int main()
{
	scanf("%d%d%d", &n, &m, &t);
	for (int i = 1; i <= n; ++i)
		scanf("%s", map[i] + 1);
	double ans = 0;
	for (int x = 1; x <= n; ++x)
		for (int y = 1; y <= m; ++y)
		{
			ans = std::max(ans, calc(x, y));
#ifdef DB
			fprintf(stderr, "%d %d %f\n", x, y, ans);
#endif
		}
	printf("%.6f\n", ans);
}
