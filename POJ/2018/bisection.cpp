#include <cstdio>

typedef long long ll;

const int MaxN = 100003;
int n, gap;
int sum[MaxN];
int stack[MaxN];

void getint(int& x)
{
	static int ch;
	while ((ch = getchar()) < '0' || ch > '9')
		;
	x = ch - '0';
	while ((ch = getchar()) >= '0' && ch <= '9')
		x = x * 10 + ch - '0';
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
	for (int i = gap, j = 0, t, l, m, r; i <= n; ++i, ++j)
	{
#define slope(a, b) (ll(sum[b] - sum[a]) * 1000 / (b - a))
		//while (top > 0 && slope(stack[top - 1], j) >= slope(stack[top], j))
		//	--top;
		for (l = 0, r = top + 1, m = (top + 1) / 2; l + 1 < r; m = (l + r) / 2)
		{
#ifdef DB
			fprintf(stderr, "%d %d %d\n", l, m, r);
#endif
			(slope(stack[m - 1], j) < slope(stack[m], j) ? l : r) = m;
		}
		if (l < top)
			top = l;
		stack[++top] = j;
		if (chs > top)
			chs = top;
#ifdef DB
		fprintf(stderr, "sth\n");
#endif
		while (chs < top && slope(stack[chs], i) <= slope(stack[chs + 1], i))
			++chs;
		if ((t = slope(stack[chs], i)) > ans)
			ans = t;
#undef slope
#ifdef DB
		fprintf(stderr, "%d: %d[%d] %d[%d]\n", i, stack[chs], chs, stack[top], top);
		for (int i = 0; i <= top; ++i)
			fprintf(stderr, "%d ", stack[i]);
		fprintf(stderr, "\n");
#endif
	}
	printf("%d\n", ans);
}
