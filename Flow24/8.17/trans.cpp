#include <climits>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>

#define OP(x) ((((x) - 1) ^ 1) + 1)

const int Max_v = 200;
const int Max_e = 20400;
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
    int A[103];
    int B[103];
    int C[103][130];
    int n, m;
    scanf("%d%d", &n, &m);
    S = n + m + 1;
    T = S + 1;
    for (int i = 1, x; i <= n; i++) {
        scanf("%d", &x);
        A[i] = x;
        Ins(S, i, x, 0);
    }
    for (int i = n + 1, x; i <= n + m; i++) {
        scanf("%d", &x);
        B[i - n] = x;
        Ins(i, T, x, 0);
    }
    const int INF = 100000;
    for (int i = 1; i <= n; i++)
        for (int j = n + 1; j <= n + m; j++) {
            int x;
            scanf("%d", &x);
            C[i][j - n] = x;
            Ins(i, j, INF, x);
        }
    printf("%d\n", SSPA());

    memset(start, 0, sizeof start);
    edge = 0;
    for (int i = 1, x; i <= n; i++) {
        x = A[i];
        Ins(S, i, x, 0);
    }
    for (int i = n + 1, x; i <= n + m; i++) {
        x = B[i - n];
        Ins(i, T, x, 0);
    }
    for (int i = 1; i <= n; i++)
        for (int j = n + 1; j <= n + m; j++) {
            int x = C[i][j - n];
            Ins(i, j, INF, -x);
        }
    printf("%d\n", -SSPA());
}
