#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>

#define OP(x) ((((x) - 1) ^ 1) + 1)

const int maxn = 1603;
const int maxm = 36407;
int n, m;
int S, T;
int start[maxn], to[maxm], next[maxm], cap[maxm], cost[maxm], edge;

void Add(int a, int b, int c, int d)
{
    to[++edge] = b;
    next[edge] = start[a];
    start[a] = edge;
    cap[edge] = c;
    cost[edge] = d;
}

void Init()
{
    scanf("%d%d", &n, &m);
    S = n + n + 1;
    T = n + n + 2;
    for (int i = 1, x; i <= n; ++i) {
        scanf("%d", &x);
        Add(S, i, 1, x);
        Add(i, S, 0, -x);
        /*
        Add(i, i + n, n, 0);
        Add(i + n, i, 0, 0);
        */
        Add(i, T, 1, 0);
        Add(T, i, 0, 0);
        Add(S, i + n, 1, 0);
        Add(i + n, S, 0, 0);
    }
    for (int a, b, c; m--; ) {
        scanf("%d%d%d", &a, &b, &c);
        if (a > b)
            std::swap(a, b);
        Add(a + n, b, n, c);
        Add(b, a + n, 0, -c);
    }
}

int dist[maxn], flow[maxn];
int pre[maxn];

bool SPFA()
{
    std::queue<int> q;
    static bool in[maxn];
    memset(dist, 0x3f, sizeof dist);
    flow[S] = dist[0];
    dist[S] = 0;
    q.push(S);
    while (!q.empty()) {
        int x = q.front();
        q.pop();
        in[x] = false;
        for (int e = start[x]; e; e = next[e])
            if (cap[e] && dist[x] + cost[e] < dist[to[e]]) {
                dist[to[e]] = dist[x] + cost[e];
                flow[to[e]] = std::min(flow[x], cap[e]);
                pre[to[e]] = e;
                if (!in[to[e]]) {
                    in[to[e]] = true;
                    q.push(to[e]);
                }
            }
    }
    return dist[T] != 0x3f3f3f3f;
}

int Flow()
{
    int ret = 0;
    while (SPFA()) {
        ret += flow[T] * dist[T];
        for (int i = T; i != S; i = to[OP(pre[i])]) {
#if DB & 1
            fprintf(stderr, "%d <- ", i);
#endif
            cap[pre[i]] -= flow[T];
            cap[OP(pre[i])] += flow[T];
        }
#if DB & 1
        fprintf(stderr, "0\n");
#endif
    }
    return ret;
}

int main()
{
    Init();
    printf("%d\n", Flow());
}
