#include <cstdio>
#include <cmath>
#include <cassert>
#include <cstring>
#include <algorithm>

const int maxn = 20003;
const int maxm = 157;
int kid[maxn];
int ans;
int blk[maxm][maxm];

int* msort(const int l, const int r)
{
    if (l + 1 == r)
	return new int(kid[l]);
    const int mid = (l + r) / 2;
    const int n = mid - l;
    const int m = r - mid;
    int* a = msort(l, mid);
    int* b = msort(mid, r);
    int* c = new int[r - l];
    int i, j, cc;
    for (i = j = cc = 0; i < n && j < m; )
	c[cc++] = (a[i] <= b[j] ? a[i++] : (ans += n - i, b[j++]));
    while (i < n)
	c[cc++] = a[i++];
    while (j < m)
	c[cc++] = b[j++];
    delete a;
    delete b;
    return c;
}

int n, m;

void mk_blks()
{
    for (int i = 0; i < n; ++i)
	blk[i / m][i % m] = kid[i];
    int nn = n - n / m * m;
    if (nn)
	memset(blk[n / m] + nn, 0x7f, sizeof blk[0][0] * size_t(m - nn));
    for (int i = 0; i * m < n; ++i)
	std::sort(blk[i], blk[i] + m);
}

int gt(int x, int y)
{
    //return blk[x] + m - std::upper_bound(blk[x], blk[x] + m, y);
    int* a = blk[x];
    int l, mid, r;
    for (l = -1, mid = m / 2, r = m; l + 1 < r; mid = (l + r) / 2)
	(y < a[mid] ? r : l) = mid;
    return m - r;
}

int gt(int l, int r, int x)
{
    int rtn = 0;
    for (int i = l; i < r; ++i)
	rtn += gt(i, x);
    return rtn;
}

int lt(int x, int y)
{
    //return std::lower_bound(blk[x], blk[x] + m, y) - blk[x];
    int* a = blk[x];
    int l, mid, r;
    for (l = -1, mid = m / 2, r = m; l + 1 < r; mid = (l + r) / 2)
	(y <= a[mid] ? r : l) = mid;
    return r;
}

int lt(int l, int r, int x)
{
    int rtn = 0;
    for (int i = l; i < r; ++i)
	rtn += lt(i, x);
    return rtn;
}

void addremove(int p, int rm, int add)
{
    int* a = blk[p];
    if (rm == add)
	return;
    else if (rm < add)
    {
	for (int i = 0; i < m; ++i)
	    if (a[i] == rm)
	    {
		for (int j = i + 1; j < m; ++j)
		{
		    a[j - 1] = a[j];
		    if (a[j] >= add)
		    {
			a[j - 1] = add;
			return;
		    }
		}
		a[m - 1] = add;
		return;
	    }
    }
    else
    {
	for (int i = m - 1; i >= 0; --i)
	    if (a[i] == rm)
	    {
		for (int j = i - 1; j >= 0; --j)
		{
		    a[j + 1] = a[j];
		    if (a[j] <= add)
		    {
			a[j + 1] = add;
			return;
		    }
		}
		a[0] = add;
		return;
	    }
    }
}

#ifdef NDB
void check()
{
    static int tmp[maxn];
    memcpy(tmp, kid, sizeof kid);
    int N = n / m * m + m * (n != n / m * m);
    for (int i = n; i < N; ++i)
	tmp[i] = 0x7f7f7f7f;
    for (int i = 0; i * m < N; ++i)
	std::sort(tmp + i * m, tmp + i * m + m);
    for (int i = 0; i < N; ++i)
	assert(tmp[i] == blk[i / m][i % m]);
}
#endif

//ans += new - old;
//ans += greater than l, less than r;
//ans -= less than l, greater than r;
void calc(int l, int r)
{
    int L = l / m + 1;
    int R = r / m;
    if (L <= R)
    {
	ans += gt(L, R, kid[l]) + lt(L, R, kid[r]) - lt(L, R, kid[l]) - gt(L, R, kid[r]);
	for (int i = l + 1; i < L * m; ++i)
	    ans += (kid[i] > kid[l]) + (kid[i] < kid[r]) - (kid[i] < kid[l]) - (kid[i] > kid[r]);
	for (int i = R * m; i < r; ++i)
	    ans += (kid[i] > kid[l]) + (kid[i] < kid[r]) - (kid[i] < kid[l]) - (kid[i] > kid[r]);
    }
    else
    {
	for (int i = l + 1; i < r; ++i)
	    ans += (kid[i] > kid[l]) + (kid[i] < kid[r]) - (kid[i] < kid[l]) - (kid[i] > kid[r]);
    }
    ans += (kid[r] > kid[l]) - (kid[r] < kid[l]);
    addremove(L - 1, kid[l], kid[r]);
    addremove(R, kid[r], kid[l]);
    std::swap(kid[l], kid[r]);
#ifdef NDB
    check();
#endif
}

int main()
{
    scanf("%d", &n);
    m = int(sqrt(n));
#ifdef DB
    fprintf(stderr, "m = %d\n", m);
#endif
    for (int i = 0; i < n; ++i)
	scanf("%d", kid + i);
    msort(0, n);
    mk_blks();
    printf("%d\n", ans);
    int _, a, b;
    for (scanf("%d", &_); _--; )
    {
	scanf("%d%d", &a, &b);
	--a;
	--b;
	if (a > b)
	    std::swap(a, b);
	calc(a, b);
	printf("%d\n", ans);
#ifdef DB
	for (int i = 0; i < n - 1; ++i)
	    fprintf(stderr, "%d ", kid[i]);
	fprintf(stderr, "%d\n", kid[n - 1]);
#endif
    }
}
