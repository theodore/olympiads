#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>

#define UPN(a, b) a = std::min(a, b)

const int dx[] = {-1, 0, 1, 0};
const int dy[] = {0, 1, 0, -1};
const int Dir_U = 0;
const int Dir_R = 1;
const int Dir_D = 2;
const int Dir_L = 3;
const int Max_n = 13;
const int Max_s = 1 << 9;
int n, m, p;
int key[Max_n][Max_n];
int pass[Max_n][Max_n][4]; // -1 - wall, 0 - good, else - door
unsigned dist[Max_s][Max_n][Max_n];

int main()
{
    scanf("%d%d%d", &n, &m, &p);
    for (int i = 1; i <= m; i++)
        pass[1][i][Dir_U] = pass[n][i][Dir_D] = -1;
    for (int i = 1; i <= n; i++)
        pass[i][1][Dir_L] = pass[i][m][Dir_R] = -1;
    int z;
    scanf("%d", &z);
    for (int i = 0, a, b, c, d, x; i < z; i++) {
        scanf("%d%d%d%d%d", &a, &b, &c, &d, &x);
        if (x == 0)
            x = -1;
        if (a == c) {
            UPN(b, d);
            pass[a][b][Dir_R] = pass[a][b + 1][Dir_L] = x;
        } else {
            UPN(a, c);
            pass[a][b][Dir_D] = pass[a + 1][b][Dir_U] = x;
        }
    }
    scanf("%d", &z);
    for (int i = 0, x, y, v; i < z; i++) {
        scanf("%d%d%d", &x, &y, &v);
        key[x][y] |= 1 << (v - 1);
    }

    memset(dist, -1, sizeof dist);
    dist[0][1][1] = 0;
    std::queue<int> q;
    for (q.push(0), q.push(1), q.push(1); !q.empty(); ) {
        int s = q.front(); q.pop();
        int x = q.front(); q.pop();
        int y = q.front(); q.pop();
        for (int d = 0; d < 4; d++) {
            if (pass[x][y][d] == -1)
                continue;
            if (pass[x][y][d] == 0 || (s & (1 << (pass[x][y][d] - 1)))) {
                int ns = s, nx = x + dx[d], ny = y + dy[d];
                ns |= key[nx][ny];
                if (dist[s][x][y] + 1 < dist[ns][nx][ny]) {
                    dist[ns][nx][ny] = dist[s][x][y] + 1;
                    q.push(ns);
                    q.push(nx);
                    q.push(ny);
                }
            }
        }
    }
    for (int i = 1; i < (1 << p); i++)
        UPN(dist[0][n][m], dist[i][n][m]);
    printf("%d\n", dist[0][n][m]);
}
