#include <cstdio>
#include <cstdlib>

const int mod = 10;

int main()
{
    int n, m, k, r;
    scanf("%d%d%d%d", &n, &m, &k, &r);
    srand(r);
    printf("%d %d\n", n, m);
    for (int i = 0; i < m; ++i)
	printf("%d %d %d\n", rand() % n + 1, rand() % n + 1, rand() % mod);
    printf("%d %d %d\n", rand() % n + 1, rand() % n + 1, k);
}
