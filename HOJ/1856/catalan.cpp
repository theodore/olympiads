#include <cstdio>

const int p(20100403);
int n, m;

long long power_mod(long long a, int n)
{
	long long ret = 1;
	long long cur = a;
	while (n)
	{
		if (n & 1)
			ret = ret * cur % p;
		cur = cur * cur % p;
		n >>= 1;
	}
	return ret;
}

int main()
{
	scanf("%d%d", &m, &n);
	if (m < n)
	{
		printf("0\n");
		return 0;
	}
	long long ago = 1;
	long long fn = 1, fm;
	for (int i = 2; i <= n; ++i)
		fn = fn * i % p;
	fm = fn;
	for (int i = n + 1; i <= m; ++i)
		fm = fm * i % p;
	ago = fm;
	for (int i = m + 1; i <= n + m; ++i)
		ago = ago * i % p;
	ago *= m + 1 - n;
	ago %= p;
	fn = fn * fm % p;
	fn = fn * (m + 1) % p;
#ifdef DB
	fprintf(stderr, "%lld\n%lld\n", t, power_mod(t, p - 2));
#endif
	ago = ago * power_mod(fn, p - 2) % p;
	printf("%I64d\n", ago);
	return 0;
}
