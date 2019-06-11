#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <queue>
#include <utility>

struct state
{
	state(){}
	state(int xx, int yy, int ss) :x(xx), y(yy), s(ss){}
	int x, y;
	int s;
};

const int maxn = 17;
const int maxs = 523;
int n, m, d;
int v[maxn];
char map[maxn][maxn];
int sx, sy;
int f[maxn][maxn][maxs];
std::queue<state> q;
bool in[maxn][maxn][maxs];
int sum[maxs];

int calc()
{
	memset(f, 0x3f, sizeof f);
	f[sx][sy][0] = 0;
	in[sx][sy][0] = true;
	q.push(state(sx, sy, 0));
	while (!q.empty())
	{
		state tmp = q.front();
		const int& x = tmp.x;
		const int& y = tmp.y;
		const int& s = tmp.s;
		q.pop();
		in[x][y][s] = false;
		for (int d = -1; d <= 1; d += 2)
		{
			if (map[x][y + d] == '0' && f[x][y][s] + 1 < f[x][y + d][s])
			{
				f[x][y + d][s] = f[x][y][s] + 1;
				if (!in[x][y + d][s])
				{
					in[x][y + d][s] = true;
					q.push(state(x, y + d, s));
				}
			}
			int xs = 0;
			for (int j = 1; j <= y; ++j)
			{
				char c = map[x - (d == -1)][j];
				if (c >= '1' && c <= '9')
					xs |= 1 << (c - '1');
			}
			if (map[x + d][y] == '0' && f[x][y][s] + 1 < f[x + d][y][s ^ xs])
			{
				f[x + d][y][s ^ xs] = f[x][y][s] + 1;
				if (!in[x + d][y][s ^ xs])
				{
					in[x + d][y][s ^ xs] = true;
					q.push(state(x + d, y, s ^ xs));
				}
			}
		}
	}
#ifdef DB
	for (int i = 1; i <= n; ++i)
	{
		for (int j = 1; j <= m; ++j)
			fprintf(stderr, "(%d,%d,%d,%d)\t", f[i][j][0], f[i][j][1], f[i][j][2], f[i][j][3]);
		fprintf(stderr, "\n");
	}
	abort();
#endif
	int r = 0;
	for (int s = 1; s < (1 << d); ++s)
		r = std::max(r, sum[s] - f[sx][sy][s]);
	return r;
}

int main()
{
	scanf("%d%d%d", &n, &m, &d);
	for (int i = 1; i <= d; ++i)
		scanf("%d", v + i);
	for (int s = 1; s < (1 << d); ++s)
		for (int i = 1; i <= d; ++i)
			if (s & (1 << (i - 1)))
				sum[s] += v[i];
	for (int i = 1; i <= n; ++i)
		scanf("%s", map[i] + 1);
	int ans = 0;
	for (sx = 1; sx <= n; ++sx)
		for (sy = 1; sy <= m; ++sy)
			if (map[sx][sy] == '0')
				ans = std::max(ans, calc());
	printf("%d\n", ans);
}
