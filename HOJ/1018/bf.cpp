#include <cstdio>
#include <cstring>
#include <algorithm>

const int dx[] = {-1, 0, 1, 0};
const int dy[] = {0, -1, 0, 1};
const int maxn = 100007;
const int maxN = (1 << 18);
bool con[maxn][3];
bool vis[maxn][2];
int n;

bool good(int a, int b, int c, int)
{
    if (a == c)
	return con[a][0];
    else
	return con[std::min(a, c)][b + 1];
}

void fill(int x, int y)
{
    if (vis[x][y])
	return;
    vis[x][y] = true;
    for (int d = 0; d < 4; ++d)
    {
	int nx = x + dx[d];
	int ny = y + dy[d];
	if (nx >= 1 && nx <= n && ny >= 0 && ny <= 1 && good(x, y, nx, ny))
	    fill(nx, ny);
    }
}

bool ask(int l, const int a, int r, const int b)
{
    memset(vis, 0, sizeof vis);
    fill(l, a);
    return vis[r][b];
}

int main()
{
    char s[11];
    int a, b, c, d;
    scanf("%d", &n);
    while (scanf("%s%d%d%d%d", s, &b, &a, &d, &c) != 1)
    {
	switch (s[0])
	{
	case 'O':
	case 'C':
	    if (a == c)
		con[a][0] = s[0] == 'O';
	    else
	    {
		a = std::min(a, c);
		con[a][b] = s[0] == 'O';
	    }
	    break;
	default:
	    if (a > c)
	    {
		std::swap(a, c);
		std::swap(b, d);
	    }
	    printf(ask(a, b - 1, c, d - 1) ? "Y\n" : "N\n");
	}
    }
}
