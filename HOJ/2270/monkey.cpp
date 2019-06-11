#include <climits>
#include <cstdio>
#include <cstring>
#include <queue>

const int Max_v = 21;
const int Max_e = Max_v * Max_v;
const int Max_s = 1 << Max_v;
int n;
unsigned dist[Max_s];
int to[Max_v];

void Reset()
{
    memset(to, 0, sizeof to);
}

void Add(int a, int b)
{
    to[a] |= 1 << b;
    to[b] |= 1 << a;
}

int from[Max_s], pre[Max_s];

bool SPFA()
{
    memset(dist, -1, sizeof dist[0] * (1 << n));
    dist[(1 << n) - 1] = 0;
    pre[(1 << n) - 1] = -1;
    static bool in[Max_s];
    std::queue<int> q;
    q.push((1 << n) - 1);
    while (!q.empty()) {
        int s = q.front();
        q.pop();
        in[s] = false;
        for (int i = 0; i < n; i++) {
            int ns = 0;
            for (int b = 0; b < n; b++)
                if (b != i && (s & (1 << b)))
                    ns |= to[b];
            if (dist[s] + 1 < dist[ns]) {
                dist[ns] = dist[s] + 1;
                from[ns] = s;
                pre[ns] = i;
#if DB & 1
                fprintf(stderr, "dist[%#x] <- %d\n", ns, dist[s] + 1);
                fprintf(stderr, " from %#x, pre %d\n", s, i);
#endif
                if (!in[ns]) {
                    in[ns] = true;
                    q.push(ns);
                }
            }
        }
    }
    return dist[0] != UINT_MAX;
}

void Output(int x)
{
    if (pre[x] == -1)
        return;
    Output(from[x]);
    printf(" %d", pre[x]);
}

void Output()
{
    printf("%d:", dist[0]);
    Output(0);
    puts("");
}

int main()
{
    for (int m; ; ) {
        scanf("%d%d", &n, &m);
        Reset();
        if (!n && !m)
            return 0;
        for (int a, b; m--; ) {
            scanf("%d%d", &a, &b);
            Add(a, b);
            Add(b, a);
        }
        if (SPFA())
            Output();
        else
            puts("Impossible");
    }
}
