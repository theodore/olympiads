#include <cstdio>
#include <cstring>
#include <queue>

const int max_n = 507;
const int dx[] = {0, 0, 1, 1};
const int dy[] = {0, 1, 0, 1};
const int ddx[] = {-1, -1, 1, 1};
const int ddy[] = {-1, 1, -1, 1};
const char good[] = "\\//\\";
const char bad[] = "/\\\\/";
int n, m;
int dist[max_n][max_n];
char str[max_n][max_n];
bool in[max_n][max_n];

int SPFA()
{
    for (int i = 1; i<= n; i++)
        scanf("%s", str[i] + 1);
    memset(dist, 0x3f, sizeof dist);
    dist[0][0] = 0;
    std::queue<int> q;
    q.push(0);
    q.push(0);
    while (!q.empty()) {
        int x = q.front();
        q.pop();
        int y = q.front();
        q.pop();
        in[x][y] = false;
#if DB & 1
        fprintf(stderr, "%d %d %d\n", x, y, dist[x][y]);
#endif
        for (int d = 0; d < 4; d++) {
            int i = x + dx[d];
            int j = y + dy[d];
            int nx = x + ddx[d];
            int ny = y + ddy[d];
            if (str[i][j] == good[d] && dist[x][y] < dist[nx][ny]) {
                dist[nx][ny] = dist[x][y];
                if (!in[nx][ny]) {
                    in[nx][ny] = true;
                    q.push(nx);
                    q.push(ny);
                }
            } else if (str[i][j] == bad[d] && dist[x][y] + 1 < dist[nx][ny]) {
                dist[nx][ny] = dist[x][y] + 1;
                if (!in[nx][ny]) {
                    in[nx][ny] = true;
                    q.push(nx);
                    q.push(ny);
                }
            }
        }
    }
    return dist[n][m];
}

int main()
{
    scanf("%d%d", &n, &m);
    if ((n + m) & 1)
        printf("NO SOLUTION\n");
    else
        printf("%d\n", SPFA());
}
