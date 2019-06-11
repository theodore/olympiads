#include <climits>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>

#define OP(x) ((((x) - 1) ^ 1) + 1)

const int max_n = 111;
const int max_h = 1003;
const int max_m = 200111;
int start[max_n], to[max_m], next[max_m], cap[max_m], edge;
int n, m, S, T;

void Add(int a, int b, int c)
{
    to[++edge] = b;
    next[edge] = start[a];
    start[a] = edge;
    cap[edge] = c;
}

void MkGraph()
{
    static int pre[max_h];
    static int pig[max_h];
    const int inf = INT_MAX / 4;
    scanf("%d%d", &m, &n);
    S = 0;
    T = n + 1;
    for (int i = 1; i <= m; i++)
        scanf("%d", &pig[i]);
    for (int i = 1; i <= n; i++) {
        int a, x;
        for (scanf("%d", &a); a--; ) {
            scanf("%d", &x);
            Add(pre[x], i, pig[x]);
            Add(i, pre[x], 0);
            pig[x] = inf;
            pre[x] = i;
        }
        scanf("%d", &x);
        Add(i, T, x);
        Add(T, i, 0);
    }
}

int dist[max_n];
bool in[max_n];

bool MarkUp()
{
    memset(dist, 0x3f, sizeof dist);
    dist[S] = 0;
    std::queue<int> q;
    q.push(S);
    while (!q.empty()) {
        int x = q.front();
        q.pop();
        in[x] = false;
        for (int e = start[x], t; e; e = next[e])
            if (cap[e] && (t = dist[x] + 1) < dist[to[e]]) {
                dist[to[e]] = t;
                if (to[e] == T)
                    break;
                if (!in[to[e]]) {
                    in[to[e]] = true;
                    q.push(to[e]);
                }
            }
    }
    return dist[T] != 0x3f3f3f3f;
}

int flow(int x, int f)
{
    if (x == T)
        return f;
    int r = 0;
    for (int e = start[x]; e && f; e = next[e])
        if (cap[e] && dist[x] + 1 == dist[to[e]]) {
            int t = flow(to[e], std::min(f, cap[e]));
            if (t) {
                r += t;
                f -= t;
                cap[e] -= t;
                cap[OP(e)] += t;
            } else {
                dist[to[e]] = INT_MAX / 2;
            }
        }
    return r;
}

int Dinic()
{
    const int inf = INT_MAX / 2;
    int r = 0;
    while (MarkUp())
        r += flow(S, inf);
    return r;
}

int main()
{
    MkGraph();
    printf("%d\n", Dinic());
}
