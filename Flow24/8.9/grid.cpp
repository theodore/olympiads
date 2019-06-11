#include <climits>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>

#define OP(x) ((((x) - 1) ^ 1) + 1)

const int Max_v = 50 * 50;
const int Max_e = 6 * Max_v;
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
            r += t;
            f -= t;
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
    int n, m, sum = 0;
    scanf("%d%d", &n, &m);
    S = n * m;
    T = S + 1;
    for (int i = 0; i < n; i++)
        for (int j = 0, x; j < m; j++) {
            scanf("%d", &x);
            sum += x;
            if ((i ^ j) & 1)
                Ins(S, i * m + j, x);
            else
                Ins(i * m + j, T, x);
        }
    const int INF = INT_MAX / 10;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m - 1; j++)
            if ((i ^ j) & 1)
                Ins(i * m + j, i * m + j + 1, INF);
            else
                Ins(i * m + j + 1, i * m + j, INF);
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < m; j++)
            if ((i ^ j) & 1)
                Ins(i * m + j, i * m + j + m, INF);
            else
                Ins(i * m + j + m, i * m + j, INF);
    printf("%d\n", sum - Dinics());
}
