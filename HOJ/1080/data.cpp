#include <cstdio>
#include <cstdlib>

void gen(const int x)
{
    int a;
    for (int i = 0; i < x; ++i)
    {
	putchar(a = '0' + (rand() & 1));
	fprintf(stderr, "%c", a);
    }
    putchar('\n');
    fprintf(stderr, "\n");
}

int main()
{
    int n, m, r;
    scanf("%d%d%d", &n, &m, &r);
    srand(r);
    printf("%d\n", n);
    for (int i = 0; i < n; ++i)
	gen(rand() % m + 1);
}
