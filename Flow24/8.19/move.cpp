#include <climits>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>

#define OP(x) ((((x) - 1) ^ 1) + 1)

const int Max_v = 120;
const int Max_e = 830;
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
#if DB & 1
        fprintf(stderr, "r = %d %d\n", r, flow[T]);
#endif
    }
    return r;
}

int main()
{
    int n;
    scanf("%d", &n);
    S = n + 1;
    T = S + 1;
    int s = 0;
    for (int i = 1, x; i <= n; i++) {
        scanf("%d", &x);
        s += x;
        Ins(S, i, x, 0);
    }
    s /= n;
    const int INF = 100000;
    for (int i = 1; i < n; i++)
        Ins(i, i + 1, INF, 1);
    for (int i = 2; i <= n; i++)
        Ins(i, i - 1, INF, 1);
    for (int i = 1; i <= n; i++)
        Ins(i, T, s, 0);
    Ins(1, n, INF, 1);
    Ins(n, 1, INF, 1);
    printf("%d\n", SSPA());
}
