#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n, a, b, r;
    scanf("%d%d%d%d", &n, &a, &b, &r);
    srand(r);
    printf("%d\n", n);
    for (int i = 0, x = 0; i < n; i++) {
        x += rand() % a + 1;
        printf("%d %d\n", x, rand() % b);
    }
}
