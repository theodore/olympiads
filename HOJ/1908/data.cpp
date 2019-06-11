#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n, m, r;
    scanf("%d%d%d", &n, &m, &r);
    printf("%d 1\n", n);
    for (int i = 0; i < n; i++)
        printf("%d ", rand() % m);
    puts("");
    for (int i = 2; i <= n; i++)
        printf("%d %d\n", rand() % (i - 1) + 1, i);
    puts("0 0");
}
