#include <cstdio>
#include <cstdlib>

int main()
{
    int n, r;
    scanf("%d%d", &n, &r);
    srand(r);
    printf("%d\n", n);
    int m = n * 2 / 3;
    for (int i = 0; i < n; i++)
        printf("%d %d\n", rand() % m, rand() % m);
}
