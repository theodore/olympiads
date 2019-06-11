#include <climits>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>

#define OP(x) ((((x) - 1) ^ 1) + 1)

const int Max_n = 1000000;
const int Max_m = Max_n;
int S, T;
int start[Max_n], to[Max_m], next[Max_m], cap[Max_m], edge;

bool IsSqr(int x)
{
    int z = sqrt(x);
    return z * z == x;
}

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
    for (int e = start[x]; e; e = next[e])
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
    while (BFS()) {
        r += Flow(S, INT_MAX);
#if DB & 1
        fprintf(stderr, "r = %d\n", r);
#endif
    }
    return r;
}

int Check(int n)
{
#if DB & 1
    fprintf(stderr, "checking %d\n", n);
#endif
    S = n + n + 1;
    T = S + 1;
    memset(start, 0, sizeof start);
    edge = 0;
    for (int i = 1; i <= n; i++) {
        Add(S, i + n, 1);
        Add(i + n, S, 0);
        Add(i, T, 1);
        Add(T, i, 0);
    }
    for (int i = 1; i <= n; i++)
        for (int j = i + 1; j <= n; j++)
            if (IsSqr(i + j)) {
                Add(i + n, j, 1);
                Add(j, i + n, 0);
            }
    return n - Dinics();
}

int main()
{
    int p;
    scanf("%d", &p);
    int l = 1, r = Max_n / 100;
    for (int m = (l + r) / 2; r - l > 1; m = (l + r) / 2)
        (Check(m) <= p ? l : r) = m;
    printf("%d\n", l);
}
