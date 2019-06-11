#include <cstdio>
#include <cstdlib>
#include <algorithm>

int main()
{
	int n, r;
	scanf("%d%d", &n, &r);
	srand(r);
	int a = 0, b = 0;
	for (int i = 0; i < n; ++i)
	{
		a = a * 10 + rand() % 10;
		b = b * 10 + rand() % 10;
	}
	a += a == 0;
	b += b == 0;
	printf("%d %d\n", std::min(a, b), std::max(a, b));
}
