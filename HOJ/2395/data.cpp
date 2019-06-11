#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n, m, r, mod;
    scanf("%d%d%d%d", &n, &m, &mod, &r);
    srand(r);
    printf("%d %d\n", n, m);
    for (int i = 1; i < n; i++)
        printf("%d %d %d %d\n",
                rand() % i, i, rand() % mod + 1, rand() % mod + 1);
    m -= n - 1;
    while (m--) {
        int a = rand() % n, b = rand() % n;
        while (a == b)
            b = rand() % n;
        printf("%d %d %d %d\n", a, b, rand() % mod + 1, rand() % mod + 1);
    }
}
