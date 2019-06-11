#include <cstdio>
#include <cstdlib>

const int mod = 10000;

int main()
{
    int n, r;
    scanf("%d%d", &n, &r);
    srand(r);
    for (printf("%d\n", n); n--; )
	printf("%d %d\n", rand() % mod, rand() % mod);
}
