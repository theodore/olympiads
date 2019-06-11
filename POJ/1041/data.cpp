#include <cstdio>
#include <cstdlib>
#include <cstring>

int main()
{
	int n, r, mod, m;
	scanf("%d%d%d%d", &n, &m, &mod, &r);
	srand(n * r);
	int* deg = new int [n + 3];
	memset(deg, 0, 4 * n + 12);
	for (int i = 2; i <= n; ++i)
	{
		int t = rand() % (i - 1) + 1;
		++deg[t];
		++deg[i];
		printf("%d %d %d\n", t, i, rand() % mod);
	}
	for (int i = 0; i < m; ++i)
	{
		int a = rand() % n + 1;
		int b = rand() % n + 1;
		++deg[a];
		++deg[b];
		printf("%d %d %d\n", a, b, rand() % mod);
	}
	for (int i = 1; i <= n; ++i)
		if (deg[i] & 1)
			for (int j = i + 1; j <= n; ++j)
				if (deg[j] & 1)
				{
					++deg[j];
					printf("%d %d %d\n", i, j, rand() % mod);
					break;
				}
	printf("0 0 0 0\n");
}
