#include <cstdio>
#include <cstdlib>
#include <ctime>

int n, k, t, r;

int main()
{
	scanf("%d%d%d%d", &n, &k, &t, &r);
	srand(n * k * t * r * time(0));
	printf("%d %d %d\n", n, k, t);
	for (int i = 0; i < n; ++i)
		printf("%d ", rand() % (t + 1));
	putchar('\n');
	for (int i = 0; i < n; ++i)
		printf("%d ", rand() % 300);
	putchar('\n');
	for (int i = 0; i < n; ++i)
		printf("%d ", rand() % k + 1);
	putchar('\n');
	return 0;
}
