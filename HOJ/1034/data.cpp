#include <cstdio>
#include <cstdlib>

int main()
{
    int n, m, r;
    scanf("%d%d%d", &n, &m, &r);
    srand(r);
    printf("%d\n", n);
    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < n; ++j)
            printf("%d\n", rand() % m);
}
