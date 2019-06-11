#include <cstdio>
#include <cstdlib>

const int mod = 10;

int main()
{
    int n, m, r;
    scanf("%d%d%d", &n, &m, &r);
    srand(r);
    printf("%d %d\n", n, m);
    for (int i = 0; i < n; ++i)
        printf("%d ", rand() % mod);
    puts("");
    while (m--)
        printf("%d %d %d\n", rand() % n + 1, rand() % n + 1, rand() % mod);
}
