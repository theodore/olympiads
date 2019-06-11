#include <cstdio>
#include <cstdlib>

const int maxn = 200003;
int hash[maxn];
const int mod = 100;

int main()
{
	int mode;
	int n, m, k, r;
	scanf("%d%d%d%d%d", &mode, &n, &m, &k, &r);
	srand(n * m * k * r);
	printf("%d %d %d\n", n, m, k);
	for (int i = 0; i < k; ++i)
	{
		int x;
		do
			x = rand() % n + 1;
		while (hash[x]);
		hash[x] = true;
		printf("%d\n", x);
	}
	if (mode == 1)
		for (int i = 2; i <= n; ++i)
			printf("1 %d %d\n", i, rand() % mod);
	else if (mode == 2)
		for (int i = 2; i <= n; ++i)
			printf("%d %d %d\n", i - 1, i, rand() % mod);
	else
		for (int i = 2; i <= n; ++i)
			printf("%d %d %d\n", i, rand() % (i - 1) + 1, rand() % mod - mod / 2);
}
