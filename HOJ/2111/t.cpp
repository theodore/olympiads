#include <cstdio>

typedef long long int Bignum_t;

const int N_MAX = 1000000;
int n, mod;
int ways[N_MAX + 1];
int factorial[N_MAX];
int inv_fact[N_MAX];
int power_mod(int a, int b, int mod)
{
    int ret = 1;
    while (b)
    {
	if (b & 1)
	    ret = (Bignum_t)ret * a % mod;
	a = (Bignum_t)a * a % mod;
	b >>= 1;
    }
    return ret;
}

int inverse_fatorial(int n)
{
    if (inv_fact[n])
	return inv_fact[n];
    return inv_fact[n] = power_mod(factorial[n], mod - 2, mod);
}

int C(int n, int m)
{
    return (Bignum_t)factorial[n]
	* inverse_fatorial(m) % mod
	* inverse_fatorial(n - m) % mod;
}

int Ways(int n)
{
    int &ans = ways[n];
    if (ans)
	return ans;
    int l, r, size = 1;
    while (size * 2 + 1 <= n)
	size = size * 2 + 1;
    int size0 = (size + 1) >> 1;
    if (size + size0 >= n)
	r = size >> 1, l = n - 1 - r;
    else l = (size >> 1) + size0, r = n - 1 - l;
    ans = (Bignum_t)C(n -1, l)
	* Ways(l) % mod
	* Ways(r) % mod;
    return ans;
}

int main()
{
    scanf("%d%d", &n, &mod);
    factorial[0] = 1;
    for (int i = 1; i <= n; i ++)
	factorial[i] = (Bignum_t)factorial[i - 1] * i % mod;
    ways[0] = ways[1] = 1;
    printf("%d\n", Ways(n));
#if DB & 1
    for (int i = 1; i <= 20; ++i)
	fprintf(stderr, "%d\n", Ways(i));
#endif
    return 0;
}
