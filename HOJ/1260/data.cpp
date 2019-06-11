#include <cstdio>
#include <cstdlib>

int main()
{
    int n, m, r;
    scanf("%d%d%d", &n, &m, &r);
    srand(r);
    while (n--)
        putchar('A' + rand() % m);
    puts("");
}
