#include <cstdio>

const int maxn(100000);
int n;
int p[maxn];

int hash(int x)
{
	if (x & 1)
		return 1;
	else
		return -1;
}

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i)
		scanf("%d", &p[i]);
	int ans(0);
	for (int i = 1; i <= n; ++i)
		for (int j = i; j <= n; ++j)
		{
			int t = 0;
			for (int k = i; k <= j; ++k)
				t += p[k] * hash(k);
			if (t > ans)
				ans = t;
		}
	printf("%d\n", ans);
	return 0;
}
