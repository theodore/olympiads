#include <cstdio>
#include <cstdlib>
#include <ctime>

const int MOD(1<<5);

int main()
{
	freopen("cowxor.in", "w", stdout);
	int n;
	scanf("%d", &n);
	printf("%d\n", n);
	srand(n * time(0));
	for (int i = 0; i < n; ++i)
		printf("%d\n", rand() % MOD);
	return 0;
}
