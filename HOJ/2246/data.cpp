#include <cstdio>
#include <cstdlib>

char s[37][37];
const int mod = 100;
int n, m, k, h, r;

void put(char x)
{
    for (int i = 0; i < rand() % 15 + 20; ++i)
	s[rand() % n][rand() % m] = x;
}

void putc(char x, int z)
{
    for (int i = 0; i < z; ++i)
	s[rand() % n][rand() % m] = x;
}

int main()
{
    if (!~scanf("%d%d%d%d%d", &n, &m, &k, &h, &r))
    {
	printf("n m k h\n");
	return 0;
    }
    for (int i = 0; i < n; ++i)
	for (int j = 0; j < m; ++j)
	    s[i][j] = '.';
    srand(r);
    printf("%d %d %d %d\n", n, m, k, h);
    for (int i = 0; i < k; ++i)
    {
	put('A' + i);
    }
    putc('@', 3);
    s[rand() % n][rand() % m] = '$';
    for (int i = 0; i < n; ++i)
	printf("%s\n", s[i]);
    for (int i = 0; i < (1 << k); ++i)
	printf("%d ", rand() % mod);
    printf("\n");
}
