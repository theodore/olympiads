#include <climits>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>

#define OP(x) ((((x) - 1) ^ 1) + 1)

const int Max_v = 13 * 103;
const int Max_e = 7027;
int S, T;
int start[Max_v], to[Max_e], next[Max_e], cap[Max_e], edge;

void Add(int a, int b, int c)
{
    to[++edge] = b;
    next[edge] = start[a];
    start[a] = edge;
    cap[edge] = c;
}

void Ins(int a, int b, int c, int d = 0)
{
    Add(a, b, c);
    Add(b, a, d);
}

unsigned dist[Max_v];

bool BFS()
{
    memset(dist, -1, sizeof dist);
    dist[S] = 0;
    std::queue<int> q;
    for (q.push(S); !q.empty(); ) {
        int x = q.front();
        q.pop();
        for (int e = start[x], t; e; e = next[e])
            if (cap[e] && dist[x] + 1 < dist[t = to[e]]) {
                dist[t] = dist[x] + 1;
                if (t == T)
                    return true;
                q.push(t);
            }
    }
    return false;
}

int Flow(int x, int f)
{
    if (x == T)
        return f;
    int r = 0;
    for (int e = start[x]; e && f; e = next[e])
        if (cap[e] && dist[x] + 1 == dist[to[e]]) {
            int t = Flow(to[e], std::min(f, cap[e]));
            f -= t;
            r += t;
            cap[e] -= t;
            cap[OP(e)] += t;
        }
    if (!r)
        dist[x] = -1;
#if DB & 2
    fprintf(stderr, "%d: ret %d\n", x, r);
#endif
    return r;
}

int Dinics()
{
    int r = 0;
    while (BFS())
        r += Flow(S, INT_MAX);
    return r;
}

int main()
{
    int n, m, k;
    const int Max_n = 17;
    const int Max_m = 23;
    static int size[Max_m], period[Max_m], stop[Max_m][Max_n];
    scanf("%d%d%d", &n, &m, &k);
    S = 13 * 101;
    T = S + 1;
    for (int i = 0; i < m; i++) {
        scanf("%d%d", &size[i], &period[i]);
        for (int j = 0; j < period[i]; j++)
            scanf("%d", &stop[i][j]);
    }
    for (int day = 1, flow = 0; day <= 100; day++) {
        for (int i = 1; i <= n; i++)
            Ins(i + 13 * (day - 1), i + 13 * day, INT_MAX / 100);
        for (int i = 0; i < m; i++) {
            int x = stop[i][(day - 1) % period[i]];
            int y = stop[i][day % period[i]];
            switch (x) {
                case 0: x = S; break;
                case -1: x = T; break;
                default: x += 13 * (day - 1); break;
            }
            switch (y) {
                case 0: y = S; break;
                case -1: y = T; break;
                default: y += 13 * day; break;
            }
            Ins(x, y, size[i]);
        }
        if ((flow += Dinics()) >= k) {
            printf("%d\n", day);
            return 0;
        }
#if DB & 1
        fprintf(stderr, "day %d: flow %d\n", day, flow);
#endif
    }
    puts("0");
}
