#include <cstdio>
#include <cassert>
#include <algorithm>

#define ls(x) ((x) << 1)
#define rs(x) (ls(x) + 1)

const int maxn = 20007;

class ST_t
{
public:
    int lt(int) const;
    int gt(int) const;
    void init(int);
    void init(const ST_t&, const ST_t&);
    void init_empty();
    void rm(int);
    void add(int);
#ifdef NDB
    void db_print() const;
#endif
private:
    struct node_t
    {
	void init(const int s, const int v, const int f, const int s0,
		const int s1);
	int size, val;
	int father, son[2];
    };
    void resize(const int);
    void rotate(const int);
    void splay(int pos, const int father = 0);
    void mklist(int* arr, int x, int& pos) const;
    int mktree(int* arr, int l, int r);
    int find_pred(int) const;
    int find_succ(int) const;
    node_t *node;
    int root, ncnt, id;
    static const int inf = 1234567890;
};

#ifdef DB
void ST_t::db_print() const
{
    fprintf(stderr, "root = %d, ncnt = %d\n", root, ncnt);
    for (int i = 0; i <= ncnt; ++i)
	fprintf(stderr, "%2d: {size %d, val %d, father %d, son %d %d}\n",
		i, node[i].size, node[i].val, node[i].father, node[i].son[0], node[i].son[1]);
    fprintf(stderr, "\n");
}
#endif

int ST_t::lt(int x) const
{
    int r = 0;
    for (int p = root; p; )
	if (node[p].val < x)
	{
	    r += node[node[p].son[0]].size + 1;
	    p = node[p].son[1];
	}
	else
	    p = node[p].son[0];
    return r;
}

int ST_t::gt(int x) const
{
    int r = 0;
    for (int p = root; p; )
	if (node[p].val > x)
	{
	    r += node[node[p].son[1]].size + 1;
	    p = node[p].son[0];
	}
	else
	    p = node[p].son[1];
    return r;
}

void ST_t::add(int x)
{
    int pos, next = root;
    do
    {
	pos = next;
	++node[pos].size;
	next = node[pos].son[node[pos].val < x];
    } while (next);
    node[next = node[pos].son[node[pos].val < x] = id].init(1, x, pos, 0, 0);
    splay(next);
}

void ST_t::rm(int x)
{
    int pos = root;
    while (node[pos].val != x)
	pos = node[pos].son[node[pos].val < x];
    id = pos;
    int pred = find_pred(pos);
    int succ = find_succ(pos);
    splay(pred);
    splay(succ, pred);
    node[succ].son[0] = 0;
    --node[succ].size;
    --node[pred].size;
}

int ST_t::find_pred(int p) const
{
    int r;
    if (node[p].son[0])
	for (r = node[p].son[0]; node[r].son[1]; r = node[r].son[1])
	    ;
    else
	for (r = node[p].father; node[r].son[0] == p; p = r, r = node[r].father)
	    ;
    return r;
}

int ST_t::find_succ(int p) const
{
    int r;
    if (node[p].son[1])
	for (r = node[p].son[1]; node[r].son[0]; r = node[r].son[0])
	    ;
    else
	for (r = node[p].father; node[r].son[1] == p; p = r, r = node[r].father)
	    ;
    return r;
}

void ST_t::node_t::init(const int s, const int v, const int f, const int s0,
	const int s1)
{
    size = s;
    val = v;
    father = f;
    son[0] = s0;
    son[1] = s1;
}

void ST_t::init(int x)
{
    node = new node_t[4];
    root = 1;
    node[0].init(0, 0, 0, 0, 0);
    node[1].init(3, x, 0, 2, 3);
    node[2].init(1, -inf, 1, 0, 0);
    node[3].init(1, inf, 1, 0, 0);
    ncnt = 3;
}

void ST_t::init(const ST_t& l, const ST_t& r)
{
    static int a[maxn], b[maxn], c[maxn];
    int n = 0, m = 0;
    l.mklist(a, l.root, n);
    r.mklist(b, r.root, m);
    std::merge(a, a + n, b, b + m, c);
    node = new node_t[n + m];
    node[0].init(0, 0, 0, 0, 0);
    root = mktree(c, 1, n + m - 1);
    assert(ncnt == n + m - 2);
}

void ST_t::init_empty()
{
    ncnt = 2;
    node = new node_t[3];
    node[0].init(0, 0, 0, 0, 0);
    node[1].init(2, -inf, 0, 0, 2);
    node[2].init(1, inf, 1, 0, 0);
    root = 1;
}

void ST_t::mklist(int* arr, int x, int& pos) const
{
    if (node[x].son[0])
	mklist(arr, node[x].son[0], pos);
    arr[pos++] = node[x].val;
    if (node[x].son[1])
	mklist(arr, node[x].son[1], pos);
}

int ST_t::mktree(int* arr, int l, int r)
{
    if (l >= r)
	return 0;
    int m = (l + r) / 2, a, b;
    a = mktree(arr, l, m);
    b = mktree(arr, m + 1, r);
    node[++ncnt].init(1 + node[a].size + node[b].size, arr[m], 0, a, b);
    node[a].father = node[b].father = ncnt;
    return ncnt;
}

void ST_t::resize(const int x)
{
    node[x].size = 1;
    node[x].size += node[node[x].son[0]].size;
    node[x].size += node[node[x].son[1]].size;
}

void ST_t::rotate(const int x)
{
    const int y = node[x].father;
    const int f = node[y].father;
    node[x].father = f;
    node[f].son[y == node[f].son[1]] = x;
    const int d = (x == node[y].son[1]);
    node[node[x].son[!d]].father = y;
    node[y].son[d] = node[x].son[!d];
    node[y].father = x;
    node[x].son[!d] = y;
    resize(y);
    resize(x);
}

void ST_t::splay(int x, const int pos)
{
    if (pos == 0)
	root = x;
    for (int y = node[x].father; y != pos; y = node[x].father)
    {
	if (node[y].father == pos)
	    rotate(x);
	else
	{
	    if ((x == node[y].son[1]) ^ (y == node[node[y].father].son[1]))
	    {
		rotate(x);
		rotate(x);
	    }
	    else
	    {
		rotate(y);
		rotate(x);
	    }
	}
    }
}

const int maxN = 1 << 16;
int n, N;
int kid[maxn];
int ans;
ST_t splay[maxN];

int* msort(int l, int r)
{
    if (l + 1 == r)
	return new int(kid[l]);
    int mid = (l + r) / 2;
    int* a = msort(l, mid);
    int* b = msort(mid, r);
    int* c = new int[r - l];
    int n = mid - l, m = r - mid, cc = 0;
    int i, j;
    for (i = 0, j = 0; i < n && j < m; )
	c[cc++] = (a[i] <= b[j] ? a[i++] : (ans += n - i, b[j++]));
    while (i < n)
	c[cc++] = a[i++];
    while (j < m)
	c[cc++] = b[j++];
    delete a;
    delete b;
    return c;
}

//ans += new - old;
//ans += greater than l, less than r;
//ans -= less than l, greater than r;
void calc(int L, int R)
{
    for (int l = L + N, r = R + N; l ^ r ^ 1; l >>= 1, r >>= 1)
    {
	if (~l & 1)
	{
	    int i = l ^ 1;
	    ans += splay[i].gt(kid[L]) + splay[i].lt(kid[R]) - 2;
	    ans -= splay[i].lt(kid[L]) + splay[i].gt(kid[R]) - 2;
#ifdef DB
	    fprintf(stderr, "ans = %d\n", ans);
#endif
	}
	if (r & 1)
	{
	    int i = r ^ 1;
	    ans += splay[i].gt(kid[L]) + splay[i].lt(kid[R]) - 2;
	    ans -= splay[i].lt(kid[L]) + splay[i].gt(kid[R]) - 2;
#ifdef DB
	    fprintf(stderr, "ans = %d\n", ans);
#endif
	}
    }
    ans += (kid[L] < kid[R]) - (kid[R] < kid[L]);
    for (int l = L + N, r = R + N; l ^ r; l >>= 1, r >>= 1)
    {
#ifdef DB
	fprintf(stderr, "%d %d\n", l, r);
#endif
	splay[l].rm(kid[L]);
	splay[l].add(kid[R]);
	splay[r].rm(kid[R]);
	splay[r].add(kid[L]);
    }
    std::swap(kid[L], kid[R]);
}

void init_tree()
{
    for (N = 4; N < n + 2; N <<= 1)
	;
    splay[N].init_empty();
    for (int i = N + 1; i <= N + n; ++i)
    {
	splay[i].init(kid[i - N]);
#ifdef DB
	fprintf(stderr, "splay %d:\n", i);
	splay[i].db_print();
#endif
    }
    for (int i = N + n + 1; i < N + N; ++i)
    {
	splay[i].init_empty();
#ifdef DB
	fprintf(stderr, "splay %d:\n", i);
	splay[i].db_print();
#endif
    }
    for (int i = N - 1; i; --i)
    {
	splay[i].init(splay[ls(i)], splay[rs(i)]);
#ifdef DB
	fprintf(stderr, "splay %d:\n", i);
	splay[i].db_print();
#endif
    }
}

#ifdef DB
void db_o()
{
    for (int i = 1; i < N + N; ++i)
    {
	fprintf(stderr, "splay %d:\n", i);
	splay[i].db_print();
    }
}
#endif

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
	scanf("%d", kid + i);
    msort(1, n + 1);
    printf("%d\n", ans);
    init_tree();
    int _, a, b;
    for (scanf("%d", &_); _--; )
    {
	scanf("%d%d", &a, &b);
	if (a > b)
	    std::swap(a, b);
	calc(a, b);
	printf("%d\n", ans);
#ifdef DB
	db_o();
#endif
    }
}
