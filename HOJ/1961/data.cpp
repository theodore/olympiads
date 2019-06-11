#include <cstdio>
#include <cstdlib>

int main()
{
	int n, m, r;
	scanf("%d%d%d", &n, &m, &r);
	srand(r);
	for (printf("%d\n", n); n--; )
		printf("%d ", rand() % m + 1);
	printf("\n");
}
