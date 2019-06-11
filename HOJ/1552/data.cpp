#include <cstdio>
#include <cstdlib>
#include <ctime>

int main()
{
	freopen("in", "w", stdout);
	int n, m, r;
	scanf("%d%d%d", &r, &n, &m);
	srand(time(0) * n / m * time(0) * r);
	printf("%d\n", n);
	for (int i = 0; i < n; ++i)
		printf("%d ", rand() % m);
	putchar(10);
	return 0;
}
