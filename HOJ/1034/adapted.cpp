#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <queue>

#define OP(x) ((((x) - 1) ^ 1) + 1)

const int maxn = 100003;
const int maxm = maxn;
int n, S, T;
int mine[maxn], yours[maxn];
int start[maxn], to[maxm], next[maxm], cap[maxm], fee[maxm], edge;

void Add(int a, int b, int c, int d)
{
    to[++edge] = b;
    next[edge] = start[a];
    start[a] = edge;
    cap[edge] = c;
    fee[edge] = d;
}

void MkGraph()
{
    S = n * 2;
    T = S + 1;
    for (int i = 0; i < n; ++i) {
        Add(S, i, 1, 0);
        Add(i, S, 0, 0);
        Add(i + n, T, 1, 0);
        Add(T, i + n, 0, 0);
    }
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            if (mine[i] > yours[j]) {
                Add(i, n + j, 1, 2);
                Add(n + j, i, 0, -2);
            } else if (mine[i] == yours[j]) {
                Add(i, n + j, 1, 1);
                Add(n + j, i, 0, -1);
            } else {
                Add(i, n + j, 1, 0);
                Add(n + j, i, 0, 0);
            }
}

void AdaptGraph()
{
    for (int i = 1; i <= edge; i += 2) {
        cap[i] += cap[i + 1];
        cap[i + 1] = 0;
        fee[i] = -fee[i];
        fee[i + 1] = -fee[i + 1];
    }
}

int dist[maxn], flow[maxn];
bool in[maxn];
int pre[maxn];

bool SPFA()
{
    memset(dist, 0x3f, sizeof dist);
    flow[S] = dist[0];
    dist[S] = 0;
    std::queue<int> q;
    q.push(S);
    while (!q.empty()) {
        int x = q.front();
        q.pop();
        in[x] = false;
#if DB & 1
        fprintf(stderr, "x = %d, dist = %d\n", x, dist[x]);
#endif
        for (int e = start[x]; e; e = next[e])
            if (cap[e] && dist[x] + fee[e] < dist[to[e]]) {
                dist[to[e]] = dist[x] + fee[e];
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

int CostFlow()
{
#if DB & 1
    fprintf(stderr, "Flow\n");
#endif
    int ret = 0;
    while (SPFA()) {
#if DB & 1
        fprintf(stderr, "flow[T] = %d\n", flow[T]);
#endif
        ret += dist[T] * flow[T];
        for (int x = T; x != S; x = to[OP(pre[x])]) {
            cap[pre[x]] -= flow[T];
            cap[OP(pre[x])] += flow[T];
        }
    }
    return ret;
}

int main()
{
    scanf("%d", &n);
    for (int i = 0; i < n; ++i)
        scanf("%d", &mine[i]);
    for (int i = 0; i < n; ++i)
        scanf("%d", &yours[i]);
    MkGraph();
    int ans = CostFlow();
    AdaptGraph();
    printf("%d %d\n", abs(CostFlow()), ans);
}
