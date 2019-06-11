#include <cstdio>
#include <cstdlib>

const int dist_mod = 5;
const int mod = 10;

int main()
{
    int n, m, r;
    scanf("%d%d%d", &n, &m, &r);
    srand(r);
    printf("%d %d\n", n, m);
    for (int i = 1, s = 0; i < n; i++)
        printf("%d ", s += rand() % dist_mod + 1);
    puts("");
    for (int i = 0; i < 3; i++, puts(""))
        for (int j = 0; j < n; j++)
            printf("%d ", rand() % mod);
}
