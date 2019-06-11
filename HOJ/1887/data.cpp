#include <cstdio>
#include <cstdlib>
#include <ctime>

int main()
{
	int n, mod, r;
	scanf("%d%d%d", &n, &mod, &r);
	srand(n * mod * r * time(0));
	printf("%d\n", n);
	for (int i = 2; i <= n; ++i)
	{
		//printf("%d %d %d\n", i - 1, i, 1000);
		printf("%d %d %d\n", rand() % (i-1) + 1, i, rand() % mod +1);
	}
	return 0;
}
