#include <climits>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>

#define OP(x) ((((x) - 1) ^ 1) + 1)

const int dx[] = {1, 2, 2, 1};
const int dy[] = {2, 1, -1, -2};
const int Max_v = 40300;
const int Max_e = 400300;
const int Max_n = 233;
int S, T;
int start[Max_v], to[Max_e], next[Max_e], cap[Max_e], edge;

void Add(int a, int b, int c)
{
    to[++edge] = b;
    next[edge] = start[a];
    start[a] = edge;
    cap[edge] = c;
}

void Ins(int a, int b, int c, int d = 0)
{
    Add(a, b, c);
    Add(b, a, d);
}

unsigned dist[Max_v];

bool BFS()
{
    memset(dist, -1, sizeof dist);
    dist[S] = 0;
    std::queue<int> q;
    for (q.push(S); !q.empty(); ) {
        int x = q.front();
        q.pop();
        for (int e = start[x], t; e; e = next[e])
            if (cap[e] && dist[x] + 1 < dist[t = to[e]]) {
                dist[t] = dist[x] + 1;
                if (t == T)
                    return true;
                q.push(t);
            }
    }
    return false;
}

int Flow(int x, int f)
{
    if (x == T)
        return f;
    int r = 0;
    for (int e = start[x]; e && f; e = next[e])
        if (cap[e] && dist[x] + 1 == dist[to[e]]) {
            int t = Flow(to[e], std::min(f, cap[e]));
            f -= t;
            r += t;
            cap[e] -= t;
            cap[OP(e)] += t;
        }
    if (!r)
        dist[x] = -1;
    return r;
}

int Dinics()
{
    int r = 0;
    while (BFS())
        r += Flow(S, INT_MAX);
    return r;
}

int main()
{
    static bool obs[Max_n][Max_n];
    int n, m;
    scanf("%d%d", &n, &m);
    S = (n + 1) * n + 1;
    T = S + 1;
    for (int i = 0, x, y; i < m; i++) {
        scanf("%d%d", &x, &y);
        obs[x][y] = true;
    }
    int ans = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            if (!obs[i][j]) {
                ans++;
                if ((i ^ j) & 1)
                    Ins(S, i * n + j, 1);
                else
                    Ins(i * n + j, T, 1);
                for (int d = 0; d < 4; d++) {
                    int x = i + dx[d];
                    int y = j + dy[d];
                    if (x > 0 && x <= n && y > 0 && y <= n && !obs[x][y]) {
                        if ((i ^ j) & 1)
                            Ins(i * n + j, x * n + y, 1);
                        else
                            Ins(x * n + y, i * n + j, 1);
                    }
                }
            }
    printf("%d\n", ans - Dinics());
}
