#include <cstdio>
#include <cstdlib>

int main()
{
    int n, r;
    int mod;
    scanf("%d%d%d", &n, &mod, &r);
    srand(r);
    printf("%d\n", n);
    while (n--)
	printf("%d ", rand() % mod);
    printf("\n");
}
