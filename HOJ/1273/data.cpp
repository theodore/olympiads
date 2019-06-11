#include <cstdio>
#include <cstdlib>

int main()
{
    int n, m, r, mod;
    scanf("%d%d%d%d", &n, &m, &mod, &r);
    srand(r);
    printf("%d %d\n", n, m);
    for (int i = 0; i < n; i++)
        printf("%d\n", rand() % mod);
    for (int i = 0; i < m; i++)
        if (rand() & 1)
            printf("A %d\n", rand() % mod);
        else
            printf("Q %d\n", rand() % 16);
}
