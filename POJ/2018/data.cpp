#include <cstdio>
#include <cstdlib>

const int mod = 100;

int main()
{
	int n, m, r;
	scanf("%d%d%d", &n, &m, &r);
	srand(n * m * r);
	printf("%d %d\n", n, m);
	for (int i = 0; i < n; ++i)
		printf("%d\n", rand() % mod);
}
