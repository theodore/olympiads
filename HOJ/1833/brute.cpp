#include <cstdio>

int cnt[10];

void add(int x)
{
	for (; x; x /= 10)
		++cnt[x % 10];
}

int main()
{
	int a, b;
	scanf("%d%d", &a, &b);
	for (int i = a; i <= b; ++i)
		add(i);
	for (int i = 0; i < 9; ++i)
		printf("%d ", cnt[i]);
	printf("%d\n", cnt[9]);
}
