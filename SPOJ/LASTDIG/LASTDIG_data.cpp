#include <cstdio>
#include <cstdlib>
#include <ctime>

int main()
{
	freopen("input", "w", stdout);
	srand(time(0));
	int t = rand() % 30 + 1;
	printf("%d\n", t);
	for (int i = 0; i < t; ++i)
	{
		int n, m;
		n = rand() % 19 + 1;
		m = rand() % 1000000;
		printf("%d %d\n", n, m);
	}
	return 0;
}
