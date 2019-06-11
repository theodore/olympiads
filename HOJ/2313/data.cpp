#include <cstdio>
#include <cstdlib>

int n, m, r;

int main()
{
    scanf("%d%d%d", &n, &m, &r);
    srand(r);
    puts("10");
    for (int i = 0; i < 10; ++i)
	printf("%d %d\n", rand() % n + 1, rand() % m + 1);
}
