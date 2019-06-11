#include <cstdio>
#include <cstdlib>

int shuffle(const void*, const void*)
{
    int a[] = {-1, 1};
    return a[rand() & 1];
}

int main()
{
    int n, r;
    int a[103];
    scanf("%d%d", &n, &r);
#ifdef DB
    fprintf(stderr, "%d %d read\n", n, r);
#endif
    srand(r);
    for (int i = 0; i < n; ++i)
	a[i] = i;
    qsort(a, n, 4, shuffle);
    printf("%d\n", n);
    for (int i = 0; i < n - 1; ++i)
	printf("%d ", a[i]);
    printf("%d\n", a[n - 1]);
}
