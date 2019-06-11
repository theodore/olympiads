#include <cstdio>
#include <cstring>
#include <queue>

#define OP(x) ((((x) - 1) ^ 1) + 1)

const int maxn = 1007;
const int maxm = 20007;
const int inf = ~0u >> 1;
int n, m, k;
int start[maxn], to[maxm], next[maxm], cap[maxm], cost[maxm], edge;

void add(int a, int b, int c, int d)
{
    to[++edge] = b;
    next[edge] = start[a];
    start[a] = edge;
    cap[edge] = c;
    cost[edge] = d;
}

int dist[maxn];

bool markup()
{
    std::queue<int> q;
    memset(dist, 0x3f, sizeof dist);
    dist[1] = 0;
    q.push(1);
    while (!q.empty()) {
        const int x = q.front();
        q.pop();
        for (int e = start[x]; e; e = next[e])
            if (cap[e] && !cost[e] && dist[x] + 1 < dist[to[e]]) {
                dist[to[e]] = dist[x] + 1;
                if (to[e] == n)
                    return true;
                q.push(to[e]);
            }
    }
    return false;
}

int flow(int x, int f)
{
    if (x == n)
        return f;
    int r = 0;
    for (int e = start[x]; e && f; e = next[e])
        if (cap[e] && !cost[e] && dist[x] + 1 == dist[to[e]]) {
            int t = flow(to[e], std::min(cap[e], f));
            if (t == 0) {
                dist[to[e]] = -1;
                continue;
            }
            f -= t;
            r += t;
            cap[e] -= t;
            cap[OP(e)] += t;
        }
    return r;
}

int Dinics()
{
    int r = 0;
    while (markup())
        r += flow(1, inf);
    return r;
}

int pre[maxn];
int left[maxn];

bool SPFA()
{
    std::queue<int> q;
    static bool in[maxn];
    memset(dist, 0x3f, sizeof dist);
    dist[1] = 0;
    left[1] = inf;
    q.push(1);
    while (!q.empty()) {
        const int x = q.front();
        q.pop();
        in[x] = false;
        for (int e = start[x]; e; e = next[e])
            if (cap[e] && dist[x] + cost[e] < dist[to[e]]) {
                dist[to[e]] = dist[x] + cost[e];
                pre[to[e]] = e;
                left[to[e]] = std::min(left[x], cap[e]);
                if (!in[to[e]]) {
                    in[to[e]] = true;
                    q.push(to[e]);
                }
            }
    }
    return dist[n] != 0x3f3f3f3f;
}

int augment()
{
    for (int i = n; i != 1; i = to[OP(pre[i])]) {
        cap[pre[i]] -= left[n];
        cap[OP(pre[i])] += left[n];
    }
    return left[n] * dist[n];
}

int SSPA() // Successive Shortest Path Algorithm
{
    int r = 0;
    while (SPFA())
        r += augment();
    return r;
}

int main()
{
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 0, a, b, c, d; i < m; ++i) {
        scanf("%d%d%d%d", &a, &b, &c, &d);
        add(a, b, c, 0);
        add(b, a, 0, 0);
        add(a, b, k, d);
        add(b, a, 0, -d);
    }
    printf("%d ", Dinics());
    add(n, n + 1, k, 0);
    add(n + 1, n, 0, 0);
    ++n;
    printf("%d\n", SSPA());
}
