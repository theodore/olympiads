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
const int neginf = 0; //xc0c0c0c0;
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

void init()
{
    for (N = 4; N < n + 2; N <<= 1)
	;
    //memset(valnow, 0xc0, sizeof valnow[0] * (N + N));
    //memset(valmax, 0xc0, sizeof valmax[0] * (N + N));
    //memset(delmax, 0xc0, sizeof delmax[0] * (N + N));
    //valnow[N] = 0xc0c0c0c0;
    //for (int i = N + n + 1; i < N + N; ++i)
    //valnow[i] = 0xc0c0c0c0;
}

void pushdown(int l, int r)
{
    if (!l)
	return;
    pushdown(l >> 1, r >> 1);
    if (delnow[l] || delmax[l] != neginf)
    {
	if (l < N)
	    for (int s = LS(l); s <= RS(l); ++s)
	    {
		UPX(valmax[s], valnow[s] + delmax[l]);
		valnow[s] += delnow[l];
		UPX(delmax[s], delnow[s] + delmax[l]);
		delnow[s] += delnow[l];
	    }
	delnow[l] = 0;
	delmax[l] = neginf; // does this really hurt?
    }
    if (delnow[r] || delmax[r] != neginf)
    {
	if (r < N)
	    for (int s = LS(r); s <= RS(r); ++s)
	    {
		UPX(delmax[s], delnow[s] + delmax[r]);
		delnow[s] += delnow[r];
		UPX(valmax[s], valnow[s] + delmax[r]);
		valnow[s] += delnow[r];
	    }
	delnow[r] = 0;
	delmax[r] = neginf;
    }
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

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
	scanf("%d", num + i);
    scanf("%d", &m);
    for (int i = 0; i < m; ++i)
	scanf("%d%d", &q[i].l, &q[i].r), q[i].id = i;
    std::sort(q, q + m);
    init();
    for (int i = 1, j = 0; j < m; ++i)
    {
	add(pre[num[i] + vadd] + 1, i, num[i]);
	pre[num[i] + vadd] = i;
	while (i == q[j].r)
	    ans[q[j].id] = ask(q[j].l, i), ++j;
    }
    for (int i = 0; i < m; ++i)
	printf("%d\n", ans[i]);
}
