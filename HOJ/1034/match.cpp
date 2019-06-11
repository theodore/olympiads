#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <queue>

#define OP(x) ((((x) - 1) ^ 1) + 1)
#define LT(x) (1 * n + (x))
#define EQ(x) (2 * n + (x))
#define GT(x) (3 * n + (x))
#define ED(x) (4 * n + (x))

const int maxn = 500013;
const int maxm = 2000013;
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

void LinkToSink(int x, int c)
{
    Add(LT(x), ED(x), c, 0);
    Add(ED(x), LT(x), 0, 0);

    Add(EQ(x), ED(x), c, 0);
    Add(ED(x), EQ(x), 0, 0);

    Add(GT(x), ED(x), c, 0);
    Add(ED(x), GT(x), 0, 0);

    Add(ED(x), T, c, 0);
    Add(T, ED(x), 0, 0);
}

void MkGraph()
{
    std::sort(mine, mine + n);
    std::sort(yours, yours + n);
    S = n * 5;
    T = S + 1;

    // Any advice? This piece of code isn't so neat.
    int c = 0, p = -1, first = -1;
    static int prev[maxn], succ[maxn];
    for (int i = 0; i < n; ++i) {
        Add(S, i, 1, 0);
        Add(i, S, 0, 0);
        if (i && yours[i] != yours[i - 1]) {
            LinkToSink(i - 1, c);
            prev[i - 1] = p;
            if (p != -1)
                succ[p] = i - 1;
            else
                first = i - 1;
            p = i - 1;
            c = 0;
        }
        ++c;
    }
    LinkToSink(n - 1, c);
    prev[n - 1] = p;
    if (p != -1)
        succ[p] = n - 1;
    else
        first = n - 1;
    succ[n - 1] = -1;

    for (int i = first; i != -1; i = succ[i]) {
        int t = prev[i];
        if (t != -1) {
            t = LT(t);
            Add(LT(i), t, maxn, 0);
            Add(t, LT(i), 0, 0);
        }
        t = succ[i];
        if (t != -1) {
            t = GT(t);
            Add(GT(i), t, maxn, 0);
            Add(t, GT(i), 0, 0);
        }
    }

    for (int i = 0, j = first; i < n; ++i) {
        while (j != -1 && yours[j] < mine[i])
            j = succ[j];
        if (j == -1) {
            p = n - 1;
        } else {
            int s;
            if (yours[j] == mine[i]) {
                Add(i, EQ(j), 1, 1);
                Add(EQ(j), i, 0, -1);
                s = succ[j];
            } else {
                s = j;
            }
            if (s != -1) {
                Add(i, GT(s), 1, 0);
                Add(GT(s), i, 0, 0);
            }
            p = prev[j];
        }
        if (p != -1) {
            Add(i, LT(p), 1, 2);
            Add(LT(p), i, 0, -2);
        }
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
        fprintf(stderr, "dist[%d] = %d\n", x, dist[x]);
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

int SSPA() // Successive Shortest Path Algorithm
{
#if DB & 1
    fprintf(stderr, "SSPA\n");
#endif
    int ret = 0;
    while (SPFA()) {
#if DB & 1
        fprintf(stderr, "dist %d, flow %d\n", dist[T], flow[T]);
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
    int ans = SSPA();
    AdaptGraph();
    printf("%d %d\n", abs(SSPA()), ans);
}
