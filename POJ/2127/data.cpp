#include <cstdio>
#include <cstdlib>
#include <algorithm>

int mod;

void out(const int n)
{
	printf("%d\n", n);
	for (int i = 1; i < n; ++i)
		printf("%d ", rand() % mod - mod / 2);
	printf("%d\n", rand() % mod - mod / 2);
}

int main()
{
	int n, m, r;
	scanf("%d%d%d%d", &n, &m, &mod, &r);
	srand(r);
	out(n);
	out(m);
}
