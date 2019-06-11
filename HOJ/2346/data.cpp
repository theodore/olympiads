#include <cstdio>
#include <cstdlib>

int main()
{
    int n, m, r;
    char c[] = "\\/";
    scanf("%d%d%d", &n, &m, &r);
    srand(r);
    printf("%d %d\n", n, m);
    for (int i = 0; i < n; i++, puts(""))
        for (int j = 0; j < n; j++)
            putchar(c[rand() & 1]);
}
