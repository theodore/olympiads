#include <cstdio>
#include <cstdlib>

const int color = 3;
int n, m, r;

int R()
{
    return rand() % n + 1;
}

int main()
{
    scanf("%d%d%d", &n, &m, &r);
    srand(r);
    printf("%d %d\n", n, m);
    for (int i = 0; i < n; ++i)
	printf("%d ", rand() % color + 1);
    printf("\n");
    for (int i = 2; i <= n; ++i)
	printf("%d %d\n", rand() % (i - 1) + 1, i);
    while (m--)
    {
	if (rand() & 1)
	    printf("Q %d %d\n", R(), R());
	else
	    printf("C %d %d %d\n", R(), R(), rand() % color + 1);
    }
}
