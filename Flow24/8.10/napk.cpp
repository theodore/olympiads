#include <climits>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>

#define OP(x) ((((x) - 1) ^ 1) + 1)

const int Max_v = 2000;
const int Max_e = 24000;
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
                pre[t] = e;
                dist[t] = dist[x] + fee[e];
                flow[t] = std::min(flow[x], cap[e]);
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
    int n, buy, time0, fee0, time1, fee1;
    scanf("%d%d%d%d%d%d", &n, &buy, &time0, &fee0, &time1, &fee1);
    S = n + n + 1;
    T = S + 1;
    for (int i = 1, x, INF = INT_MAX / 20; i <= n; i++) {
        scanf("%d", &x);
        Ins(S, i, x, 0);
        Ins(i + n, T, x, 0);
        Ins(S, i + n, INF, buy);
        if (i < n)
            Ins(i, i + 1, INF, 0);
        if (i + time0 <= n)
            Ins(i, i + time0 + n, INF, fee0);
        if (i + time1 <= n)
            Ins(i, i + time1 + n, INF, fee1);
    }
    printf("%d\n", SSPA());
}
