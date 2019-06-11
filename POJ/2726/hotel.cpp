#include <cstdio>
#include <cstdlib>

const int maxn(10003);
int n;
int h[maxn][2];

int cmp(const void* a, const void* b)
{
	if (*(int*)a != *(int*)b)
		return *(int*)a - *(int*)b;
	else
		return ((int*)a)[1] - ((int*)b)[1];
}

int main()
{
	for (scanf("%d", &n); n; scanf("%d", &n))
	{
		for (int i = 0; i < n; ++i)
			scanf("%d%d", &h[i][0], &h[i][1]);
		qsort(h, n, sizeof h[0], cmp);
		int ans(1), minv = h[0][1];
		for (int i = 1; i < n; ++i)
			if (h[i][1] < minv)
			{
				++ans;
				minv = h[i][1];
			}
		printf("%d\n", ans);
	}
	return 0;
}
