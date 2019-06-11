#include <cstdio>
#include <cstring>
#include <algorithm>

#ifdef LOCAL
# include <cassert>
# define Assert(x) assert(x)
#else
# define Assert(x) 0
#endif

typedef int Hash_t;
const int maxn = 100007;

class SplayTree {
public:
    SplayTree(char* s);
    void Insert(int pos, char c);
    void Replace(int pos, char c);
    int Query(int l, int r);
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
        char c;
        Hash_t sum;
        int size;
#if DB & 1
        void Print()
        {
            fprintf(stderr, "{father %d, son %d %d, c %c, sum %d, size %d\n",
                    father, son[0], son[1], c, sum, size);
        }
#endif
    };

    int MkTree(int l, int r, char* s);
    int SplayInterval(int l, int r);
    Hash_t GetSum(int l, int r);
    int Find(int k);
    void Update(int x);
    void Splay(int x, int f = 0);
    void Rotate(int x);

    Node node[maxn];
    int pow[maxn];
    int n, root;
    static const int base = 127;
};

SplayTree::SplayTree(char* s)
{
    pow[0] = 1;
    for (int i = 1; i < maxn; i++)
        pow[i] = pow[i - 1] * base;
    root = MkTree(1, (n = strlen(s + 2)) + 3, s);
    n += 2;
}

int SplayTree::MkTree(int l, int r, char* s)
{
    if (l == r)
        return 0;
    int m = (l + r) / 2;
    int a = node[m].son[0] = MkTree(l, m, s);
    int b = node[m].son[1] = MkTree(m + 1, r, s);
    node[a].father = node[b].father = m;
    node[m].c = s[m];
    Update(m);
    return m;
}

int SplayTree::Query(int L, int R)
{
    if (L > R)
        std::swap(L, R);
    int l, r, m;
    for (l = 0, r = n - R, m = (l + r) / 2; l + 1 < r; m = (l + r) / 2)
        (GetSum(L, L + m - 1) == GetSum(R, R + m - 1) ? l : r) = m;
    return l;
}

void SplayTree::Insert(int x, char c)
{
    int t = Find(x), z;
    Splay(t);
    Splay(z = Find(x + 1), t);
    Assert(node[z].son[0] == 0);
    node[z].son[0] = ++n;
    node[n].father = z;
    node[n].c = c;
    node[n].sum = c;
    node[n].size = 1;
}

void SplayTree::Replace(int x, char c)
{
    int t = Find(x);
    Splay(t);
    node[t].c = c;
}

Hash_t SplayTree::GetSum(int l, int r)
{
    if (l > r)
        return 0;
    int t = SplayInterval(l, r);
    return node[t].sum;
}

int SplayTree::Find(int k)
{
    int x = root;
    for (; ; ) {
        int t = node[node[x].son[0]].size;
        if (t == k)
            return x;
        else if (t < k)
            x = node[x].son[1], k -= t + 1;
        else
            x = node[x].son[0];
    }
}

int SplayTree::SplayInterval(int l, int r)
{
    l = Find(l - 1);
    r = Find(r + 1);
    Splay(l);
    Splay(r, l);
    return node[r].son[0];
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
    if (father == 0)
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

void SplayTree::Update(int x)
{
    int a = node[x].son[0], b = node[x].son[1];
    node[x].sum = node[a].sum * base + node[x].c;
    node[x].sum *= pow[node[b].size];
    node[x].sum += node[b].sum;
    node[x].size = node[a].size + 1 + node[b].size;
}

int main()
{
    static char s[maxn];
    int m;
    scanf("%s%d", s + 2, &m);
    for (static SplayTree splay(s); m--; ) {
        char cmd, c;
        int x, y;
        scanf("\n%c%d", &cmd, &x);
        switch (cmd) {
        case 'Q':
            scanf("%d", &y);
            printf("%d\n", splay.Query(x, y));
            break;
        case 'R':
            scanf(" %c", &c);
            splay.Replace(x, c);
            break;
        case 'I':
            scanf(" %c", &c);
            splay.Insert(x, c);
            break;
        }
#if DB & 1
        splay.Print();
#endif
    }
}
