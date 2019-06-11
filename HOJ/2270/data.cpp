#include <cstdio>
#include <cstdlib>

int main()
{
    int t, n, m, r;
    scanf("%d%d%d%d", &t, &n, &m, &r);
    srand(r);
    while (t--) {
        printf("%d %d\n", n, m + n - 1);
        for (int i = 1; i < n; i++)
            printf("%d %d\n", rand() % i, i);
        for (int i = 0; i < m; i++) {
            int a, b;
            do {
                a = rand() % n;
                b = rand() % n;
            } while (a == b);
            printf("%d %d\n", a, b);
        }
        puts("");
    }
    puts("0 0");
}
