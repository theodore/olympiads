#include <cstdio>
#include <cstdlib>

const int maxn = 303;

int main()
{
    int n, m, r;
    static bool map[maxn][maxn];
    scanf("%d%d%d", &n, &m, &r);
    srand(r);
    printf("%d %d\n", n, m);
    for (int i = 0; i < n; ++i)
	printf("%d ", rand() & 1);
    putchar('\n');
    for (int i = 0, a, b; i < m; ++i)
    {
	do {
	    a = rand() % n + 1;
	    b = rand() % n + 1;
	} while (a == b || map[a][b]);
	map[a][b] = map[b][a] = true;
	printf("%d %d\n", a, b);
    }
}
