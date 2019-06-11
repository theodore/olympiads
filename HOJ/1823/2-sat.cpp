#include <cstdio>
#include <cstring>
#include <algorithm>
#include <stack>

#define UPN(a, b) a = std::min(a, b)

const int maxn = 203;
const int maxm = 2003;
int n, m;
int start[maxn], to[maxm], next[maxm], edge;

void Add(int a, int b)
{
    to[++edge] = b;
    next[edge] = start[a];
    start[a] = edge;
}

void Init()
{
    scanf("%d%d", &n, &m);
    edge = 0;
    memset(start + 1, 0, sizeof (int) * 2 * n);
    char c0, c1;
    int n0, n1;
    while (m--) {
        scanf("\n%c%d %c%d", &c0, &n0, &c1, &n1);
        bool b0 = c0 == 'h', b1 = c1 == 'h';
        Add(n0 + !b0 * n, n1 + b1 * n);
        Add(n1 + !b1 * n, n0 + b0 * n);
    }
}

int time;
int color[maxn];
int low[maxn], dfn[maxn];
std::stack<int> S;
bool in[maxn];

int Tarjan(int x)
{
    color[x] = low[x] = dfn[x] = ++time;
    in[x] = true;
    S.push(x);
    for (int e = start[x]; e; e = next[e])
        if (!dfn[to[e]])
            UPN(low[x], Tarjan(to[e]));
        else if (in[to[e]])
            UPN(low[x], dfn[to[e]]);
    if (dfn[x] == low[x]) {
        int t;
        do {
            t = S.top();
            S.pop();
            in[t] = false;
            color[t] = color[x];
        } while (t != x);
    }
    return low[x];
}

bool Solve()
{
    time = 0;
    memset(dfn + 1, 0, sizeof (int) * 2 * n);
    for (int i = 1; i <= 2 * n; ++i)
        if (!dfn[i])
            Tarjan(i);
    for (int i = 1; i <= n; ++i)
        if (color[i] == color[i + n])
            return false;
    return true;
}

int main()
{
    int _;
    for (scanf("%d", &_); _--; ) {
        Init();
        puts(Solve() ? "GOOD" : "BAD");
    }
}
