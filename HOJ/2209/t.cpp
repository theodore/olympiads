#include <cstdio>
#include <cassert>
#include <algorithm>

using namespace std;

const int N = 100005, INF = N + 1;

struct Node
{
    Node *ch[2], *par;
    int ma[2], mi[2];
    int val, sum, size;
    bool inversed, fliped;
#define swap(_a, _b) \
    ({int register t = _a; _a = _b; _b = t;})
    void inverse()
    {
        swap(ma[0], mi[0]);
        swap(ma[1], mi[1]);
        sum = -sum;
        val = -val;
        inversed ^= 1;
    }

    void flip()
    {
        swap(ma[0], ma[1]);
        swap(mi[0], mi[1]);
#undef swap
#define swap(a, b) \
        ({Node register *t = a; a = b; b = t;})
        swap(ch[0], ch[1]);
#undef swap
        fliped ^= 1;
    }

    void push()
    {
        if (inversed)
            ch[0]->inverse(), ch[1]->inverse(), inversed = false;
        if (fliped)
            ch[0]->flip(), ch[1]->flip(), fliped = false;
    }

#define max(_a, _b) \
    ({int register a = _a, b = _b; a = a > b ? a : b;})
    void update()
    {
        int register s0 = ch[0]->sum + val, s1 = ch[1]->sum + val;
        ma[0] = max(ch[0]->ma[0], s0 + ch[1]->ma[0]);
        ma[1] = max(ch[1]->ma[1], s1 + ch[0]->ma[1]);

        mi[0] = max(ch[0]->mi[0], -s0 + ch[1]->mi[0]);
        mi[1] = max(ch[1]->mi[1], -s1 + ch[0]->mi[1]);

        sum = ch[0]->sum + val + ch[1]->sum;
        size = ch[0]->size + 1 + ch[1]->size;
    }
};

Node NIL_INSTANCE, *NIL = &NIL_INSTANCE;

void print(Node *root)
{
    if (root == NIL) return;
    fprintf(stderr, "node: 0x%x, son: 0x%x 0x%x\n", root, root->ch[0], root->ch[1]);
    print(root->ch[0]);
    print(root->ch[1]);
}

Node *alloc(int val)
{
    static Node node[N];
    static int nnode = 0;
    Node *ret = node + (nnode ++);
    ret->ch[0] = ret->ch[1] = ret->par = NIL;
    ret->val = val;
    ret->update();
    return ret;
}

Node *root = NIL;

void check(Node *root)
{
    Node t = *root;
    t.update();
    assert(t.ma[0] == root->ma[0]);
    assert(t.ma[1] == root->ma[1]);
    assert(t.mi[0] == root->mi[0]);
    assert(t.mi[1] == root->mi[1]);
}

void do_printseq(Node *root, bool flag)
{
    if (root == NIL) return;
    root->push();
    if (!flag)
        check(root);
    do_printseq(root->ch[0], flag);
    if (flag)
        fprintf(stderr, "%c", root->val == 1 ? '(' : ')');
    do_printseq(root->ch[1], flag);
}

void printseq(bool flag = false)
{
    do_printseq(root, flag);
    if (flag)
        fprintf(stderr, "\n");
}


void init()
{
    NIL->ch[0] = NIL->ch[1] = NIL->par = NIL;
    NIL->val = NIL->sum = 0;
    NIL->ma[0] = NIL->ma[1] = NIL->mi[0] = NIL->mi[1] = 0;
    NIL->size = 0;
}

int n, nq;
Node *build_tree(const char *str, int left, int right)
{
    if (left > right)
        return NIL;
    int mid = (left + right) >> 1;
    Node *root = alloc(str[mid] == '(' ? 1 : -1);
    (root->ch[0] = build_tree(str, left, mid - 1))->par = root;
    (root->ch[1] = build_tree(str, mid + 1, right))->par = root;
    root->update();
    return root;
}

inline Node *&get_ref(Node *n)
{ return n->par == NIL ? root : n->par->ch[n == n->par->ch[1]]; }

void rotate(Node *&cur, bool dir)
{
    Node *son = cur->ch[!dir];
    (cur->ch[!dir] = son->ch[dir])->par = cur;
    son->par = cur->par;
    (son->ch[dir] = cur)->par = son;
    cur->update();
    cur = son;
}

void splay(Node *cur, Node *par0 = NIL)
{
    Node *par, *gpar;
    while ((par = cur->par) != par0)
    {
        if ((gpar = par->par) == par0)
            rotate(get_ref(par), cur == par->ch[0]);
        else
        {
            bool dcur = (cur == par->ch[1]),
                 dpar = (par == gpar->ch[1]);
            if (dcur != dpar)
                rotate(get_ref(par), !dcur), rotate(get_ref(gpar), !dpar);
            else rotate(get_ref(gpar), !dpar), rotate(get_ref(par), !dcur);
        }
    }
    cur->update();
}

Node *find(int k)
{
    assert(root->size >= k);
    Node *cur = root;
    for (; ;)
    {
        cur->push();
        int lsize = cur->ch[0]->size;
        if (k == lsize + 1)
            break;
        if (k <= lsize)
            cur = cur->ch[0];
        else k -= lsize + 1, cur = cur->ch[1];
    }
    assert(cur != NIL);
    splay(cur);
    return cur;
}

void splay_interval(int left, int right)
{
    right += 2;
    Node *nl = find(left), *nr = find(right);
    splay(nl), splay(nr, nl);
}

int excute_cmd(int cmd, int left, int right)
{
    splay_interval(left, right);
    Node *node = root->ch[1]->ch[0];
    int ret = -1;
    if (cmd == 0)
        ret = ((node->mi[0] + 1) >> 1) + ((node->ma[1] + 1) >> 1);
    else
    {
        if (cmd == 1)
            node->inverse();
        else node->flip();
        root->ch[1]->update();
        root->update();
    }
    return ret;
}

char str[N];

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

    init();

    READ_INT(n); READ_INT(nq);
    READ_STR(str + 1);
    root = build_tree(str, 0, n + 1);

    //  print(root);
    while (nq --)
    {
        int cmd, l, r;
        READ_INT(cmd); READ_INT(l); READ_INT(r);
        //  printseq();
        if (cmd == 0)
            printf("%d\n", excute_cmd(cmd, l, r));
        else excute_cmd(cmd, l, r);
    }
    //  printseq();
    return 0;
}
