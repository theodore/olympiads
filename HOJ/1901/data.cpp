#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <algorithm>

int main()
{
	freopen("in", "w", stdout);
	int n, m, r, l;
	scanf("%d%d%d%d", &r, &n, &m, &l);
	srand(r * n * m * l * time(0));
	printf("%d %d", n, m);
	for (int i = 0; i < n; ++i)
	{
		if (i % 10 == 0)
			putchar(10);
		printf("%d ", rand() % l);
	}
	putchar(10);
	putchar(10);
	while (m--)
	{
		if (rand() & 1)
		{
			printf("C %d %d\n", rand() % n + 1, rand() % l);
		}
		else
		{
			int a, b, c;
			a = rand() % n + 1;
			b = rand() % n + 1;
			if (a > b)
				std::swap(a, b);
			if (b == a)
				c = 1;
			else
				c = rand() % (b - a) + 1;
			printf("Q %d %d %d\n", a, b, c);
		}
	}
}
