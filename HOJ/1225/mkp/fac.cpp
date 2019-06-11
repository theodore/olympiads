#include <cstdio>
#include <cmath>
#include <cassert>

//const int maxn = 100000007;
//const int maxp = 50848007;
const int maxn = 100007;
const int maxp = 5007;
int n;
int p[maxp], pc;
int pre[maxn], cnt[maxn];
int prm[maxn];

#define not_P(x) (not_p[(x) >> 5] >> ((x) & 31) & 1)

void mkp()
{
    static int not_p[maxn / 32 + 1];
    pc = 1;
    p[0] = 2;
    for (int i = 3; i <= n; i += 2)
    {
	if (!not_P(i))
	    p[pc++] = i, pre[i] = 0, cnt[i] = 1, prm[i] = i;
	for (int j = 1, lim = n / i; p[j] <= lim; ++j)
	{
	    not_p[(p[j] * i) >> 5] |= 1 << (p[j] * i & 31);
	    prm[p[j] * i] = p[j];
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

//void factorize(int x, int& npf, int& nf)
void factorize(int x)
{
#if DB >= 1
    fprintf(stderr, "x = %d\n", x);
#endif
    if (~x & 1)
    {
	int c = 0;
	while (++c, x >>= 1, ~x & 1)
	    ;
	if (x == 1)
	{
	    printf("2^%d", c);
	}
	else
	{
	    printf("2^%d ", c);
	    factorize(x);
	}
    }
    else if (pre[x] == 0)
    {
	printf("%d^%d\n", prm[x], cnt[x]);
    }
    else
    {
	printf("%d^%d ", prm[x], cnt[x]);
	factorize(pre[x]);
    }
}

int main()
{
    scanf("%d", &n);
    assert(n <= maxn);
    mkp();
    factorize(n);
    //putchar('\n');
}
