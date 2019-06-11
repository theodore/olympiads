#include <climits>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>

#define UPX(a, b) a = std::max(a, b)

#define OP(x) ((((x) - 1) ^ 1) + 1)

const int Max_v = 1000;
const int Max_e = 550000;
int n, S, T;
int X[Max_v];
int f[Max_v];
int start[Max_v], next[Max_e], to[Max_e], cap[Max_e], edge;

void Add(int a, int b, int c)
{
    to[++edge] = b;
    next[edge] = start[a];
    start[a] = edge;
    cap[edge] = c;
}

void Ins(int a, int b, int c)
{
    Add(a, b, c);
    Add(b, a, 0);
}

unsigned dist[Max_v];

bool BFS()
{
    std::queue<int> q;
    memset(dist, -1, sizeof dist);
    dist[S] = 0;
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

int Flow(int x, int fl)
{
    if (x == T)
        return fl;
    int r = 0;
    for (int e = start[x]; e && fl; e = next[e])
        if (cap[e] && dist[x] + 1 == dist[to[e]]) {
            int t = Flow(to[e], std::min(fl, cap[e]));
            fl -= t;
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
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &X[i]);
    X[n + 1] = INT_MAX;

    for (int i = 1; i <= n + 1; i++) {
        for (int j = 1; j < i; j++)
            if (X[j] <= X[i])
                UPX(f[i], f[j]);
        f[i]++;
    }
    int ans;
    printf("%d\n", ans = f[n + 1] - 1);

    S = n + n + 1;
    T = S + 1;
    const int INF = INT_MAX / 1000;
    for (int i = 1; i <= n; i++) {
        Ins(i, i + n, 1);
        if (f[i] == 1)
            Ins(S, i, i == 1 ? INF : 1);
        if (f[i] == ans)
            Ins(i + n, T, i == n ? INF : 1);
        for (int j = i + 1; j <= n; j++)
            if (X[i] <= X[j] && f[i] + 1 == f[j])
                Ins(i + n, j, 1);
    }

    int t;
    printf("%d\n", t = Dinics());

    Ins(1, 1 + n, INF);
    Ins(n, n + n, INF);

    printf("%d\n", t + Dinics());
}
