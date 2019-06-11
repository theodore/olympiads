#include <cstdio>
#include <cstdlib>
#include <algorithm>

int main()
{
    int n, m, mod, r;
    scanf("%d%d%d%d", &n, &m, &mod, &r);
    srand(r);
    for (int i = 0; i < n; i++)
        putchar('a' + rand() % mod);
    puts("");
    printf("%d\n", m);
    while (m--) {
        if (rand() & 1) {
            int a = rand() % n + 1;
            int b = rand() % n + 1;
            if (a > b)
                std::swap(a, b);
            printf("Q %d %d\n", a, b);
        } else if (rand() & 1) {
            printf("I %d %c\n", rand() % (n + 1), 'a' + rand() % 3);
        } else {
            printf("R %d %c\n", rand() % n + 1, 'a' + rand() % 3);
        }
    }
}
