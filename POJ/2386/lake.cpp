#include <cstdio>

const int dx[] = {-1, -1, -1,  0,  1,  1,  1,  0};
const int dy[] = {-1,  0,  1,  1,  1,  0, -1, -1};
const int maxn(103);
int n, m;
char map[maxn][maxn];
bool vis[maxn][maxn];

void fill(int x, int y)
{
	vis[x][y] = true;
	for (int i = 0; i < 8; ++i)
	{
		int nx = x + dx[i];
		int ny = y + dy[i];
		if (map[nx][ny] == 'W' && !vis[nx][ny])
			fill(nx, ny);
	}
}

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i)
		scanf("%s", map[i] + 1);
	int c(0);
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
			if (map[i][j] == 'W' && !vis[i][j])
			{
				++c;
				fill(i, j);
			}
	printf("%d\n", c);
	return 0;
}
