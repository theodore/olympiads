#include <climits>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>

#define OP(x) ((((x) - 1) ^ 1) + 1)

const int Max_v = 1030;
const int Max_e = 3333;
const int Max_n = 533;
int S, T;
int start[Max_v], to[Max_e], next[Max_e], cap[Max_e], fee[Max_e], edge;

void Add(int a, int b, int c, int d)
{
    to[++edge] = b;
    next[edge] = start[a];
    start[a] = edge;
    cap[edge] = c;
    fee[edge] = d;
#if DB & 2
    if (edge == 77 || edge == 81 || edge == 83 || edge == 95)
        fprintf(stderr, "%d -> %d (%d, %d)\n", a, b, c, d);
#endif
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

struct Itvl { int l, r, v; };
struct SortMe {
    int v, x;
    bool operator<(const SortMe& z) const { return v < z.v; }
};

int main()
{
    int n, k;
    scanf("%d%d", &n, &k);
    S = n + n;
    T = S + 1;

    static Itvl itvl[Max_n];
    static SortMe tmp[Max_n * 2];
    for (int i = 0; i < n; i++) {
        scanf("%d%d", &itvl[i].l, &itvl[i].r);
        if (itvl[i].r < itvl[i].l)
            std::swap(itvl[i].l, itvl[i].r);
        itvl[i].v = itvl[i].r - itvl[i].l;
        tmp[i * 2].v = itvl[i].l;
        tmp[i * 2].x = i * 2;
        tmp[i * 2 + 1].v = itvl[i].r;
        tmp[i * 2 + 1].x = i * 2 + 1;
    }
    std::sort(tmp, tmp + n + n);

    int c = 0;
    for (int i = 0; i < n + n; i++)
        (tmp[i].x & 1 ? itvl[tmp[i].x / 2].r : itvl[tmp[i].x / 2].l) = c
            += (i && tmp[i].v != tmp[i - 1].v);

    const int INF = 3212135;
    Ins(S, 0, k, 0);
    for (int i = 0; i < c; i++)
        Ins(i, i + 1, INF, 0);
    Ins(c, T, k, 0);
    for (int i = 0; i < n; i++)
        Ins(itvl[i].l, itvl[i].r, 1, -itvl[i].v);

    printf("%d\n", -SSPA());

#if DB & 1
    for (int i = 1; i <= edge; i += 2)
        if (cap[i] == 0 && fee[i])
            fprintf(stderr, "%d\n", i);
#endif
}
