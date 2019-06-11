#include <cstdio>
#include <cstdlib>
#include <cstring>

const int dx[] = {-1, 0, 1, 0},
	  dy[] = {0, 1, 0, -1};
int n, ans;
bool vis[4][100];

bool good(int x, int y)
{
	if (x < 0 || x > 3)
		return false;
	if (y < 0 || y >= n)
		return false;
	if (x == 0 && y == 0)
		return true;
	return !vis[x][y];
}

int pre[4][100];
char str[4][100];

/*
void get_next(int x, int y)
{
	if (x == 0 && y == 0 && next[0][0] != -1)
		return;
	int nx(x - pre[x][y]), ny(y - pre[x][y]);
	next[nx][ny] = pre[x][y];
	get_next(nx, ny);
}
*/

int Ans[1000][7];
char trans[][3] = {"4u", "4d", "4s", "2u", "2d", "2s", "2m"};

void output()
{
	memset(str, ' ', sizeof str);
	/*
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < n; ++j)
			printf("%d ", pre[i][j]);
		putchar(10);
	}
	*/
	//get_next(0, 0);
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < n; ++j)
			// i, 2 * j
			switch (pre[i][j])
			{
				case 0:
					str[i][2*j] = '|';
					break;
				case 1:
					str[i][2*j+1] = '_';
					break;
				case 2:
					str[i+1][2*j] = '|';
					break;
				case 3:
					str[i][2*j-1] = '_';
					break;
				default:
					fprintf(stderr, "%d\n", pre[i][j]);
					exit(1);
			}
	for (int i = 0; i < 4; ++i)
	{
		str[i][2*n-1] = 0;
		puts(str[i]);
	}
	for (int i = 1; i < n; ++i)
		if (1 == pre[0][i-1] || 3 == pre[0][i])
		{
			if (1 == pre[1][i-1] || 3 == pre[1][i])
			{
				if (1 == pre[2][i-1] || 3 == pre[2][i])
					++Ans[i][0];
				else
					++Ans[i][3];
			}
			else
				++Ans[i][5];
		}
		else if (1 == pre[1][i-1] || 3 == pre[1][i])
			++Ans[i][6];
		else
			++Ans[i][4];
}

void search(int x, int y, int c)
{
	int nx, ny;
	if (x == 0 && y == 0 && c == 4 * n)
	{
		++ans;
#ifdef DB
		output();
#endif
		return;
	}
	vis[x][y] = true;
	for (int i = 0; i < 4; ++i)
		if (good(nx = x + dx[i], ny = y + dy[i]))
		{
			pre[nx][ny] = (i + 2) % 4;
			search(nx, ny, c + 1);
		}
	vis[x][y] = false;
}

int main()
{
	freopen("vans.in", "r", stdin);
	freopen("vans.ans", "w", stdout);
	scanf("%d", &n);
	search(0, 0, 0);
	printf("%d\n", ans);
	/*
	for (int i = 1; i < n; ++i)
	{
		for (int j = 0; j < 7; ++j)
			printf("ans[%d][%s] = %d\n", i, trans[j], Ans[i][j]);
		putchar('\n');
	}
	printf("ans = %d\n", ans);
	*/
	return 0;
}
