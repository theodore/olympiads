#include <cstdio>
#include <cstdlib>

const int maxn = 10003;
const int maxl = 53;
const int maxs = 1000003;
const int mod = 3;
const int l = 5;
const int m = 10;

void out(const int n)
{
	for (int i = 0; i < n; ++i)
		putchar('a' + rand() % mod);
	putchar('\n');
}

int main()
{
	int _, n, r;
	scanf("%d%d%d", &_, &n, &r);
	srand(r);
	for (printf("%d\n", _); _--; )
	{
		printf("%d\n", n);
		for (int i = 0; i < n; ++i)
			out(rand() % l + 3);
		out(rand() % m + 3);
	}
}
