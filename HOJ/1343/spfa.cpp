#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>

namespace
{
    const int maxz = 103;
    const int maxn = 207;

    struct Rect_t
    {
	int x0, y0, x1, y1;
    };

    Rect_t rect[maxz];
    int lenx[maxn], leny[maxn];
    bool not_feasible[maxn][maxn][2];
    int n, m, z;

    void rehashx();
    void rehashy();
    void blk_the_road();
    int spfa();
}

namespace
{
    struct Sort_t
    {
	int id, real;
	bool zero;

	bool operator<(const Sort_t& x) const
	{ return real < x.real; }
    };

    Sort_t tmp[maxn];

    void rehashx()
    {
	for (int i = 0; i < z; ++i)
	{
	    tmp[i * 2].real = rect[i].x0;
	    tmp[i * 2].zero = true;
	    tmp[i * 2 + 1].real = rect[i].x1;
	    tmp[i * 2 + 1].zero = false;
	    tmp[i * 2].id = tmp[i * 2 + 1].id = i;
	}
	std::sort(tmp, tmp + 2 * z);
	(tmp[0].zero ? rect[tmp[0].id].x0 : rect[tmp[0].id].x1) = n = 1;
	for (int i = 1; i < 2 * z; ++i)
	{
	    lenx[n] = tmp[i].real - tmp[i - 1].real;
	    (tmp[i].zero ? rect[tmp[i].id].x0 : rect[tmp[i].id].x1) = n
		+= tmp[i].real != tmp[i - 1].real;
	}
    }

    void rehashy()
    {
	for (int i = 0; i < z; ++i)
	{
	    tmp[i * 2].real = rect[i].y0;
	    tmp[i * 2].zero = true;
	    tmp[i * 2 + 1].real = rect[i].y1;
	    tmp[i * 2 + 1].zero = false;
	    tmp[i * 2].id = tmp[i * 2 + 1].id = i;
	}
	std::sort(tmp, tmp + 2 * z);
	(tmp[0].zero ? rect[tmp[0].id].y0 : rect[tmp[0].id].y1) = m = 1;
	for (int i = 1; i < 2 * z; ++i)
	{
	    leny[m] = tmp[i].real - tmp[i - 1].real;
	    (tmp[i].zero ? rect[tmp[i].id].y0 : rect[tmp[i].id].y1) = m
		+= tmp[i].real != tmp[i - 1].real;
	}
    }

    void blk_the_road()
    {
	for (int i = 0; i < z; ++i)
	{
	    for (int j = rect[i].x0; j < rect[i].x1; ++j)
		for (int k = rect[i].y0 + 1; k < rect[i].y1; ++k)
		    not_feasible[j][k][0] = true;
	    for (int j = rect[i].x0 + 1; j < rect[i].x1; ++j)
		for (int k = rect[i].y0; k < rect[i].y1; ++k)
		    not_feasible[j][k][1] = true;
	}
    }

    const int dx[] = {1, 0, -1, 0};
    const int dy[] = {0, 1, 0, -1};
    bool black[maxn][maxn];

    int test(int x, int y, int d)
    {
	if (d > 1)
	{
	    x += dx[d];
	    y += dy[d];
	    d -= 2;
	}
	if (not_feasible[x][y][d])
	    return 0;
	return d ? leny[y] : lenx[x];
    }

    bool test2(int x, int y, int d)
    {
	if (d < 2)
	{
	    x += dx[d];
	    y += dy[d];
	}
	else
	    d -= 2;
	return not_feasible[x][y][!d];
    }

    void fill(int x, int y)
    {
#if DB >= 1
	fprintf(stderr, "fill %d %d\n", x, y);
#endif
	black[x][y] = true;
	for (int d = 0; d < 4; ++d)
	{
	    int nx = x + dx[d];
	    int ny = y + dy[d];
	    if (nx > 0 && nx < n && ny > 0 && ny < m
		    && test2(x, y, d) && !black[nx][ny])
		fill(nx, ny);
	}
    }

    int spfa()
    {
	fill(rect[0].x0, rect[0].y0);
	int sx, sy;
	for (int i = 1; i < n; ++i)
	    for (int j = 1; j < m; ++j)
		if (black[i][j])
		{
		    sx = i;
		    sy = j;
		    goto out;
		}
out:
#if DB >= 1
	fprintf(stderr, "%d, %d\n", sx, sy);
	for (int j = 7; j >= 0; --j)
	{
	    for (int i = 0; i <= 7; ++i)
		fprintf(stderr, "%d", black[i][j]);
	    fprintf(stderr, "\n");
	}
#endif
	static int dist[maxn][maxn][1 << 4];
	static bool in[maxn][maxn][1 << 4];
	const int mainx[] = {rect[0].x0, rect[0].x0, rect[0].x1 - 1, rect[0].x1 - 1};
	const int mainy[] = {rect[0].y0, rect[0].y1 - 1, rect[0].y0, rect[0].y1 - 1};
	memset(dist, 0x3f, sizeof dist);
	dist[sx][sy][0] = 0;
	std::queue<int> q;
	q.push(sx);
	q.push(sy);
	q.push(0);
#if DB >= 1
	fprintf(stderr, "%d %d\n", sx, sy);
#endif
	while (!q.empty())
	{
	    int x = q.front(); q.pop();
	    int y = q.front(); q.pop();
	    int s = q.front(); q.pop();
	    in[x][y][s] = false;
#if DB >= 2
	    fprintf(stderr, "%d %d %d %d\n", x, y, s, dist[x][y][s]);
#endif
	    for (int d = 0; d < 4; ++d)
	    {
		int nx = x + dx[d];
		int ny = y + dy[d];
		int t;
		if (nx > 0 && nx <= n && ny > 0 && ny <= m
			&& (t = test(x, y, d)))
		{
		    int ns = s;
		    if (d & 1)
			for (int i = 0; i < 4; ++i)
			    if (mainy[i] == std::min(y, ny) && mainx[i] < nx)
				ns ^= 1 << i;
		    if ((t += dist[x][y][s]) < dist[nx][ny][ns])
		    {
			dist[nx][ny][ns] = t;
			if (!in[nx][ny][ns])
			{
			    in[nx][ny][ns] = true;
			    q.push(nx);
			    q.push(ny);
			    q.push(ns);
			}
		    }
		}
	    }
	}
	return dist[sx][sy][(1 << 4) - 1];
    }
}

int main()
{
    scanf("%d", &z);
    for (int i = 0; i < z; ++i)
	scanf("%d%d%d%d", &rect[i].x0, &rect[i].y0, &rect[i].x1, &rect[i].y1);
    rehashx();
    rehashy();
    blk_the_road();
    printf("%d\n", spfa());
}
