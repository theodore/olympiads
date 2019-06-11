// Network flow, SAP
// Sat Aug 7, 7:39 PM
// Error #1: typed ty wrong as tx somewhere
#include <cstdio>
#include <cstdlib>
#include <cstring>

namespace invoke
{
	void input();
	int maxflow();
	inline int min(int, int);
	const int N(1010);
	const int M(1000010);
	const int dx[] = {0, 1, 1, 0, -1, -1};
	const int dy[] = {1, 1, 0, -1, -1, 0};
	bool vis[N][N];
	int n, m;
	int c[N][N][6];
	int d[N][N], f[N][N];
	int px[N][N], py[N][N], pd[N][N];
	int cur[N][N];
	int cnt[M];
#ifdef G
	void itstime();
#endif
}

inline int invoke::min(int a, int b)
{
	if (a < b)
		return a;
	else
		return b;
}

void invoke::input()
{
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < m - 1; ++j)
		{
			scanf("%d", &c[i][j][0]);
			c[i][j+1][3] = c[i][j][0];
		}
	for (int i = 0; i < n - 1; ++i)
		for (int j = 0; j < m; ++j)
		{
			scanf("%d", &c[i][j][2]);
			c[i+1][j][5] = c[i][j][2];
		}
	for (int i = 0; i < n - 1; ++i)
		for (int j = 0; j < m - 1; ++j)
		{
			scanf("%d", &c[i][j][1]);
			c[i+1][j+1][4] = c[i][j][1];
		}
}

int invoke::maxflow()
{
	int ix = 0, iy = 0, r(0);
	vis[0][0] = true;
	cnt[0] = n * m;
	while (d[0][0] < n * m)
	{
#define nx (ix + dx[i])
#define ny (iy + dy[i])
#ifdef DB
		printf("ix = %d, iy = %d\n", ix, iy);
#endif
		if (ix == 0 && iy == 0)
		{
			memset(f, 0, sizeof(f));
			f[0][0] = 0x7fffffff;
			memset(vis, 0, sizeof(vis));
			vis[0][0] = true;
		}
		if (ix == n - 1 && iy == m - 1)
		{
			r += f[ix][iy];
			for (int x = px[ix][iy], y = py[ix][iy], ox = ix, oy = iy; ox != 0 || oy != 0; ox = x, oy = y, x = px[ox][oy], y = py[ox][oy])
			{
				//vis[ox][oy] = false;
				c[x][y][pd[ox][oy]] -= f[ix][iy];
				c[ox][oy][(pd[ox][oy]+3)%6] += f[ix][iy];
			}
			ix = iy = 0;
#ifdef DB
			printf("r = %d\n", r);
			getchar();
#endif
			continue;
		}
		static bool found;
		found = false;
		for (int i = cur[ix][iy]; i < 6; ++i)
		{
			if (nx >= 0 && ny >= 0 && nx < n && ny < m && d[nx][ny] + 1 == d[ix][iy] && c[ix][iy][i] && !vis[nx][ny])
			{
				found = true;
				cur[ix][iy] = i;
				f[nx][ny] = min(f[ix][iy], c[ix][iy][i]);
				px[nx][ny] = ix;
				py[nx][ny] = iy;
				pd[nx][ny] = i;
				ix = nx;
				iy = ny;
				vis[ix][iy] = true;
				break;
			}
		}
		if (!found)
		{
			int best(n * m - 1);
			for (int i = 0; i < 6; ++i)
				if (nx >= 0 && ny >= 0 && nx < n && ny < m && d[nx][ny] != n * m && !vis[nx][ny] && c[ix][iy][i] && (!found || d[nx][ny] < best))
				{
					found = true;
					cur[ix][iy] = i;
					best = d[nx][ny];
				}
			if (--cnt[d[ix][iy]] == 0)
				return r;
			d[ix][iy] = best + 1;
			++cnt[d[ix][iy]];
			if (ix != 0 || iy != 0)
			{
				vis[ix][iy] = false;
				static int ox;
				ox = ix;
				ix = px[ix][iy];
				iy = py[ox][iy];
			}
		}
#undef nx
#undef ny
	}
	return r;
}

int main()
{
#ifdef LOCAL
#ifndef DB
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
#endif
#endif
	invoke::input();
	printf("%d\n", invoke::maxflow());
	return 0;
}

#ifdef G
void invoke::itstime()
{
	printf("digraph {\n");
	for (int x = 0; x < n; ++x)
		for (int y = 0; y < m; ++y)
			for (int i = 0; i < 6; ++i)
			{
				int nx = x + dx[i], ny = y + dy[i];
				if (nx >= 0 && nx < n && ny >= 0 && ny < m)
					printf("\t\"(%d, %d)\" -> \"(%d, %d)\" [label = %d]\n", x, y, nx, ny, c[x][y][i]);
			}
	printf("}\n");
	exit(0);
}
#endif
