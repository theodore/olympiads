#include <cstdio>
#include <cstdlib>

int A = 31;
int B = 15;
int C = 183;

int main()
{
    int n, r, mod;
    scanf("%d%d%d", &n, &mod, &r);
    srand(r);
    srand(rand());
    n = rand() % n + 5;
    mod = rand() % mod + 10;
    printf("%d %d %d %d\n", n, rand() % A + 2, rand() % B + 3, rand() % C + 10);
    for (int i = 0; i < n; ++i)
	printf("%d %d\n", rand() % mod, rand() % mod);
}
