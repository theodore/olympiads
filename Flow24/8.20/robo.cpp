#include <climits>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>

#define OP(x) ((((x) - 1) ^ 1) + 1)

const int Max_v = 400;
const int Max_e = 3300;
int S, T;
int start[Max_v], to[Max_e], next[Max_e], cap[Max_e], fee[Max_e], edge;

void Add(int a, int b, int c, int d)
{
    to[++edge] = b;
    next[edge] = start[a];
    start[a] = edge;
    cap[edge] = c;
    fee[edge] = d;
}

void Ins(int a, int b, int c, int d)
{
    Add(a, b, c, d);
    Add(b, a, 0, -d);
}

int dist[Max_v], flow[Max_v], pre[Max_v];

bool SPFA()
{
    static bool in[Max_v];
    memset(dist, 0x3f, sizeof dist);
    dist[S] = 0;
    flow[S] = INT_MAX;
    std::queue<int> q;
    for (q.push(S); !q.empty(); ) {
        int x = q.front();
        q.pop();
        in[x] = false;
        for (int e = start[x], t; e; e = next[e])
            if (cap[e] && dist[x] + fee[e] < dist[t = to[e]]) {
                dist[t] = dist[x] + fee[e];
                flow[t] = std::min(flow[x], cap[e]);
                pre[t] = e;
                if (!in[t]) {
                    in[t] = true;
                    q.push(t);
                }
            }
    }
    return dist[T] != 0x3f3f3f3f;
}

int SSPA()
{
    int r = 0;
    while (SPFA()) {
        r += flow[T] * dist[T];
        for (int i = T; i != S; i = to[OP(pre[i])]) {
            cap[pre[i]] -= flow[T];
            cap[OP(pre[i])] += flow[T];
        }
    }
    return r;
}

int main()
{
    int n, m, p, q;
    scanf("%d%d%d%d", &n, &m, &p, &q);
    S = (p + 1) * (q + 1);
    T = S + 1;
    const int INF = 123452;
    for (int i = 0; i <= p; i++)
        for (int j = 0, x; j < q; j++) {
            scanf("%d", &x);
            Ins(i * (q + 1) + j, i * (q + 1) + j + 1, 1, -x);
            Ins(i * (q + 1) + j, i * (q + 1) + j + 1, INF, 0);
        }
    for (int j = 0; j <= q; j++)
        for (int i = 0, x; i < p; i++) {
            scanf("%d", &x);
            Ins(i * (q + 1) + j, (i + 1) * (q + 1) + j, 1, -x);
            Ins(i * (q + 1) + j, (i + 1) * (q + 1) + j, INF, 0);
        }
    for (int i = 0, a, x, y; i < n; i++) {
        scanf("%d%d%d", &a, &x, &y);
        Ins(S, x * (q + 1) + y, a, 0);
    }
    for (int i = 0, a, x, y; i < m; i++) {
        scanf("%d%d%d", &a, &x, &y);
        Ins(x * (q + 1) + y, T, a, 0);
    }
    printf("%d\n", -SSPA());
}
