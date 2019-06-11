#include <cstdio>
#include <cstdlib>
#include <ctime>

int main()
{
	freopen("in", "w", stdout);
	int r, n, m, mod;
	scanf("%d%d%d%d", &r, &n, &m, &mod);
	srand(r * n * m * time(0));
	printf("%d %d\n", n, m);
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < m - 1; ++j)
			printf("%d ", rand() % mod + 1);
		putchar(10);
	}
	for (int i = 0; i < n - 1; ++i)
	{
		for (int j = 0; j < m; ++j)
			printf("%d ", rand() % mod + 1);
		putchar(10);
	}
	for (int i = 0; i < n - 1; ++i)
	{
		for (int j = 0; j < m - 1; ++j)
			printf("%d ", rand() % mod + 1);
		putchar(10);
	}
	return 0;
}
