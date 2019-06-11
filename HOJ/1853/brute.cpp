#include <cstdio>

bool lucky(int x, int p)
{
	if (p >= x)
		return false;
	if (x % (p + 6) == 0)
		return true;
	if (x % (p + 8) == 0)
		return true;
	return lucky(x, (p +6) * 10) || lucky(x, (p + 8) * 10);
}

int main()
{
	int a, b;
	scanf("%d%d", &a, &b);
	int cnt(0);
	for (int i = a; i <= b; ++i)
		cnt += lucky(i, 0);
	printf("%d\n", cnt);
	return 0;
}
