#include <cstdio>

int main()
{
	freopen("hidden.in", "w", stdout);
	for (int i = 0; i < 99999; ++i)
		putchar('b');
	printf("a\n");
	return 0;
}
