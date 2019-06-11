#include <cstdio>
#include <cmath>
#include <cassert>

const int maxn = 100000007;
const int maxp = 50848007;
//const int maxn = 100007;
//const int maxp = 5007;
int n;
int p[maxp], pc;
int pre[maxn], cnt[maxn];

#define not_P(x) (not_p[(x) >> 5] >> ((x) & 31) & 1)

void mkp()
{
    static int not_p[maxn / 32 + 1];
    pc = 1;
    p[0] = 2;
    for (int i = 3; i <= n; i += 2)
    {
	if (!not_P(i))
	    p[pc++] = i, pre[i] = 0, cnt[i] = 1;
	for (int j = 1, lim = n / i; p[j] <= lim; ++j)
	{
	    not_p[(p[j] * i) >> 5] |= 1 << (p[j] * i & 31);
	    if (!(i % p[j]))
	    {
		pre[p[j] * i] = pre[i];
		cnt[p[j] * i] = cnt[i] + 1;
		break;
	    }
	    else
	    {
		pre[p[j] * i] = i;
		cnt[p[j] * i] = 1;
	    }
	}
    }
}

void factorize(int x, int& npf, int& nf)
{
    if (~x & 1)
    {
	int c = 1;
	while (++c, x >>= 1, ~x & 1)
	    ;
	if (x == 1)
	{
	    npf = 1;
	    nf = c;
	}
	else
	{
	    factorize(x, npf, nf);
	    ++npf;
	    nf *= c;
	}
    }
    else if (pre[x] == 0)
    {
	npf = 1;
	nf = cnt[x] + 1;
    }
    else
    {
	factorize(pre[x], npf, nf);
	++npf;
	nf *= cnt[x] + 1;
    }
}

int main()
{
    scanf("%d", &n);
    assert(n <= maxn);
    mkp();
    int nf = 0, npf = 0;
    for (int i = 2; i <= n; ++i)
    {
	int a, b;
	factorize(i, a, b);
#if DB >= 1
	fprintf(stderr, "%d: %d %d\n", i, a, b);
#else
	if (a > npf)
	    printf("%d: npf = %d\n", i, npf = a);
	if (b > nf)
	    printf("%d: nf  = %d\n", i, nf = b);
#endif
    }
}
