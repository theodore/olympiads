#include <cstdio>
#include <cstdlib>

const int mod = 10000;
int n, m, r;

int main()
{
	scanf("%d%d%d", &n, &m, &r);
	printf("%d %d\n", n, m);
	srand(r);
	for (int i = 0; i < n; ++i)
		printf("%d\n", rand() % mod - mod / 2);
	for (int i = 0; i < m; ++i)
	{
		int a = rand() % n + 1;
		int b;
		do
			b = rand() % n + 1;
		while (a == b);
		printf("%d %d\n", a, b);
	}
}
