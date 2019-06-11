#include <cstdio>
#include <cstdlib>

const int mod = 100;

int main()
{
    int n, m, r;
    scanf("%d%d%d", &n, &m, &r);
    srand(r);
    printf("%d\n", n);
    for (int i = 0; i < n; ++i)
	printf("%d ", rand() % mod);
    for (printf("\n%d\n", m); m--; )
    {
	int a, b;
	do
	{
	    a = rand() % n + 1;
	    b = rand() % n + 1;
	} while (a == b);
	printf("%d %d\n", a, b);
    }
}
