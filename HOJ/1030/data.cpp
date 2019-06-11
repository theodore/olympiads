#include <cstdio>
#include <cstdlib>

int main()
{
    int n, m, r;
    int mod = 4;
    scanf("%d%d%d", &n, &m, &r);
    srand(r);
    printf("%d %d\n", n, m);
    for (int i = 0; i < n; ++i)
    {
	int z = rand() % 5 + 1;
	for (int i = 0; i < z; ++i)
	    putchar('A' + rand() % mod);
	putchar('\n');
    }
}
