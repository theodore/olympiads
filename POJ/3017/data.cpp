#include <cstdio>
#include <cstdlib>

int main()
{
    int n, m, r;
    scanf("%d%d%d", &n, &m, &r);
    srand(r);
    printf("%d %d\n", n, m);
    for (int i = 0; i < n; ++i)
	printf("%d ", rand() % 10);//(m / (rand() % 10 + 1) + 1));
    printf("\n");
}
