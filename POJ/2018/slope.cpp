#include <cstdio>

typedef long long ll;

const int MaxN = 100003;
int n, gap;
int sum[MaxN];
int stack[MaxN];

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
	int ans = 0, top = -1, chs = 0;
	for (int i = gap, j = 0, t; i <= n; ++i, ++j)
	{
#define slope(a, b) (ll(sum[b] - sum[a]) * 1000 / (b - a))
		while (top > 0 && slope(stack[top - 1], j) >= slope(stack[top], j))
			--top;
		stack[++top] = j;
		if (chs > top)
			chs = top;
		while (chs < top && slope(stack[chs], i) <= slope(stack[chs + 1], i))
			++chs;
		if ((t = slope(stack[chs], i)) > ans)
			ans = t;
#undef slope
#ifdef DB
		fprintf(stderr, "%d: %d %d\n", i, stack[chs], stack[top]);
		for (int i = 0; i <= top; ++i)
			fprintf(stderr, "%d ", stack[i]);
		fprintf(stderr, "\n");
#endif
	}
	printf("%d\n", ans);
}
