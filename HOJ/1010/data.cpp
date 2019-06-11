#include <cstdio>
#include <cstdlib>

int main()
{
    int n, l, mod, r;
    scanf("%d%d%d%d", &n, &l, &mod, &r);
    srand(r);
    printf("%d %d\n", n, l);
    for (int i = 0; i < n; i++)
        printf("%d ", rand() % mod + 1);
    puts("");
}
