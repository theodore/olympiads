/** @file paint.cpp
 *  @brief SDOI2011 Round 1, Day 1, Problem 3, paint.
 *  This is also my first Lu4 Jing4 Pou1 Fen1(I don't know how to express this
 *  in English..) implementation.
 *  @author Theodore You <theodoreyou@gmail.com>
 *  @date Sun, 10 Apr 2011 23:38:02 +0800
 */
#include <cstdio>
#include <cstdlib>
#include <algorithm>

#define IL if (~l & 1)
#define IR if (r & 1)
#define L (l ^ 1)
#define R (r ^ 1)
#define LS(x) ((x) << 1)
#define RS(x) (LS(x) + 1)
#define FDEF bool fl = false, fr = false
#define FL if (fl)
#define FR if (fr)
#define FLT fl = true
#define FRT fr = true
#define FOR for (; l ^ r ^ 1; l >>= 1, r >>= 1)
#define FORL for (l >>= 1; l; l >>= 1)

struct Value
{
    int cnt, hc, lc; // count, high color, low color

    void init(const int z)
    { cnt = z != 0; hc = lc = z; }
    void operator+=(const Value& z)
    {
	cnt += z.cnt - (hc == z.lc && hc);
	if (z.hc)
	    hc = z.hc;
	if (!lc)
	    lc = z.lc;
    }
};

const Value operator+(const Value& a, const Value& b)
{
    Value z;
    z.hc = a.hc ? a.hc : b.hc;
    z.lc = b.lc ? b.lc : a.lc;
    z.cnt = a.cnt + b.cnt - (a.lc == b.hc && a.lc);
    return z;
}

struct Info;

class SgmtTree
{
public:
    const Info* const father;
    const int depth;

    SgmtTree(Info* pos, const Info* f);
    void set(int d0, int d1, const int newcolor);
    const Value ask(int d0, int d1);
private:
#if DB >= 1
public:
#endif
    int N;
    //int *color, *stamp;
    Value* data;
    int* all2;

    void putdown(int l, int r);
};

struct Info
{
    int depth;
    SgmtTree* tree;
    // temporary data(only for init)
    int color, length;
    Info* chs;
};

#if DB >= 1
namespace db
{
    void printtree();
    void printallst();
    void print(const SgmtTree*);
    template<class T> void st_print(const T*, const int);
    void st_print(const int);
    void st_print(const Value);
}
#endif

const int maxn = 100007;
const int maxm = 200007;
int n;
Info node[maxn];
int start[maxn], to[maxm], next[maxm], edge;
//int time;

SgmtTree::SgmtTree(Info* pos, const Info* f): father(f), depth(pos->depth)
{
    const int nn = pos->length;
    for (N = 4; N < nn + 2; N <<= 1)
	;
    //color = new int[N * 2];
    data = new Value[N * 2];
    all2 = new int[N * 2];
    data[N].init(0);
    for (int i = N + 1; pos; pos = pos->chs, ++i)
	data[i].init(pos->color), pos->tree = this;
    for (int i = N + nn + 1; i < N + N; ++i)
	data[i].init(0);
    for (int i = N - 1; i; --i)
	data[i] = data[LS(i)] + data[RS(i)];
}

void SgmtTree::putdown(int l, int r)
{
    if (l)
    {
	putdown(l >> 1, r >> 1);
	if (all2[l])
	{
	    if (l < N)
	    {
		const int c = all2[l];
		all2[LS(l)] = c;
		data[LS(l)].init(c);
		all2[RS(l)] = c;
		data[RS(l)].init(c);
	    }
	    all2[l] = 0;
	}
	if (all2[r])
	{
	    if (r < N)
	    {
		const int c = all2[r];
		all2[LS(r)] = c;
		data[LS(r)].init(c);
		all2[RS(r)] = c;
		data[RS(r)].init(c);
	    }
	    all2[r] = 0;
	}
    }
}

void SgmtTree::set(int l, int r, const int c)
{
    l += N - depth;
    r += N - depth + 2;
#if DB >= 1
    fprintf(stderr, "set, this = %p, l = %d, r = %d\n", this, l, r);
#endif
    putdown(l, r);
    FDEF;
    FOR
    {
	FL data[l] = data[LS(l)] + data[RS(l)];
	FR data[r] = data[LS(r)] + data[RS(r)];
	IL data[L].init(c), all2[L] = c, FLT;
	IR data[R].init(c), all2[R] = c, FRT;
    }
    data[l] = data[LS(l)] + data[RS(l)];
    data[r] = data[LS(r)] + data[RS(r)];
    FORL data[l] = data[LS(l)] + data[RS(l)];
}

const Value SgmtTree::ask(int l, int r)
{
    l += N - depth;
    r += N - depth + 2;
    putdown(l, r);
    Value rl, rr;
    rl.init(0);
    rr.init(0);
    FOR
    {
	IL rl = rl + data[L];
	IR rr = data[R] + rr;
    }
    return rl + rr;
}

void add(const int a, const int b)
{
    to[++edge] = b;
    next[edge] = start[a];
    start[a] = edge;
}

int ask(const Info* a, const Info* b)
{
#if DB >= 1
    fprintf(stderr, "ask a = %p, b = %p\n", a, b);
#endif
    Value *va = new Value, *vb = new Value, *v;
    va->init(0);
    va->init(0);
    SgmtTree* t;
    const Info** p = &a;
    while (a->tree != b->tree)
    {
	if (a->tree->depth < b->tree->depth)
	    t = b->tree, p = &b, v = vb;
	else
	    t = a->tree, p = &a, v = va;
	*v += t->ask(t->depth, (*p)->depth);
	*p = t->father;
    }
    t = (*p)->tree;
#if DB >= 1
    fprintf(stderr, " a = %p, b = %p\n", a, b);
    fprintf(stderr, "*p = %p\n", *p);
    fprintf(stderr, "(*p)->tree = %p\n", (*p)->tree);
    fprintf(stderr, "t = %p\n", t);
#endif
    (a->depth < b->depth ? *vb : *va) +=
	t->ask(std::min(a->depth, b->depth), std::max(a->depth, b->depth));
#if DB >= 1
    fprintf(stderr, "t = %p\n", t);
#endif
    return va->cnt + vb->cnt - (va->hc == vb->hc);
}

void change(const Info* a, const Info* b, const int c)
{
#if DB >= 1
    fprintf(stderr, "change %d %d %d\n", a - node, b - node, c);
#endif
    SgmtTree* t;
    const Info** p = &a;
    while (a->tree != b->tree)
    {
	if (a->tree->depth < b->tree->depth)
	    t = b->tree, p = &b;
	else
	    t = a->tree, p = &a;
	t->set(t->depth, (*p)->depth, c);
	*p = t->father;
    }
    t = (*p)->tree;
#if DB >= 1
    fprintf(stderr, " %d %d\n", a - node, b - node);
#endif
    t->set(std::min(a->depth, b->depth), std::max(a->depth, b->depth), c);
}

int dfs(const int x, const int f)
{
    node[x].depth = node[f].depth + 1;
    node[x].chs = &node[0];
    int bsz = 0, tot = 1;
    Info*& chs = node[x].chs;
    for (int e = start[x]; e; e = next[e])
	if (to[e] != f)
	{
	    const int sz = dfs(to[e], x);
	    tot += sz;
	    if (sz > bsz)
		bsz = sz, chs = &node[to[e]];
	}
    node[x].length = chs->length + 1;
    for (int e = start[x]; e; e = next[e])
	if (to[e] != f && &node[to[e]] != chs)
	    node[to[e]].tree = new SgmtTree(&node[to[e]], &node[x]);
    return tot;
}

inline void mktree(const int root)
{
#if DB >= 1
    fprintf(stderr, "root = %d\n", root);
#endif
    dfs(root, 0);
    node[root].tree = new SgmtTree(&node[root], 0);
#if DB >= 1
    db::printtree();
    db::printallst();
#endif
}

inline void init()
{
    for (int i = 1; i <= n; ++i)
	scanf("%d", &node[i].color);
    for (int i = 1, a, b; i < n; ++i)
    {
	scanf("%d%d", &a, &b);
	add(a, b);
	add(b, a);
    }
    mktree(rand() % n + 1);
}

int main()
{
#if DB >= 1
    fprintf(stderr, "\n****************\nProgram Starts\n****************\n\n");
#endif
    int _;
    scanf("%d%d", &n, &_);
    srand(n * _);
    init();
    char s[3];
    int a, b, c;
    //for (time = 1; time <= _; ++time)
    while (_--)
    {
	if (scanf("%s%d%d%d", s, &a, &b, &c) == 3)
	    printf("%d\n", ask(&node[a], &node[b]));
	else
	    change(&node[a], &node[b], c);
#if DB >= 1
	db::printallst();
#endif
    }
}

#if DB >= 1
void db::printtree()
{
    fprintf(stderr, "The tree:\n");
    for (int i = 1; i <= n; ++i)
    {
	const Info& x = node[i];
	printf("%2d: depth = %d, tree = %p, color = %d, length = %d, "
		"chs = %p\n", i, x.depth, x.tree, x.color, x.length, x.chs);
    }
    fprintf(stderr, "\n");
}

#include <map>
std::map<SgmtTree*, bool> used;

void db::printallst()
{
    fprintf(stderr, "-------------\nAll SgmtTrees:\n");
    used.clear();
    for (int i = 1; i <= n; ++i)
    {
	SgmtTree* z = node[i].tree;
	if (!used[z])
	{
	    used[z] = true;
	    print(z);
	}
    }
    fprintf(stderr, "-------------\n");
}

void db::print(const SgmtTree* p)
{
    fprintf(stderr, "%p:\n", p);
    fprintf(stderr, "father = %p, depth = %d, N = %d\n",
	    p->father, p->depth, p->N);
    st_print(p->data, p->N);
    st_print(p->all2, p->N);
    fprintf(stderr, "\n");
}

template<class T> void db::st_print(const T* z, const int N)
{
    for (int i = 1; i < N + N; ++i)
    {
	st_print(z[i]);
	if (i + 1 == ((i + 1) & (-i - 1)))
	    fprintf(stderr, "\n");
    }
}

void db::st_print(const int z)
{
    fprintf(stderr, "%d ", z);
}

void db::st_print(const Value z)
{
    //fprintf(stderr, "{cnt = %d, hc = %d, lc = %d} ", z.cnt, z.hc, z.lc);
    fprintf(stderr, "{%d, %d, %d} ", z.cnt, z.hc, z.lc);
}
#endif
