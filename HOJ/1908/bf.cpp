#include <stdio.h>
#include <string.h>
#include <algorithm>

struct Node {
    int cxs, s;
    Node() {}
    Node(int z) : cxs(z), s(1) {}
    bool operator<(const Node& z) const
    { return double(cxs) / s < double(z.cxs) / z.s; }
};

const int Max_n = 1003;
int n, r;
Node node[Max_n];
//int H[Max_n];
int father[Max_n];

bool vis[Max_n];

int FindMax()
{
    int x;
    for (x = 1; x <= n; x++)
        if (!vis[x] && x != r)
            break;
    if (x == n + 1)
        throw int();
    for (int i = x + 1; i <= n; i++)
        if (!vis[i] && i != r && node[x] < node[i])
            x = i;
    return x;
}

int FindFather(int x)
{
    int& f = father[x];
    while (vis[f])
        f = father[f];
    return f;
}

int Merge(int a, int b)
{
    vis[b] = true;
    const int ret = node[a].s * node[b].cxs;
    node[a].s += node[b].s;
    node[a].cxs += node[b].cxs;
    return ret;
}

int Work()
{
    int ans = 0;
    memset(vis, 0, sizeof vis);
    for (int _ = 1; _ < n; _++) {
        int x = FindMax();
#if DB & 1
        int t = FindFather(x);
        int z = Merge(t, x);
        ans += z;
        fprintf(stderr, "Merge %d, %d: %d\n", t, x, z);
#else
        ans += Merge(FindFather(x), x);
#endif
    }
    return ans += node[r].cxs;
}

int main()
{
    for (; ; ) {
        scanf("%d%d", &n, &r);
        if (!n && !r)
            return 0;
        for (int i = 1, c; i <= n; i++) {
            scanf("%d", &c);
            node[i] = Node(c);
        }
        father[r] = r;
        for (int i = 1, a, b; i < n; i++) {
            scanf("%d%d", &a, &b);
            father[b] = a;
        }
        printf("%d\n", Work());
    }
}
