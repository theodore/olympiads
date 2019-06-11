#include <cstdio>
#include <cstring>
#include <queue>

const int maxn = 1003;
const int dx[] = {-1, 0, 1, 0};
const int dy[] = {0, -1, 0, 1};
int n, m;
std::queue<int> q;
bool vis[maxn][maxn];
int dist[maxn][maxn];

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i)
    {
	static char s[maxn];
	vis[i][0] = vis[i][m + 1] = true;
	scanf("%s", s + 1);
	for (int j = 1; j <= m; ++j)
	    if (s[j] == '1')
	    {
		vis[i][j] = true;
		q.push(i);
		q.push(j);
	    }
    }
    memset(vis[0], true, sizeof vis[0]);
    memset(vis[n + 1], true, sizeof vis[n + 1]);
    while (!q.empty())
    {
	int x = q.front(); q.pop();
	int y = q.front(); q.pop();
	for (int d = 0; d < 4; ++d)
	{
	    int nx = x + dx[d];
	    int ny = y + dy[d];
	    if (!vis[nx][ny])
	    {
		vis[nx][ny] = true;
		dist[nx][ny] = dist[x][y] + 1;
		q.push(nx);
		q.push(ny);
	    }
	}
    }
    for (int i = 1; i <= n; ++i)
    {
	for (int j = 1; j < m; ++j)
	    printf("%d ", dist[i][j]);
	printf("%d\n", dist[i][m]);
    }
}
