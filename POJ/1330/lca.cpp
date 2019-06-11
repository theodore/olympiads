#include <stdio.h>
#include <string.h>
#include <algorithm>

const int Max_n = 10033;
const int Max_m = 20033;
const int Max_log = 14;
int n;
int start[Max_n], to[Max_m], next[Max_m], edge;

void Add(int a, int b)
{
    to[++edge] = b;
    next[edge] = start[a];
    start[a] = edge;
}

int depth[Max_n], anc[Max_n][Max_log];

void DFS(int x, int d, int f)
{
    depth[x] = d;
    for (int e = start[x], t; e; e = next[e])
        if ((t = to[e]) != f) {
            anc[t][0] = x;
            for (int i = 1; i < Max_log; i++)
                anc[t][i] = anc[anc[t][i - 1]][i - 1];
            DFS(t, d + 1, x);
        }
}

void Init()
{
    scanf("%d", &n);
    static int father[Max_n];
    memset(father, 0, sizeof father);
    memset(start, 0, sizeof start);
    edge = 0;
    for (int i = 1, a, b; i < n; i++) {
        scanf("%d%d", &a, &b);
        Add(a, b);
        Add(b, a);
        father[b] = a;
    }
    int root = 1;
    while (father[root])
        root = father[root];
    for (int i = 0; i < Max_log; i++)
        anc[root][i] = root;
    DFS(root, 0, 0);
}

int GoUp(int x, int d)
{
    for (int i = 0; i < Max_log; i++)
        if ((1 << i) & d)
            x = anc[x][i];
    return x;
}

int LCA(int a, int b)
{
    if (depth[a] < depth[b])
        std::swap(a, b);
    a = GoUp(a, depth[a] - depth[b]);
    if (a == b)
        return a;
    for (int i = Max_log - 1; i >= 0; i--)
        if (anc[a][i] != anc[b][i])
            a = anc[a][i], b = anc[b][i];
    return anc[a][0];
}

int main()
{
    int _;
    for (scanf("%d", &_); _--; ) {
        Init();
        int a, b;
        scanf("%d%d", &a, &b);
        printf("%d\n", LCA(a, b));
    }
}
