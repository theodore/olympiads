#include <cstdio>
#include <cstdlib>

int main()
{
    int n, m, r;
    scanf("%d%d%d", &n, &m, &r);
    srand(r);
    printf("%d\n", n);
    for (int i = 0; i < n; ++i)
	printf("%d %d\n", rand() % 100 + 1, rand() % m + 1);
}
