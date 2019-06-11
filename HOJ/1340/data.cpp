#include <cstdio>
#include <cstdlib>

int main()
{
    int w, l, n, r;
    scanf("%d%d%d%d", &l, &w, &n, &r);
    srand(r);
    printf("%d %d %d\n", l, w, n);
    for (int i = 0; i < n; ++i)
	printf("%d %d\n", rand() % l, rand() % w);
}
