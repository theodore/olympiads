// Network flow, SPFA
// Sat Aug 7, 6:03 PM
// Sat Aug 7, 7:02 PM, TLE
#include <cstdio>
#include <cstring>

//namespace
//{
	int maxflow();
	inline int min(int, int);
	const int N(1010);
	const int M(1000010);
	const int dx[] = {0, 1, 1, 0, -1, -1};
	const int dy[] = {1, 1, 0, -1, -1, 0};
	bool in[N][N];
	int n, m;
	int c[N][N][6];
	int d[N][N];
	int px[N][N], py[N][N], pd[N][N];
	int qx[M], qy[M], head, tail;
	int prex[N][N], prey[N][N];
	void output(int, int);
//}

inline int min(int a, int b)
{
	if (a < b)
		return a;
	else
		return b;
}

int maxflow()
{
	int r(0);
	for (; ; )
	{
{
	memset(d, 0x7f, sizeof(d));
	d[0][0] = 0;
	in[0][0] = true;
	head = 0;
	tail = 1;
	qx[0] = qy[0] = 0;
	prex[0][0] = prey[0][0] = -1;
	while (head != tail)
	{
		static int x, y;
		x = qx[head];
		y = qy[head++];
		if (head == M)
			head = 0;
		in[x][y] = false;
		for (int i = 0; i < 6; ++i)
		{
			static int nx, ny;
			nx = x + dx[i];
			ny = y + dy[i];
			if (nx >= 0 && ny >= 0 && nx < n && ny < m && d[nx][ny] > d[x][y] + 1 && c[x][y][i] > 0)
			{
				d[nx][ny] = d[x][y] + 1;
				px[nx][ny] = x;
				py[nx][ny] = y;
				pd[nx][ny] = i;
				prex[nx][ny] = x;
				prey[nx][ny] = y;
				if (!in[nx][ny])
				{
					in[nx][ny] = true;
					qx[tail] = nx;
					qy[tail++] = ny;
					if (tail == M)
						tail = 0;
				}
			}
		}
	}
}
#ifdef DB
		printf("r = %d\n", r);
		printf("d[%d][%d] = %d(0x%x)\n", n - 1, m - 1, d[n-1][m-1], d[n-1][m-1]);
#endif
		if (d[n-1][m-1] == 0x7f7f7f7f)
			return r;
		else
		{
#ifdef DB
			output(n - 1, m - 1);
			putchar(10);
#endif
			int amt(0x7fffffff);
			for (int x = n - 1, y = m - 1, ox, oy; x != 0 || y != 0; x = px[ox][oy], y = py[ox][oy])
			{
				ox = x;
				oy = y;
				amt = min(amt, c[px[x][y]][py[x][y]][pd[x][y]]);
			}
			for (int x = n - 1, y = m - 1, ox, oy; x != 0 || y != 0; x = px[ox][oy], y = py[ox][oy])
			{
				ox = x;
				oy = y;
				c[px[x][y]][py[x][y]][pd[x][y]] -= amt;
#ifdef DB
				printf("%d, %d, c[%d][%d][%d] = %d\n", x, y, px[x][y], py[x][y], pd[x][y], c[px[x][y]][py[x][y]][pd[x][y]]);
#endif
			}
			r += amt;
		}
	}
}

int main()
{
#ifdef LOCAL
	freopen("in", "r", stdin);
	freopen("ans", "w", stdout);
#endif
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
	printf("%d\n", maxflow());
	return 0;
}

void output(int x, int y)
{
	if (x == -1)
		return;
	printf("%d, %d -> ", x, y);
	output(prex[x][y], prey[x][y]);
}
