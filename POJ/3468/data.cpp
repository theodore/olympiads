#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

int main()
{
    int n, q, m, r;
    scanf("%d%d%d%d", &n, &q, &m, &r);
    srand(r);
    printf("%d %d\n", n, q);
    for (int i = 0; i < n; i++)
        printf("%d ", rand() % m - m / 2);
    puts("");
    while (q--) {
        int l = rand() % n + 1;
        int r = rand() % n + 1;
        if (l > r)
            std::swap(l, r);
        if (rand() & 1)
            printf("Q %d %d\n", l, r);
        else
            printf("C %d %d %d\n", l, r, rand() % m - m / 2);
    }
}
