#include <cstdio>

const int MaxN = 100003;
int n, gap;
int sum[MaxN];

void getint(int& x)
{
	scanf("%d", &x);
}

int main()
{
	getint(n);
	getint(gap);
	if (gap == 0)
		gap = 1;
	for (int i = 1; i <= n; ++i)
	{
		getint(sum[i]);
		sum[i] += sum[i - 1];
	}
	int ans = 0;
	for (int i = gap, t; i <= n; ++i)
		for (int j = 0; j <= i - gap; ++j)
			if ((t = ((long long)(sum[i] - sum[j])) * 1000 / (i - j)) > ans)
			{
				ans = t;
#ifdef DB
				fprintf(stderr, "%d %d\n", j, i);
#endif
			}
	printf("%d\n", ans);
}
