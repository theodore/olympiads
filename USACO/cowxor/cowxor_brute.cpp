#include <cstdio>

int main()
{
	freopen("cowxor.in", "r", stdin);
	freopen("cowxor.ans", "w", stdout);
	int n, a[100];
	scanf("%d", &n);
	a[0] = 0;
	for (int i = 1; i <= n; ++i)
	{
		scanf("%d", &a[i]);
		a[i] ^= a[i-1];
	}
	int l(1), r(1);
	for (int i = 1; i <= n; ++i)
		for (int j = i; j > 0; --j)
			if ((a[l-1] ^ a[r]) < (a[j-1] ^ a[i]))
			{
				l = j;
				r = i;
			}
#ifdef DB
	printf("l = %d, r = %d\n", l, r);
#endif
	printf("%d %d %d\n", a[l-1] ^ a[r], l, r);
	return 0;
}
