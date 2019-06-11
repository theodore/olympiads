#include <cstdio>
#include <cstdlib>
#include <algorithm>

int main()
{
    int n, m, r;
    scanf("%d%d%d", &n, &m, &r);
    srand(r);
    printf("%d %d\n", n, m);
    for (int i = 0; i < n; ++i)
        putchar((rand() & 1) ? '(' : ')');
    puts("");
    while (m--) {
        int a = rand() % n + 1;
        int b = rand() % n + 1;
        if (a > b)
            std::swap(a, b);
        int c = rand() % 3;
        if (!c && ((b + 1 - a) & 1)) {
            if (b < n)
                ++b;
            else
                -- b;
        }
        printf("%d %d %d\n", c, a, b);
    }
}
