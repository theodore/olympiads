#include <cstdio>
#include <cstdlib>

const int mod = 2320;

int main()
{
    int n, m, r;
    scanf("%d%d%d", &n, &m, &r);
    srand(r);
    printf("%d\n", n);
    for (int i = 0; i < n; ++i)
	printf("%d ", rand() % mod - mod / 2);
    printf("\n%d\n", m);
    for (int i = 0; i < m; ++i)
    {
	int a, b;
	do {
	    a = rand() % n + 1;
	    b = rand() % n + 1;
	} while (a == b);
	if (a > b)
	    a ^= b, b ^= a, a ^= b;
	printf("%d %d\n", a, b);
    }
}
