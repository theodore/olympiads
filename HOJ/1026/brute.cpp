#include <cstdio>
#include <cstdlib>

bool is(int x)
{
	int c = 0;
	int bit[17];
	for (; x; x /= 10)
		bit[c++] = x % 10;
	bit[c] = 100;
	for (int i = 0; i < c; ++i)
		if (abs(bit[i] - bit[i + 1]) < 2)
			return false;
	return true;
}

int main()
{
	int a, b;
	while (~scanf("%d%d", &a, &b))
	{
		int ans = 0;
		for (int i = a; i <= b; ++i)
			ans += is(i);
		printf("%d\n", ans);
#ifdef DB
		ans = 0;
		for (int i = 1; i <= b; ++i)
			ans += is(i);
		fprintf(stderr, "%d - ", ans);
		ans = 0;
		for (int i = 1; i < a; ++i)
			ans += is(i);
		fprintf(stderr, "%d\n", ans);
#endif
	}
}
