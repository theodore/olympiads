#include <climits>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>

#define OP(x) ((((x) - 1) ^ 1) + 1)

const int Max_v = 2030;
const int Max_e = 10030;
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
#if DB & 1
            fprintf(stderr, "i = %d, d = %d\n", i, dist[i]);
#endif
            cap[pre[i]] -= flow[T];
            cap[OP(pre[i])] += flow[T];
        }
#if DB & 1
        fprintf(stderr, "r = %d\n", r);
#endif
    }
    return r;
}

int main()
{
    int n, m;
    int num[23][23];
    const int M = 40;
    const int OFFSET = 1000;
    S = OFFSET * 2;
    T = S + 1;
    scanf("%d%d", &m, &n);

    for (int i = 1; i <= n; i++)
        for (int j = 1; j < m + i; j++) {
            scanf("%d", &num[i][j]);
            Ins(i * M + j, i * M + j + OFFSET, 1, -num[i][j]);
        }
    for (int i = 1; i <= m; i++)
        Ins(S, M + i, 1, 0);
    for (int i = 1; i < m + n; i++)
        Ins(n * M + i + OFFSET, T, 1, 0);
    for (int i = 1; i < n; i++)
        for (int j = 1; j < m + i; j++) {
            Ins(i * M + j + OFFSET, (i + 1) * M + j, 1, 0);
            Ins(i * M + j + OFFSET, (i + 1) * M + j + 1, 1, 0);
        }

    printf("%d\n", -SSPA());

    int TT = T + 1;
    const int INF = 100000;
    memset(start, 0, sizeof start);
    edge = 0;
    /*
    for (int i = 1; i <= n; i++)
        for (int j = 1; j < m + i; j++)
            Ins(i * M + j, i * M + j + OFFSET, INF, -num[i][j]);
            */
    for (int i = 1; i <= n; i++)
        for (int j = 1; j < m + i; j++)
            Ins(i * M + j, i * M + j + OFFSET, INF, -num[i][j]);
    for (int i = 1; i <= m; i++)
        Ins(S, M + i, 1, 0);
    for (int i = 1; i < m + n; i++)
        Ins(n * M + i + OFFSET, TT, INF, 0);
    for (int i = 1; i < n; i++)
        for (int j = 1; j < m + i; j++) {
            Ins(i * M + j + OFFSET, (i + 1) * M + j, 1, 0);
            Ins(i * M + j + OFFSET, (i + 1) * M + j + 1, 1, 0);
        }
    Ins(TT, T, m, 0);
    printf("%d\n", -SSPA());

    memset(start, 0, sizeof start);
    edge = 0;
    /*
    for (int i = 1; i < n; i++)
        for (int j = 1; j < m + i; j++) {
            Ins(i * M + j + OFFSET, (i + 1) * M + j, INF, 0);
            Ins(i * M + j + OFFSET, (i + 1) * M + j + 1, INF, 0);
        }
        */

    for (int i = 1; i <= n; i++)
        for (int j = 1; j < m + i; j++)
            Ins(i * M + j, i * M + j + OFFSET, INF, -num[i][j]);
    for (int i = 1; i <= m; i++)
        Ins(S, M + i, 1, 0);
    for (int i = 1; i < m + n; i++)
        Ins(n * M + i + OFFSET, TT, INF, 0);
    for (int i = 1; i < n; i++)
        for (int j = 1; j < m + i; j++) {
            Ins(i * M + j + OFFSET, (i + 1) * M + j, INF, 0);
            Ins(i * M + j + OFFSET, (i + 1) * M + j + 1, INF, 0);
        }
    Ins(TT, T, m, 0);
    printf("%d\n", -SSPA());
}
