#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>

#define UPN(a, b) a = std::min(a, b)

const int dx[] = {0, 1, 0, -1};
const int dy[] = {1, 0, -1, 0};
const int Max_n = 103;
const int Max_k = 13;
int n, K, A, B, C;
bool gas[Max_n][Max_n];
unsigned dist[Max_n][Max_n][Max_k];
#if DB & 2
int pre[Max_n][Max_n][Max_k][3];
#endif

int main()
{
    scanf("%d%d%d%d%d", &n, &K, &A, &B, &C);
    for (int i = 1; i <= n; i++)
        for (int j = 1, x; j <= n; j++) {
            scanf("%d", &x);
            gas[i][j] = x;
        }
    memset(dist, -1, sizeof dist);
    dist[1][1][K] = 0;
    std::queue<int> q;
    static bool in[Max_n][Max_n][Max_k];
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            in[i][j][0] = true;
    for (q.push(1), q.push(1), q.push(K); !q.empty(); ) {
        int x = q.front(); q.pop();
        int y = q.front(); q.pop();
        int k = q.front(); q.pop();
        in[x][y][k] = false;
#if DB & 1
        fprintf(stderr, "dist[%d %d %d] = %d\n", x, y, k, dist[x][y][k]);
#endif
        for (int d = 0; d < 4; d++) {
            int nx = x + dx[d];
            int ny = y + dy[d];
            if (nx > 0 && nx <= n && ny > 0 && ny <= n) {
                int v = (d < 2 ? 0 : B) + A, nk = K;
                if (!gas[nx][ny]) {
                    v += C;
                    if (nk >= 0 && dist[x][y][k] + v < dist[nx][ny][nk]) {
                        dist[nx][ny][nk] = dist[x][y][k] + v;
#if DB & 2
                        pre[nx][ny][nk][0] = x;
                        pre[nx][ny][nk][1] = y;
                        pre[nx][ny][nk][2] = k;
#endif
                        if (!in[nx][ny][nk]) {
                            in[nx][ny][nk] = true;
                            q.push(nx);
                            q.push(ny);
                            q.push(nk);
                        }
                    }

                    nk = k - 1;
                    v -= C + A;
                }
                if (nk >= 0 && dist[x][y][k] + v < dist[nx][ny][nk]) {
                    dist[nx][ny][nk] = dist[x][y][k] + v;
#if DB & 2
                    pre[nx][ny][nk][0] = x;
                    pre[nx][ny][nk][1] = y;
                    pre[nx][ny][nk][2] = k;
#endif
                    if (!in[nx][ny][nk]) {
                        in[nx][ny][nk] = true;
                        q.push(nx);
                        q.push(ny);
                        q.push(nk);
                    }
                }
            }
        }
    }
    for (int i = 1; i <= K; i++)
        UPN(dist[n][n][0], dist[n][n][i]);
    printf("%d\n", dist[n][n][0]);
#if DB & 2
    for (int x = n, y = n, k = 1, px, py, pk; x | y | k; x = px, y = py, k = pk) {
        fprintf(stderr, "dist[%d %d %d] = %d\n", x, y, k, dist[x][y][k]);
        px = pre[x][y][k][0];
        py = pre[x][y][k][1];
        pk = pre[x][y][k][2];
    }
#endif
}
