#include <cstdio>

int main()
{
	int ans(0), n, a, b, c;
	scanf("%d", &n);
	while (--n)
	{
		scanf("%d%d%d", &a, &b, &c);
		ans ^= c;
	}
	printf("%d\n", ans);
	return 0;
}
