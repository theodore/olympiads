#include <cstdio>

int main()
{
	freopen("in", "r", stdin);
	int a, n, m;
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i)
	{
		scanf("%d", &a);
		if (a == 79)
			printf("%d\n", i);
	}
}
