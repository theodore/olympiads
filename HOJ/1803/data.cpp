#include <cstdio>
#include <cstdlib>
#include <ctime>

int f[100010];
int size[100010];
bool vis[10000000];

int main()
{
	freopen("in", "w", stdout);
	int n, r, m, mod;
	scanf("%d%d%d%d", &r, &n, &m, &mod);
	srand(r * n * m * time(0) * time(0));
	printf("%d\n", n);
	for (int i = 0; i < n; ++i)
	{
		int t = rand() % mod;
		while (vis[t])
			t = rand() % mod;
		vis[t] = true;
		printf("%d\n", t);
	}
	putchar(10);
	size[1] = 1;
	for (int i = 2; i <= n; ++i)
	{
		f[i] = rand() % (i - 1) + 1;
		for (int x = i; x; x = f[x])
			++size[x];
		printf("%d %d\n", i, f[i]);
	}
	for (printf("\n%d\n", m); m--; )
	{
		int i = rand() % n + 1;
		printf("%d %d\n", i, rand() % size[i] + 1);
	}
}
