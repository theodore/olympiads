#include <cstdio>
#include <algorithm>

const int maxn = 100013;

class SplayTree {
public:
    int MkTree(int, int);
    int Ask(int, int);
    void Change(int, int, int);

    int n;
    int treeroot;
private:
#if DB & 1
public:
#endif
    struct Elmt {
        int father, son[2];
        //int nl, nr, fl, fr; // normal left/right, flipped left/right
        int val;
        int l[4], r[4];
        int flag; // all rev? all flip?
        int size;
    };

    void Splay(int, int = 0);
    void Rotate(int);
    void PutDown(int);
    void Update(int);
    void ApplyFlag(int, int);
    int find(int k);

    Elmt node[maxn];
#if DB & 1
    void tab(int t) const
    {
        for (int i = 0; i < t; ++i)
            fprintf(stderr, "  ");
    }
    void Print(int i, int t) const
    {
        if (!i) {
            //fprintf(stderr, "\n");
            return;
        }
        //++t;
        tab(t++);
        //for (int i = 0; i < n; ++i) {
            const Elmt& x = node[i];
            fprintf(stderr, "node[%d] = {father = %d, son = {%d %d}, val = %d, "
                    "l = {%d %d %d %d}, r = {%d %d %d %d}, flag = %d}\n", i,
                    x.father, x.son[0], x.son[1], x.val, x.l[0], x.l[1], x.l[2],
                    x.l[3], x.r[0], x.r[1], x.r[2], x.r[3], x.flag);
            //}
            //fprintf(stderr, "\n");
        //tab(t);
        //fprintf(stderr, "L: ");
        Print(x.son[0], t);
        //tab(t);
        //fprintf(stderr, "R: ");
        Print(x.son[1], t);
    }
    void Print() const
    {
        Print(treeroot, 0);
        fprintf(stderr, "\n");
    }
#endif
};

int SplayTree::find(int k)
{
    int r = treeroot, t;
    PutDown(r);
    --k;
    while (k != (t = node[node[r].son[0]].size)) {
        if (k < t)
            r = node[r].son[0];
        else {
            k -= t + 1;
            r = node[r].son[1];
        }
        PutDown(r);
    }
    return r;
}

void SplayTree::PutDown(int x)
{
    ApplyFlag(node[x].son[0], node[x].flag);
    ApplyFlag(node[x].son[1], node[x].flag);
    node[x].flag = 0;
}

void SplayTree::Update(int x)
{
    for (int i = 0, a, b; i < 4; ++i) {
        if (i < 2) {
            a = node[x].son[0];
            b = node[x].son[1];
        } else {
            a = node[x].son[1];
            b = node[x].son[0];
        }
        int d = node[a].r[i] - node[b].l[i]
            + ((i & 1) ? -node[x].val : node[x].val);
        if (d >= 0) {
            node[x].l[i] = node[a].l[i];
            node[x].r[i] = node[b].r[i] + d;
        } else {
            node[x].l[i] = node[a].l[i] - d;
            node[x].r[i] = node[b].r[i];
        }
    }
    node[x].size = node[node[x].son[0]].size + node[node[x].son[1]].size + 1;
}

void SplayTree::ApplyFlag(int x, int f)
{
#if DB & 1
    //if (f)
    //fprintf(stderr, "Apply %d\n", x);
#endif
    using std::swap;
    if (f & 1) {
        swap(node[x].l[0], node[x].l[1]);
        swap(node[x].l[2], node[x].l[3]);
        swap(node[x].r[0], node[x].r[1]);
        swap(node[x].r[2], node[x].r[3]);
        node[x].val = -node[x].val;
    }
    if (f & 2) {
        swap(node[x].l[0], node[x].l[2]);
        swap(node[x].l[1], node[x].l[3]);
        swap(node[x].r[0], node[x].r[2]);
        swap(node[x].r[1], node[x].r[3]);
        swap(node[x].son[0], node[x].son[1]);
    }
    node[x].flag ^= f;
}

char s[maxn];

int SplayTree::MkTree(int l, int r)
{
    if (l == r)
        return 0;
    int m = (l + r) / 2, a, b;
    a = node[m].son[0] = MkTree(l, m);
    b = node[m].son[1] = MkTree(m + 1, r);
    node[a].father = m;
    node[b].father = m;
    if (s[m] == '(')
        node[m].val = 1;
    else if (s[m] == ')')
        node[m].val = -1;
    else // the two sentinel
        node[m].val = 0;
    Update(m);
    return m;
}

int SplayTree::Ask(int l, int r)
{
    l = find(l);
    r = find(r + 2);
#if DB & 1
    fprintf(stderr, "l = %d, r = %d\n", l, r);
#endif
    Splay(l);
#if DB & 1
    //fprintf(stderr, "After splay\n");
    //Print();
#endif
    Splay(r, l);
    const int x = node[r].son[0];
    return (node[x].l[0] + node[x].r[0]) / 2 + (node[x].l[0] & 1);
}

void SplayTree::Change(int l, int r, int f)
{
    l = find(l);
    r = find(r + 2);
    Splay(l);
    Splay(r, l);
    const int x = node[r].son[0];
    ApplyFlag(x, f);
}

void SplayTree::Splay(int x, int root)
{
#if DB & 1
    fprintf(stderr, "Splay %d %d\n", x, root);
#endif
    for (int y = node[x].father; y != root; y = node[x].father) {
        if (node[y].father == root)
            Rotate(x);
        else {
            const int f = node[y].father;
            if ((x == node[y].son[0]) == (y == node[f].son[0])) {
                Rotate(y);
                Rotate(x);
            } else {
                Rotate(x);
                Rotate(x);
            }
        }
    }
    if (root == 0)
        treeroot = x;
}

void SplayTree::Rotate(int x)
{
    const int y = node[x].father, f = node[y].father;
    const bool d = x == node[y].son[1];
    PutDown(y);
    PutDown(x);
    node[node[x].son[!d]].father = y;
    node[y].son[d] = node[x].son[!d];
    node[x].son[!d] = y;
    node[y].father = x;
    node[f].son[y == node[f].son[1]] = x;
    node[x].father = f;
    Update(y);
    Update(x);
}

int main()
{
    int m;
    static SplayTree splay;
    scanf("%d%d", &splay.n, &m);
    scanf("%s", s + 2);
    splay.treeroot = splay.MkTree(1, splay.n += 3);
#if DB & 1
    splay.Print();
#endif
    for (int a, b, c; m--; ) {
        scanf("%d%d%d", &a, &b, &c);
        if (a)
            splay.Change(b, c, 1 << (a - 1));
        else
            printf("%d\n", splay.Ask(b, c));
#if DB & 1
        splay.Print();
#endif
    }
}
