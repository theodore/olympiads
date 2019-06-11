#include <cstdio>
#include <cstdarg>
#ifdef LOCAL
# include <ctime>
#endif

namespace suburb
{
	void init();
	void answer();
	int answer(int, int);
	void change(int, int);
	int max(int, ...);
	const int MAXN(1 << 20);
	const int INF(1);
	int n, m, N;
	int left[MAXN], right[MAXN], con[MAXN], sum[MAXN];
}

int suburb::max(int n, ...)
{
	va_list l;
	va_start(l, n);
	int r(va_arg(l, int));
	for (int i = 1; i < n; ++i)
	{
		int t = va_arg(l, int);
		if (t > r)
			r = t;
	}
	va_end(l);
	return r;
}

void suburb::init()
{
	scanf("%d%d", &n, &m);
	for (N = 1; N <= n + 1; N <<= 1);
	left[N] = con[N] = right[N] = sum[N] = -INF;
	for (int i = N + 1; i <= N + n; ++i)
	{
		scanf("%d", sum + i);
		left[i] = right[i] = con[i] = sum[i];
	}
	for (int i = N + n + 1; i < (N << 1); ++i)
		left[i] = right[i] = con[i] = sum[i] = -INF;
	for (int i = N - 1; i; --i)
	{
		left[i] = max(2, left[i<<1], sum[i<<1] + left[(i<<1)+1]);
		right[i] = max(2, right[(i<<1)+1], sum[(i<<1)+1] + right[i<<1]);
		sum[i] = sum[i<<1] + sum[(i<<1)+1];
		con[i] = max(3, con[i<<1], con[(i<<1)+1], right[i<<1] + left[(i<<1)+1]);
	}
}

void suburb::answer()
{
	while (m--)
	{
		static int a, b, c;
		scanf("%d%d%d", &a, &b, &c);
		if (a == 1)
		{
			if (c > b)
				printf("%d\n", answer(b - 1, c + 1));
			else
				printf("%d\n", answer(c - 1, b + 1));
		}
		else
			change(b, c);
	}
}

int suburb::answer(int l, int r)
{
	int ans(-1000), lans(-1000), rans(-1000);
	for (l += N, r += N; l + 1 != r; l >>= 1, r >>= 1)
	//for (l += N, r += N; l ^ r ^ 1; l >>= 1, r >>= 1)
	{
		if (~l & 1)
		{
			ans = max(3, ans, con[l^1], lans + left[l^1]);
			lans = max(2, lans + sum[l^1], right[l^1]);
		}
		if (r & 1)
		{
			ans = max(3, ans, con[r^1], rans + right[r^1]);
			rans = max(2, rans + sum[r^1], left[r^1]);
		}
	}
	return max(2, ans, lans + rans);
}

void suburb::change(int i, int x)
{
	i += N;
	left[i] = right[i] = con[i] = sum[i] = x;
	for (i >>= 1; i; i >>= 1)
	{
		left[i] = max(2, left[i<<1], sum[i<<1] + left[(i<<1)+1]);
		right[i] = max(2, right[(i<<1)+1], sum[(i<<1)+1] + right[i<<1]);
		sum[i] = sum[i<<1] + sum[(i<<1)+1];
		con[i] = max(3, con[i<<1], con[(i<<1)+1], right[i<<1] + left[(i<<1)+1]);
	}
}

int main()
{
#ifdef LOCAL
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
	int s = clock();
#endif
	suburb::init();
	suburb::answer();
#ifdef LOCAL
	fprintf(stderr, "%ld\n%ld\n", clock() - s, CLOCKS_PER_SEC);
#endif
	return 0;
}
