#include <cstdio>
#include <algorithm>

#define UPX(a, b) a = std::max(a, b)

#ifdef LOCAL
# include <cassert>
# define Assert(x) assert(x)
#else
# define Assert(x) 0
#endif

const int max_n = 200007;

class SplayTree {
public:
    SplayTree(int, int[]);
    void Insert(int, int);
    void Replace(int, int);
    void Delete(int);
    int Query(int, int);
#if DB & 1
    void Print()
    {
        for (int i = 1; i <= n; i++)
            fprintf(stderr, "%d: ", i), node[i].Print();
        fprintf(stderr, "\n");
    }
#endif

private:
    struct Node {
        int father, son[2];
        int val;
        int sum, ans, lans, rans, size;
#if DB & 1
        void Print()
        {
            fprintf(stderr, "{f %d, s %d %d, v %d, sum %d, ans %d, l %d, r %d, "
                    "size = %d\n", father, son[0], son[1], val, sum, ans, lans,
                    rans, size);
        }
#endif
    };

    int Find(int k);
    int MkTree(int l, int r, int num[]);
    void Splay(int x, int f = 0);
    void Rotate(int x);
    int SplayInterval(int l, int r);
    void Update(int x);

    Node node[max_n];
    int n, root;
};

SplayTree::SplayTree(int a, int num[])
{
    //node[0].ans = num[1] = num[a + 2] = ~(~0u >> 1);
    root = MkTree(1, a + 3, num);
    n = a + 2;
}

void SplayTree::Insert(int x, int v)
{
    int z = SplayInterval(x - 1, x);
    Assert(!node[z].son[0]);
    node[z].son[0] = ++n;
    node[n].father = z;
    node[n].val  = node[n].sum = node[n].ans = v;
    node[n].lans = node[n].rans = std::max(0, v);
    node[n].size = 1;
}

void SplayTree::Replace(int x, int v)
{
    int t;
    Splay(t = Find(x));
    node[t].val = v;
}

void SplayTree::Delete(int x)
{
    int z = SplayInterval(x - 1, x + 1);
    Assert(node[z].son[0]);
    node[z].son[0] = 0;
}

int SplayTree::Query(int l, int r)
{
    int z = SplayInterval(l - 1, r + 1);
    Assert(node[z].son[0]);
    return node[node[z].son[0]].ans;
}

int SplayTree::Find(int k)
{
    int x = root;
    for (; ; ) {
        const int t = node[node[x].son[0]].size;
        if (t == k)
            return x;
        else if (t < k)
            x = node[x].son[1], k -= t + 1;
        else
            x = node[x].son[0];
    }
}

int SplayTree::MkTree(int l, int r, int num[])
{
    if (l == r)
        return 0;
    int m = (l + r) / 2;
    int a = node[m].son[0] = MkTree(l, m, num);
    int b = node[m].son[1] = MkTree(m + 1, r, num);
    node[a].father = node[b].father = m;
    node[m].val = num[m];
    Update(m);
    return m;
}

void SplayTree::Splay(int x, int father)
{
    for (int y = node[x].father, f; y != father; y = node[x].father)
        if ((f = node[y].father) == father)
            Rotate(x);
        else if ((x == node[y].son[0]) == (y == node[f].son[0]))
            Rotate(y), Rotate(x);
        else
            Rotate(x), Rotate(x);
    if (!father)
        root = x;
}

void SplayTree::Rotate(int x)
{
    int y = node[x].father, d = x == node[y].son[1], f = node[y].father;
    node[f].son[y == node[f].son[1]] = x;
    node[x].father = f;
    node[y].son[d] = node[x].son[!d];
    node[node[x].son[!d]].father = y;
    node[x].son[!d] = y;
    node[y].father = x;
    Update(y);
}

int SplayTree::SplayInterval(int l, int r)
{
    l = Find(l);
    r = Find(r);
    Splay(l);
    Splay(r, l);
    return r;
}

void SplayTree::Update(int x)
{
    using std::max;
    int a = node[x].son[0], b = node[x].son[1], v = node[x].val;
    node[x].ans = node[a].rans + v + node[b].lans;
    if (a) UPX(node[x].ans, node[a].ans);
    if (b) UPX(node[x].ans, node[b].ans);
    node[x].lans = max(node[a].lans, node[a].sum + v + node[b].lans);
    node[x].rans = max(node[b].rans, node[b].sum + v + node[a].rans);
    node[x].sum = node[a].sum + v + node[b].sum;
    node[x].size = node[a].size + 1 + node[b].size;
}

int main()
{
    int n, m;
    static int num[max_n];
    scanf("%d", &n);
    for (int i = 2; i <= n + 1; i++)
        scanf("%d", num + i);
    static SplayTree splay(n, num);
#if DB & 1
    splay.Print();
#endif
    for (scanf("%d", &m); m--; ) {
        char c;
        int x, y;
        scanf("\n%c%d", &c, &x);
        if (c == 'D') {
            splay.Delete(x);
        } else {
            scanf("%d", &y);
            switch (c) {
            case 'I': splay.Insert(x, y); break;
            case 'R': splay.Replace(x, y); break;
            case 'Q': printf("%d\n", splay.Query(x, y)); break;
            default: return 1;
            }
        }
#if DB & 1
        splay.Print();
#endif
    }
}
