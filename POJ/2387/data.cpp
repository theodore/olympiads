#include <cstdio>
#include <cstdlib>
#include <ctime>

int main()
{
	int n, m, r;
	int mod(100);
	scanf("%d%d%d", &n, &m, &r);
	srand(n * m * r * time(0));
	printf("%d %d\n", m + n - 1, n);
	for (int i = 2; i <= n; ++i)
	{
		printf("%d %d %d\n", i, rand() % (i - 1) + 1, rand() % mod + 1);
	}
	while (m--)
		printf("%d %d %d\n", rand() % n + 1, rand() % n + 1, rand() % mod + 1);
	return 0;
}
