/** @file path-ripping.cpp
 *  @brief ZJOI2008 count.
 *  Solved by path ripping.
 *  @author Thedore You <theodoreyou@gmail.com>
 *  @date Fri, 15 Apr 2011 09:05:33 +0800
 */

#include <cstdio>
#include <cstdlib>
#include <cctype>
//#include <cmath>
#include <algorithm>

#if DB >= 1
bool go;
#endif

struct Value
{
    int sum, max;
    void operator+=(const Value& z)
    {
#if DB >= 1
	if (go)
	fprintf(stderr, "sum = %d\n", sum);
#endif
	sum += z.sum;
	max = std::max(max, z.max);
    }
};

const Value operator+(Value a, const Value& b)
{
    a += b;
    return a;
}

const int maxn = 30007;
const int maxm = 60007;
int start[maxn], to[maxm], next[maxm], edge;

struct Info;

class SgmtTree
{
public:
    const int father;
    const int depth;

    SgmtTree(Info*, const int f);
    void change(int, const int);
    const Value ask(int, int) const;
private:
    int N;
    Value* num;
};

struct Info
{
    int depth;
    SgmtTree* tree;
    // tmp
    int num, len;
    Info* chs;
};

Info node[maxn];

SgmtTree::SgmtTree(Info* p, const int f) : father(f), depth(p->depth)
{
    const int n = p->len;
    for (N = 4; N < n + 2; N <<= 1)
	;
    num = new Value[N + N];
    num[N].sum = 0, num[N].max = -(~0u >> 2);
    for (int i = N + 1; p; p = p->chs, ++i)
	num[i].sum = num[i].max = p->num, p->tree = this;
    for (int i = N + n + 1; i < N + N; ++i)
	num[i].sum = 0, num[i].max = -(~0u >> 2);
    for (int i = N - 1; i; --i)
	num[i] = num[i << 1] + num[(i << 1) + 1];
}

void SgmtTree::change(int p, const int v)
{
    p += N - depth + 1;
    num[p].sum = num[p].max = v;
    for (p >>= 1; p; p >>= 1)
	num[p] = num[p << 1] + num[(p << 1) + 1];
}

const Value SgmtTree::ask(int l, int r) const
{
    l += N - depth;
    r += N - depth + 2;
#if DB >= 1
    fprintf(stderr, "ask %d %d\n", l, r);
#endif
    Value ret;
    ret.sum = 0, ret.max = -(~0u >> 2);
#if DB >= 1
    fprintf(stderr, "aret = %d %d\n", ret.sum, ret.max);
    go = true;
#endif
    for (; l ^ r ^ 1; l >>= 1, r >>= 1)
    {
	if (~l & 1)
	{
#if DB >= 1
    fprintf(stderr, " aret = %d %d\n", ret.sum, ret.max);
#endif
	    ret += num[l ^ 1];
#if DB >= 1
	    fprintf(stderr, "num[l ^ 1] = %d %d\n", num[l ^ 1].sum, num[l ^ 1].max);
    fprintf(stderr, " aret = %d %d\n", ret.sum, ret.max);
#endif
	}
	if (r & 1)
	{
	    ret += num[r ^ 1];
#if DB >= 1
	    fprintf(stderr, "num[r ^ 1] = %d %d\n", num[r ^ 1].sum, num[r ^ 1].max);
    fprintf(stderr, "aret = %d %d\n", ret.sum, ret.max);
#endif
	}
#if DB >= 1
    fprintf(stderr, "aret = %d %d\n", ret.sum, ret.max);
#endif
    }
    return ret;
}

void add(const int a, const int b)
{
    to[++edge] = b;
    next[edge] = start[a];
    start[a] = edge;
}

int dfs(const int x, const int f)
{
#if DB >= 1
    fprintf(stderr, "dfs %d %d\n", x, f);
#endif
    node[x].depth = node[f].depth + 1;
    int chs = 0, sz = 0, tot = 1;
    for (int e = start[x], t; e; e = next[e])
	if (to[e] != f)
	{
	    if ((t = dfs(to[e], x)) > sz)
	    {
		sz = t;
		chs = to[e];
	    }
	    tot += t;
	}
    node[x].chs = &node[chs];
    node[x].len = node[chs].len + 1;
    for (int e = start[x]; e; e = next[e])
	if (to[e] != f && to[e] != chs)
	    node[to[e]].tree = new SgmtTree(&node[to[e]], x);
    return tot;
}

void mktree(const int root)
{
    dfs(root, 0);
    node[root].tree = new SgmtTree(&node[root], 0);
}

const Value ask(int a, int b)
{
    Value ret;
    ret.sum = 0;
    ret.max = -(~0u >> 2);
#if DB >= 1
    fprintf(stderr, "ret = %d %d\n", ret.sum, ret.max);
#endif
    int *p;
    while (node[a].tree != node[b].tree)
    {
	p = node[a].tree->depth < node[b].tree->depth ? &b : &a;
	ret += node[*p].tree->ask(node[*p].tree->depth, node[*p].depth);
	*p = node[*p].tree->father;
    }
    ret += node[a].tree->ask(std::min(node[a].depth, node[b].depth),
	    std::max(node[a].depth, node[b].depth));
#if DB >= 1
    fprintf(stderr, "ret = %d %d\n", ret.sum, ret.max);
#endif
    return ret;
}

void getint(int& x)
{
    scanf("%d", &x);
    return;
    int c;
    while (!isdigit(c = getchar()))
	;
    x = c - '0';
    while (isdigit(c = getchar()))
	x = x * 10 + c - '0';
}

void getstr(char* s)
{
    int c;
    while (!isalpha(c = getchar()))
	;
    *s = (char)c;
    while (isalpha(c = getchar()))
	*++s = (char)c;
}

int main()
{
    int n;
    getint(n);
    for (int i = 1, a, b; i < n; ++i)
    {
	getint(a);
	getint(b);
	add(a, b);
	add(b, a);
    }
    for (int i = 1; i <= n; ++i)
	getint(node[i].num);
    srand(n * n);
    mktree(rand() % n + 1);
    int m, a, b;
    char s[11];
    for (getint(m); m--; )
    {
	getstr(s);
	getint(a);
	getint(b);
	if (s[1] == 'H')
	    node[a].tree->change(node[a].depth, b);
	else
	    printf("%d\n", s[1] == 'S' ? ask(a, b).sum : ask(a, b).max);
    }
}
