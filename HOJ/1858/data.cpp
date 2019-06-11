#include <cstdio>
#include <cstdlib>
#include <ctime>

int main()
{
	freopen("in", "w", stdout);
	int n, m, r;
	scanf("%d%d%d", &r, &n, &m);
	srand(r * n * m * time(0) * time(0));
	printf("%d %d\n", n, m);
	for (int i = 0; i < n; ++i)
		printf("%d ", rand() & 1);
	putchar(10);
	for (int i = 1; i < m; ++i)
	{
		int a = rand() % 5;
		int b = rand() % n;
		int c = rand() % n;
		if (b > c)
		{
			b ^= c;
			c ^= b;
			b ^= c;
		}
		printf("%d %d %d\n", a, b, c);
	}
	int a = rand() % n;
	int b = rand() % n;
	if (a > b)
	{
		a ^= b;
		b ^= a;
		a ^= b;
	}
	printf("%d %d %d\n", rand() % 2 + 3, a, b);
	return 0;
}
