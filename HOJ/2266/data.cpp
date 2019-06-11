#include <cstdio>
#include <cstdlib>

char c[] = "#.";

int main()
{
    int n, m, r, t, nn, mm;
    scanf("%d%d%d%d", &t, &nn, &mm, &r);
    srand(r);
    for (printf("%d\n", t); t--; )
    {
	printf("%d %d\n", n = rand() % nn + 23, m = rand() % mm + 84);
	for (int i = 0; i < n; ++i, puts(""))
	    for (int j = 0; j < m; ++j)
		putchar(c[rand() & 1]);
    }
}
