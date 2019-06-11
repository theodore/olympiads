#include <cstdio>
#include <cstdlib>

int main()
{
    int t, n, r;
    scanf("%d%d%d", &t, &n, &r);
    srand(r);
    for (printf("%d\n", t); t--; ) {
        printf("%d\n", n);
        for (int i = 0; i < n; i++, puts(""))
            for (int j = 0; j < n; ++j)
                printf("%d ", rand() & 1);
    }
}
