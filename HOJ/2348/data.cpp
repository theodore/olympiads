#include <cstdio>
#include <cstdlib>

int main()
{
    int n, m, r;
    scanf("%d%d%d", &n, &m, &r);
    srand(r);
    printf("%d\n", n);
    while (n--)
        printf("%d ", rand() % m);
    puts("");
}
