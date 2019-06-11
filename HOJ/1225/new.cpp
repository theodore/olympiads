#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

class Int
{
public:
    Int() : n(100000){}
    Int(int z) : n(1)
    {
	memset(num, 0, sizeof num);
	num[0] = z;
	if (z >= N)
	{
	    ++n;
	    num[1] = z / N;
	    num[0] %= N;
	}
    }
    void setto1()
    {
	n = 1;
	memset(num, 0, sizeof num);
	num[0] = 1;
    }
    bool operator<(const Int& z)
    {
	if (n != z.n)
	    return n < z.n;
	for (int i = n - 1; i >= 0; --i)
	    if (num[i] != z.num[i])
		return num[i] < z.num[i];
	return false;
    }

    void operator*=(const Int& z)
    {
#if DB >= 2
	fprintf(stderr, "*=\n");
#endif
#if DB >= 1
	fprintf(stderr, "*this= ");
	output();
	fprintf(stderr, "z    = ");
	z.output();
#endif
	Int r;
	r.setto1();
	r.num[0] = 0;
	for (int i = 0; i < n; ++i)
	{
	    long long c = 0;
	    for (int j = 0; j < z.n || c; ++j)
	    {
		r.n = std::max(r.n, i + j + 1);
		r.num[i + j] += num[i] * z.num[j] + c;
		c = r.num[i + j] / N;
		r.num[i + j] %= N;
	    }
	}
#if DB >= 1
	fprintf(stderr, "res  = ");
	r.output();
	fprintf(stderr, "\n");
#endif
	*this = r;
    }
    /*
    {
	long long c = 0;
	for (int i = 0; i < n || c; ++i)
	{
	    n = std::max(n, i + 1);
	    num[i] = num[i] * z + c;
	    c = num[i] / N;
	    num[i] %= N;
	}
    }
    */

    void output() const
    {
	printf("%lld", num[n - 1]);
	for (int i = n - 2; i >= 0; --i)
	    printf("%09lld", num[i]);
	printf("\n");
    }
private:
    static const int N = 1000000000;
    int n;
    long long num[3333];
};

Int powernomod(Int cur, int n)
{
    Int ret;
    ret.setto1();
    for (; n; n >>= 1)
    {
	if (n & 1)
	    ret *= cur;
	cur *= cur;
    }
    return ret;
}

const int maxn = 50007;
const int maxp = 5557;
const int maxpf = 7;
const int maxf = 137;
int n;
int p[maxp], pc;
int lpf[maxn], pre[maxn], cnt[maxn];
int pfac[maxpf], ppow[maxpf], pfc;
int fac[maxf], fc;
Int ans;
long double ansd = 1e1000l;

void init()
{
    static int not_p[maxn / 32 + 1];
    for (int i = 2; i <= n; ++i)
    {
	if (!(not_p[i / 32] >> i % 32 & 1))
	    p[pc++] = i, lpf[i] = i, pre[i] = 1, cnt[i] = 1;
	for (int j = 0, bdry = n / i; p[j] <= bdry; ++j)
	{
	    const int z = p[j] * i;
	    not_p[z / 32] |= 1 << z % 32;
	    lpf[z] = p[j];
	    if (p[j] == lpf[i])
	    {
		pre[z] = pre[i];
		cnt[z] = cnt[i] + 1;
		break;
	    }
	    else
	    {
		pre[z] = i;
		cnt[z] = 1;
	    }
	}
    }
}

void mkpfac()
{
    for (int x = n; x != 1; x = pre[x], ++pfc)
    {
	pfac[pfc] = lpf[x];
	ppow[pfc] = cnt[x];
    }
}

void dfs(int f, int d)
{
    if (d == pfc)
    {
	if (f != 1)
	    fac[fc++] = f;
	return;
    }
    dfs(f, d + 1);
    for (int i = 1; i <= ppow[d]; ++i)
	dfs(f *= pfac[d], d + 1);
}

void search(int num, int d, const int limit, long double now = 1)
{
    static int power[maxf];
    if (num == 1)
    {
	static Int z;
	z.setto1();
	for (int i = 0; i < d; ++i)
	    z *= powernomod(p[i], power[i]);
	if (z < ans)
	{
	    ans = z;
	    ansd = now;
	}
	return;
    }
    for (int i = 0; i < fc && fac[i] <= limit; ++i)
	if (num % fac[i] == 0)
	{
	    power[d] = fac[i] - 1;
	    long double z = now;
	    z *= powl(log(p[d]), power[d]);
	    if (z > ansd)
		continue;
	    search(num / fac[i], d + 1, fac[i], z);
	}
}

int main()
{
    scanf("%d", &n);
    init();
    mkpfac();
    dfs(1, 0);
    std::sort(fac, fac + fc);
    search(n, 0, ~0u >> 1);
    ans.output();
}
