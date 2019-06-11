#include <stdio.h>
#include <string.h>
#include <algorithm>

struct Node {
    int id;
    int cxs, s;
    Node() {}
    Node(int i, int z) : id(i), cxs(z), s(1) {}
    bool operator<(const Node& z) const
    { return double(cxs) / s < double(z.cxs) / z.s; }
};

const int Max_n = 1003;
int n, root;
Node node[Max_n];
int father[Max_n];
bool vis[Max_n];

int H[Max_n], Hsize;
int pos_in_H[Max_n];

struct CMP {
    bool operator()(int a, int b) const
    { return node[a] < node[b]; }
};

void HeapInit()
{
    for (int i = 1; i <= n; i++)
        H[i] = i;
    std::swap(H[root], H[n]);
    std::make_heap(H + 1, H + n, CMP());
    Hsize = n - 1;
    for (int i = 1; i < n; i++)
        pos_in_H[node[H[i]].id] = i;
}

void HeapPop()
{
    std::swap(H[1], H[Hsize--]);
    pos_in_H[node[H[1]].id] = 1;
    for (int p = 1, next; (next = p << 1) <= Hsize; p = next) {
        if (next < Hsize && node[H[next]] < node[H[next + 1]])
            next++;
        if (node[H[next]] < node[H[p]])
            break;
        std::swap(H[p], H[next]);
        std::swap(pos_in_H[node[H[p]].id], pos_in_H[node[H[next]].id]);
    }
}

int FindMax()
{
    int x = H[1];
    HeapPop();
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
    if (a != root)
        for (int p = pos_in_H[a]; p != 1 && node[H[p >> 1]] < node[H[p]]; p >>= 1) {
            std::swap(H[p >> 1], H[p]);
            std::swap(pos_in_H[node[H[p]].id], pos_in_H[node[H[p >> 1]].id]);
        }
    return ret;
}

int Work()
{
    HeapInit();
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
    return ans += node[root].cxs;
}

int main()
{
    for (; ; ) {
        scanf("%d%d", &n, &root);
        if (!n && !root)
            return 0;
        for (int i = 1, c; i <= n; i++) {
            scanf("%d", &c);
            node[i] = Node(i, c);
        }
        father[root] = root;
        for (int i = 1, a, b; i < n; i++) {
            scanf("%d%d", &a, &b);
            father[b] = a;
        }
        printf("%d\n", Work());
    }
}
