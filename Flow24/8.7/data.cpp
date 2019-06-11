#include <climits>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>

#define OP(x) ((((x) - 1) ^ 1) + 1)

const int Max_v = 2000;
const int Max_e = 200000;
int S, T;
int start[Max_v], to[Max_e], next[Max_e], cap[Max_e], edge;

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

bool MarkUp()
{
    memset(dist, -1, sizeof dist);
    std::queue<int> q;
    dist[S] = 0;
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
    while (MarkUp())
        r += Flow(S, INT_MAX);
    return r;
}

int main()
{
    int n, m;
    scanf("%d%d", &m, &n);
    S = n + m + 1;
    T = S + 1;
    int exp = 0;
    for (int i = 1, x; i <= m; i++) {
        scanf("%d", &x);
        exp += x;
        Ins(i + n, T, x);
    }
    for (int i = 1, c, x; i <= n; i++) {
        Ins(S, i, 1);
        for (scanf("%d", &c); c--; ) {
            scanf("%d", &x);
            Ins(i, n + x, 1);
        }
    }
    puts(Dinics() == exp ? "Yes" : "No");
}
