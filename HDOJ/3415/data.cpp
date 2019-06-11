#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n, k, m, r;
    scanf("%d%d%d%d", &n, &k, &m, &r);
    srand(r);
    printf("1\n%d %d\n", n, k);
    for (int i = 0; i < n; i++)
        printf("%d ", rand() % m - m / 2);
    puts("");
}
