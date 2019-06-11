#include <cstdio>
#include <cstdlib>

int main()
{
    int n, m, r;
    char c[] = "mh";
    scanf("%d%d%d", &n, &m, &r);
    srand(r);
    puts("10");
    for (int i = 0; i < 10; i++) {
        printf("%d %d\n", n, m);
        for (int j = 0; j < m; j++)
            printf("%c%d %c%d\n", c[rand() & 1], rand() % n + 1, c[rand() & 1],
                    rand() % n + 1);
    }
}
