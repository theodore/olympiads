#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n, k, r;
    scanf("%d%d%d", &n, &k, &r);
    srand(r);
    printf("%d %d\n", n, k);
    for (int i = 0; i < n; i++, puts(""))
        for (int j = 0; j < n; j++)
            putchar(rand() % 4 ? 'N' : 'Y');
}
