#include <cstdio>
#include <cstdlib>

int mod = 100;

int main()
{
    int n, r;
    scanf("%d%d", &n, &r);
    srand(r);
    printf("%d\n", n);
    for (int i = 0; i < n; ++i)
	printf("%d %d\n", rand() % mod - mod / 2, rand() % mod - mod / 2);
}
