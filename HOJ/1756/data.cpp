#include <cstdio>
#include <cstdlib>
#include <ctime>

int main()
{
	freopen("in", "w", stdout);
	int r, n, m;
	scanf("%d%d%d", &r, &n, &m);
	srand(r * time(0));
	printf("%d %d\n", n, m);
	for (int i = 0; i < n; ++i)
		printf("%d ", rand() % 2000 - 1000);
	while (m--)
	{
		int a = rand() & 1, b = rand(), c = rand();
		if (++a == 1)
		{
			b = b % n + 1;
			c = c % n + 1;
			if (b > c)
			{
				a = b;
				b = c;
				c = a;
			}
			printf("1 %d %d\n", b, c);
		}
		else
		{
			b = b % n + 1;
			c = c % 2000 - 1000;
			printf("2 %d %d\n", b, c);
		}
	}
	return 0;
}
