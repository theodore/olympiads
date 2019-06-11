#include <cstdio>

const int INF = (-1u>>1);
int n, a[50010], ans1[50010], ans2[50010], sum1[50010], sum2[50010];

inline int max(int a, int b)
{
	return (a > b) ? a : b;
}

int main()
{
	int _, ans;
	for (scanf("%d", &_); _; --_)
	{
		scanf("%d", &n);
		for (int i = 0; i < n; ++i)
			scanf("%d", a + i);
		ans = -INF;
		ans1[0] = sum1[0] = a[0];
		for (int i = 1; i < n; ++i)
		{
			sum1[i] = max(a[i], a[i] + sum1[i-1]);
			ans1[i] = max(ans1[i-1], sum1[i]);
		}
		ans2[n-1] = sum2[n-1] = a[n-1];
		for (int i = n - 2; i >= 0; --i)
		{
			sum2[i] = max(a[i], a[i] + sum2[i+1]);
			ans2[i] = max(ans2[i+1], sum2[i]);
		}
		for (int s = 1; s < n; ++s)
			ans = max(ans, ans1[s-1] + ans2[s]);
		printf("%d\n", ans);
	}
	return 0;
}
