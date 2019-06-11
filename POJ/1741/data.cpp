#include <cstdio>
#include <cstdlib>

const int mod = 70;
int n, m, r;

int main()
{
	int mode;
	scanf("%d%d%d%d", &mode, &n, &m, &r);
	srand(n * m * r);
	printf("%d %d\n", n, m);
	if (mode == 1)
		for (int i = 2; i <= n; ++i)
			printf("1 %d %d\n", i, rand() % mod);
	if (mode == 2)
		for (int i = 2; i <= n; ++i)
			printf("%d %d %d\n", i - 1, i, rand() % mod);
	else
		for (int i = 2; i <= n; ++i)
			printf("%d %d %d\n", i, rand() % (i - 1) + 1, rand() % mod);
	printf("0 0\n");
}
