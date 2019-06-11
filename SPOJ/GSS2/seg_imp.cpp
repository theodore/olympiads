#include <cstdio>
#include <cstring>
#include <algorithm>

#define UPX(a, b) (a) = std::max((a), (b))
#define LS(x) ((x) << 1)
#define RS(x) (LS(x) + 1)
#define FOR for (l += N - 1, r += N + 1; l ^ r ^ 1; l >>= 1, r >>= 1)
#define IL if (~l & 1)
#define IR if (r & 1)
#define L (l ^ 1)
#define R (r ^ 1)
#define FLGS bool fl = false, fr = false
#define FL if (fl)
#define FR if (fr)
#define FLT fl = true
#define FRT fr = true

const int maxn = 100007;
const int maxN = 1 << 18;
const int maxm = 100007;
const int maxv = 200007;
const int vadd = 100000;
int n, N, m;
int num[maxn];
int ans[maxm];
int pre[maxv];

struct Query
{
    int l, r, id;
    bool operator<(const Query& z) const
    { return r < z.r; }
};

Query q[maxm];

int valnow[maxN], valmax[maxN];
int delnow[maxN], delmax[maxN];

void pushdown(int Ll, int Rr)
{
    for (int l = 1, r = 1, z = N >> 1; z; z >>= 1)
    {
	if (delnow[l] || delmax[l])
	{
	    UPX(valmax[LS(l)], valnow[LS(l)] + delmax[l]);
	    valnow[LS(l)] += delnow[l];
	    UPX(delmax[LS(l)], delnow[LS(l)] + delmax[l]);
	    delnow[LS(l)] += delnow[l];

	    UPX(valmax[RS(l)], valnow[RS(l)] + delmax[l]);
	    valnow[RS(l)] += delnow[l];
	    UPX(delmax[RS(l)], delnow[RS(l)] + delmax[l]);
	    delnow[RS(l)] += delnow[l];

	    delnow[l] = delmax[l] = 0;
	}
	if (delnow[r] || delmax[r])
	{
	    UPX(valmax[LS(r)], valnow[LS(r)] + delmax[r]);
	    valnow[LS(r)] += delnow[r];
	    UPX(delmax[LS(r)], delnow[LS(r)] + delmax[r]);
	    delnow[LS(r)] += delnow[r];

	    UPX(valmax[RS(r)], valnow[RS(r)] + delmax[r]);
	    valnow[RS(r)] += delnow[r];
	    UPX(delmax[RS(r)], delnow[RS(r)] + delmax[r]);
	    delnow[RS(r)] += delnow[r];

	    delnow[r] = delmax[r] = 0;
	}
	l <<= 1;
	r <<= 1;
	if (Ll & z)
	    ++l;
	if (Rr & z)
	    ++r;
    }
    delnow[Ll] = delmax[Ll] = delnow[Rr] = delmax[Rr] = 0;
}

void update(int x)
{
    valnow[x] = std::max(valnow[LS(x)], valnow[RS(x)]);
    UPX(valmax[x], valnow[x]);
}

void add(int l, int r, int v)
{
    pushdown(l + N - 1, r + N + 1);
    FLGS;
    FOR
    {
	FL update(l);
	FR update(r);
	IL UPX(delmax[L], delnow[L] += v),
	   UPX(valmax[L], valnow[L] += v), FLT;
	IR UPX(delmax[R], delnow[R] += v),
	   UPX(valmax[R], valnow[R] += v), FRT;
    }
    FL update(l);
    FR update(r);
    for (l >>= 1; l; l >>= 1)
	update(l);
}

int ask(int l, int r)
{
    pushdown(l + N - 1, r + N + 1);
    int z = 1 << 31;
    FOR
    {
	IL UPX(z, valmax[L]);
	IR UPX(z, valmax[R]);
    }
    return z;
}

const int BUFFER_SIZE = 1024 * 1024 * 5;
static char buffer[BUFFER_SIZE];
char *ptr = buffer, *buf_end = buffer +1;
#define PTR_NEXT() \
{ \
    ptr ++; \
    if (ptr == buf_end) \
    { \
	ptr = buffer; \
	buf_end = buffer + fread(buffer, 1, BUFFER_SIZE, stdin); \
    } \
}
#define getint(_n_) \
{ \
    while ((*ptr < '0' || *ptr > '9') && *ptr != '-') \
    PTR_NEXT(); \
    bool _nega_; \
    if (*ptr == '-') \
    { \
	_nega_ = true; \
	PTR_NEXT(); \
    } else _nega_ = false; \
    int register _x_ = 0; \
    while (*ptr >= '0' && *ptr <= '9') \
    { \
	_x_ = _x_ * 10 + *ptr - '0'; \
	PTR_NEXT(); \
    } \
    (_n_) = _nega_ ? -_x_ : _x_; \
}

char outs[maxn * 11], *optr = outs + maxn * 11 - 1;

void out(int x)
{
    if (x == 0)
	*--optr = '0';
    while (x)
    {
	*--optr = x % 10 + '0';
	x /= 10;
    }
    *--optr = '\n';
}

int start[maxn], tol[maxn], toid[maxn], next[maxn], edge;

void add_q(const int r, const int l, const int id)
{
    tol[++edge] = l;
    toid[edge] = id;
    next[edge] = start[r];
    start[r] = edge;
}

int main()
{
    PTR_NEXT();
    getint(n);
    for (int i = 1; i <= n; ++i)
	getint(num[i]);
    getint(m);
    if (m < n)
    {
	for (int i = 0; i < m; ++i)
	{
	    getint(q[i].l); getint(q[i].r); q[i].id = i;
	}
	std::sort(q, q + m);
    }
    else
    {
	for (int i = 0, l, r; i < m; ++i)
	{
	    getint(l);
	    getint(r);
	    add_q(r, l, i);
	}
	for (int i = 1, j = 0; i <= n; ++i)
	{
	    for (int e = start[i]; e; e = next[e])
	    {
		q[j].l = tol[e];
		q[j].r = i;
		q[j].id = toid[e];
		++j;
	    }
	}
    }
    for (N = 4; N < n + 2; N <<= 1)
	;
    for (int i = 1, j = 0; j < m; ++i)
    {
	add(pre[num[i] + vadd] + 1, i, num[i]);
	pre[num[i] + vadd] = i;
	while (i == q[j].r)
	    ans[q[j].id] = ask(q[j].l, i), ++j;
    }
    for (int i = m - 1; i >= 0; --i)
	out(ans[i]);
    puts(optr + 1);
}
