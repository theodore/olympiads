#include <climits>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>

#define OP(x) ((((x) - 1) ^ 1) + 1)

const int Max_v = 400;
const int Max_e = 40000;
const int INF = INT_MAX / 4;
int n, m, S, T;
int start[Max_v], to[Max_e], next[Max_e], cap[Max_e], edge;

void Add(int a, int b, int c)
{
    to[++edge] = b;
    next[edge] = start[a];
    start[a] = edge;
    cap[edge] = c;
}

unsigned dist[Max_v];

bool MarkUp()
{
    std::queue<int> q;
    memset(dist, -1, sizeof dist);
    dist[S] = 0;
    q.push(S);
    while (!q.empty()) {
        int x = q.front();
        q.pop();
        for (int e = start[x]; e; e = next[e])
            if (cap[e] && dist[x] + 1 < dist[to[e]]) {
                dist[to[e]] = dist[x] + 1;
                if (to[e] == T)
                    return true;
                q.push(to[e]);
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
    while (MarkUp())
        r += Flow(S, INF);
    return r;
}

int main()
{
    scanf("%d%d", &n, &m);
    S = n * 2 + 1;
    T = S + 1;
    for (int i = 1; i <= n; i++) {
        Add(S, i, 1);
        Add(i, S, 0);
        Add(i + n, T, 1);
        Add(T, i + n, 0);
    }
    for (int i = 0, a, b; i < m; i++) {
        scanf("%d%d", &a, &b);
        Add(a, b + n, 1);
        Add(b + n, a, 0);
    }
    printf("%d\n", n - Dinics());
}
