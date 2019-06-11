#include <cstdio>
#include <cstdlib>

int R()
{
    return rand() % 100 + 1;
}

int main()
{
    int n, r;
    scanf("%d%d", &n, &r);
    srand(r);
    r = rand() % 5 + 1;
    if (r > 3)
	r = 3;
    printf("%d %d\n", n, r);
    for (int i = 0; i < n; ++i)
	printf("%d %d %d\n", R(), R(), R());
}
