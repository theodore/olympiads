#include <climits>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>

#define OP(x) ((((x) - 1) ^ 1) + 1)

const int Max_n = 500;
const int Max_m = 1000 + 2 * 150 * 270;
int S, T;
int start[Max_n], next[Max_m], to[Max_m], cap[Max_m], edge;

void Add(int a, int b, int c)
{
    to[++edge] = b;
    next[edge] = start[a];
    start[a] = edge;
    cap[edge] = c;
}

unsigned dist[Max_n];

bool BFS()
{
    memset(dist, -1, sizeof dist);
    dist[S] = 0;
    std::queue<int> q;
    q.push(S);
    while (!q.empty()) {
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
#if DB & 1
    fprintf(stderr, "%d: %d\n", x, r);
#endif
    if (!r)
        dist[x] = -1;
    return r;
}

int Dinics()
{
    int r = 0;
    while (BFS()) {
        r += Flow(S, INT_MAX);
#if DB & 1
        fprintf(stderr, "r = %d\n", r);
#endif
    }
    return r;
}

int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    S = n + m + 1;
    T = S + 1;
    int exp = 0;
    for (int i = 1, x; i <= n; i++) {
        scanf("%d", &x);
        exp += x;
        Add(S, i, x);
        Add(i, S, 0);
    }
    for (int i = n + 1, x; i <= n + m; i++) {
        scanf("%d", &x);
        Add(i, T, x);
        Add(T, i, 0);
    }
    for (int i = 1; i <= n; i++)
        for (int j = n + 1; j <= n + m; j++) {
            Add(i, j, 1);
            Add(j, i, 0);
        }
    puts(Dinics() == exp ? "1" : "0");
}
