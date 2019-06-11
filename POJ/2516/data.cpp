#include <cstdio>
#include <cstdlib>

const int maxn = 53;
int n, m, k, r;

void out(const int a, const int b, const int c, const int d)
{
	for (int i = 0; i < a; ++i)
	{
		for (int j = 0; j < b; ++j)
			printf("%d ", rand() % c + d);
		printf("\n");
	}
}

int main()
{
	scanf("%d%d%d%d", &n, &m, &k, &r);
	srand(r);
	printf("%d %d %d\n", n, m, k);
	out(n, k, 4, 0);
	out(m, k, 4, 0);
	for (int i = 0; i < k; ++i)
		out(n, m, 99, 1);
	printf("0 0 0\n");
}
