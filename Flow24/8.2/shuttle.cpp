#include <climits>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <vector>

#define OP(x) ((((x) - 1) ^ 1) + 1)

const int Max_v = 200;
const int Max_e = 50000;
const int INF = INT_MAX / 4;
int n, m, S, T;
int start[Max_v], to[Max_e], next[Max_e], cap[Max_e], edge;

void Add(int a, int b, int c)
{
    to[++edge] = b;
    next[edge] = start[a];
    start[a] = edge;
    cap[edge] = c;
}

int dist[Max_v];

bool MarkUp()
{
    memset(dist, 0x3f, sizeof dist);
    std::queue<int> q;
    q.push(S);
    dist[S] = 0;
    while (!q.empty()) {
        int x = q.front();
        q.pop();
        for (int e = start[x]; e; e = next[e])
            if (cap[e] && dist[x] + 1 < dist[to[e]]) {
                dist[to[e]] = dist[x] + 1;
                if (to[e] == T)
                    return true;
                q.push(to[e]);
            }
    }
    return false;
}

int Flow(int x, int f)
{
    if (x == T)
        return f;
    int r = 0;
    for (int e = start[x]; e; e = next[e])
        if (cap[e] && dist[x] + 1 == dist[to[e]]) {
            int t = Flow(to[e], std::min(f, cap[e]));
            f -= t;
            r += t;
            cap[e] -= t;
            cap[OP(e)] += t;
        }
    if (!r)
        dist[x] = -1;
    return r;
}

int Dinic()
{
    int r = 0;
    while (MarkUp())
        r += Flow(S, INF);
    return r;
}

std::vector<int> exp, equip;

void Fill(int x)
{
    static bool vis[Max_v];
    vis[x] = true;
    for (int e = start[x], t; e; e = next[e])
        if (cap[e] && !vis[t = to[e]]) {
            if (t <= n)
                exp.push_back(t);
            else
                equip.push_back(t - n);
            Fill(t);
        }
}

void Output()
{
    Fill(S);
    std::sort(exp.begin(), exp.end());
    std::sort(equip.begin(), equip.end());
    typedef std::vector<int>::iterator Viter;
    for (Viter i = exp.begin(); i != exp.end(); i++)
        printf("%d ", *i);
    puts("");
    for (Viter i = equip.begin(); i != equip.end(); i++)
        printf("%d ", *i);
    puts("");
}

int main()
{
    scanf("%d%d", &n, &m);
    S = n + m + 1;
    T = S + 1;
    int ans = 0;
    for (int i = 1, x; i <= n; i++) {
        scanf("%d", &x);
        ans += x;
        Add(S, i, x);
        Add(i, S, 0);
        int c;
        while ((c = getchar()) != '\n') {
            scanf("%d", &x);
            Add(i, x + n, INF);
            Add(x + n, i, 0);
        }
    }
    for (int i = 1 + n, x; i <= m + n; i++) {
        scanf("%d", &x);
        Add(i, T, x);
        Add(T, i, 0);
    }
    ans -= Dinic();
    //Output();
    printf("%d\n", ans);
}
