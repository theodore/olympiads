#include <cstdio>
#include <algorithm>

using std::max;
using std::min;

const int maxn = 100013;
char s[maxn];

class SplayTree {
public:
    int root;
    int MkTree(const int l, const int r);
    int Ask(int l, int r);
    void Change(const int cmd, const int l, const int r);
#if DB & 1
    void Print()
    {
        PrintNode(root, 0);
        fprintf(stderr, "\n");
    }

    void tab(int x)
    {
        while (x--)
            fprintf(stderr, "  ");
    }

    void PrintNode(const int x, int t)
    {
        if (!x)
            return;
        tab(t++);
        const Elmt& z = node[x];
        fprintf(stderr, "%d: father = %d, son = {%d %d}, size = %d, val = %d, "
                "sum = %d, mx = {%d %d}, mn = {%d %d}, flag = %d\n", x,
                z.father, z.son[0], z.son[1], z.size, z.val, z.sum, z.mx[0],
                z.mx[1], z.mn[0], z.mn[1], z.flag);
        PrintNode(z.son[0], t);
        PrintNode(z.son[1], t);
    }
#endif

private:
    struct Elmt {
        int father, son[2], size;
        int val, sum;
        int mx[2], mn[2];
        int flag; // inv? flip?

        void ApplyFlag(const int);
    };

    void Splay(const int, const int = 0);
    int SplayInterval(int l, int r);
    void Rotate(int);
    int Find(int);
    void Update(const int);
    void PushDown(const int);

    Elmt node[maxn];
};

void SplayTree::Elmt::ApplyFlag(const int f)
{
    using std::swap;
    if (f & 1) {
        swap(mx[0], mn[0]);
        swap(mx[1], mn[1]);
        val = -val;
        sum = -sum;
    }
    if (f & 2) {
        swap(mx[0], mx[1]);
        swap(mn[0], mn[1]);
        swap(son[0], son[1]);
    }
    flag ^= f;
}

void SplayTree::Rotate(int x)
{
    const int y = node[x].father, f = node[y].father;
    const bool d = x == node[y].son[1];
    node[f].son[y == node[f].son[1]] = x;
    node[x].father = f;
    node[y].son[d] = node[x].son[!d];
    node[node[x].son[!d]].father = y;
    node[x].son[!d] = y;
    node[y].father = x;
    Update(y);
}

void SplayTree::Update(const int x)
{
    const int a = node[x].son[0], b = node[x].son[1];

    node[x].mx[0] = max(node[a].mx[0],
            node[a].sum + node[x].val + node[b].mx[0]);
    node[x].mx[1] = max(node[b].mx[1],
            node[b].sum + node[x].val + node[a].mx[1]);

    node[x].mn[0] = max(node[a].mn[0],
            -node[a].sum - node[x].val + node[b].mn[0]);
    node[x].mn[1] = max(node[b].mn[1],
            -node[b].sum - node[x].val + node[a].mn[1]);

    node[x].sum = node[a].sum + node[x].val + node[b].sum;
    node[x].size = node[a].size + 1 + node[b].size;
}

void SplayTree::PushDown(const int x)
{
    node[node[x].son[0]].ApplyFlag(node[x].flag);
    node[node[x].son[1]].ApplyFlag(node[x].flag);
    node[x].flag = 0;
}

void SplayTree::Splay(const int x, const int r)
{
    for (int y = node[x].father; y != r; y = node[x].father)
        if (node[y].father == r)
            Rotate(x);
        else {
            const int f = node[y].father;
            if ((x == node[y].son[0]) == (y == node[f].son[0]))
                Rotate(y), Rotate(x);
            else
                Rotate(x), Rotate(x);
        }
    if (r == 0)
        root = x;
}

int SplayTree::SplayInterval(int l, int r)
{
    l = Find(l - 1);
    r = Find(r + 1);
    Splay(l);
    Splay(r, l);
    return node[r].son[0];
}

int SplayTree::Find(int k)
{
    int p = root;
    for (; ; ) {
        PushDown(p);
        const int sz = node[node[p].son[0]].size;
        if (sz == k)
            return p;
        else if (sz < k)
            k -= sz + 1, p = node[p].son[1];
        else
            p = node[p].son[0];
    }
}

int SplayTree::MkTree(const int l, const int r)
{
    if (l >= r)
        return 0;
    const int m = (l + r) / 2;
    node[node[m].son[0] = MkTree(l, m)].father = m;
    node[node[m].son[1] = MkTree(m + 1, r)].father = m;
    if (s[m] == '(')
        node[m].val = 1;
    else if (s[m] == ')')
        node[m].val = -1;
    else
        node[m].val = 0;
    Update(m);
    return m;
}

int SplayTree::Ask(const int l, const int r)
{
    const int x = SplayInterval(l, r);
    return (node[x].mn[0] + node[x].mx[1]) / 2 + (node[x].mn[0] & 1);
}

void SplayTree::Change(const int cmd, const int l, const int r)
{
    const int x = SplayInterval(l, r);
    node[x].ApplyFlag(cmd);
}

int main()
{
    const int BUFFER_LEN = 1024 * 1024 * 5;
    static char buffer[BUFFER_LEN];
    char *ptr = buffer, *buf_end = ptr + 1;
#define PTR_NEXT() \
    { \
        ptr ++; \
        if (ptr == buf_end) \
        { \
            ptr = buffer; \
            buf_end = buffer + fread(buffer, 1, BUFFER_LEN, stdin); \
        } \
    }
#define READ_INT(_x_) \
    { \
        while ((*ptr < '0' || *ptr > '9') && *ptr != '-') \
        PTR_NEXT(); \
        bool _nega_ = false; \
        if (*ptr == '-') \
        { \
            _nega_ = true; \
            PTR_NEXT(); \
        } \
        int register _n_ = 0; \
        while (*ptr >= '0' && *ptr <= '9') \
        { \
            _n_ = _n_ * 10 + *ptr - '0'; \
            PTR_NEXT(); \
        } \
        if (_nega_) \
        _n_ = - _n_; \
        (_x_) = (_n_); \
    }
#define READ_STR(_s_) \
    { \
        while (*ptr == ' ' || *ptr == '\n' || *ptr == '\r') \
        PTR_NEXT(); \
        char *_p_ = (_s_); \
        while (!(*ptr == ' ' || *ptr == '\n' || *ptr == '\r')) \
        { \
            *(_p_ ++) = *ptr; \
            PTR_NEXT(); \
        } \
        *_p_ = 0; \
    }
    PTR_NEXT();

    int n, m;
    static SplayTree splay;
    READ_INT(n);
    READ_INT(m);
    READ_STR(s + 2);
    splay.root = splay.MkTree(1, n + 3);
#if DB & 1
    splay.Print();
#endif
    for (int a, b, c; m--; ) {
        READ_INT(a);
        READ_INT(b);
        READ_INT(c);
        if (a)
            splay.Change(1 << (a - 1), b, c);
        else
            printf("%d\n", splay.Ask(b, c));
#if DB & 1
        splay.Print();
#endif
    }
}
