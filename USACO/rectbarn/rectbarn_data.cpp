#include <cstdio>
#include <cstdlib>

int max(int a, int b)
{
	return a > b ? a : b;
}

bool bad[100][100];

int main()
{
	freopen("rectbarn.in", "w", stdout);
	int n, m;
	scanf("%d%d", &n, &m);
	srand(n * m);
	for (int i = 0; i < max(n, m) + 5; ++i)
		bad[rand()%n+1][rand()%m+1] = true;
	int p(0);
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
			p += bad[i][j];
	printf("%d %d %d\n", n, m, p);
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
			if (bad[i][j])
				printf("%d %d\n", i, j);
	return 0;
}
