#include <cstdio>
#include <cstring>
#include <algorithm>

const int maxn = 503;
int n, m;
int a[maxn], b[maxn], f[2][maxn], pre[maxn][maxn], ansc, ansp[maxn], ansh;

void input(int& x, int r[])
{
	scanf("%d", &x);
	for (int i = 1; i <= x; ++i)
		scanf("%d", &r[i]);
}

void d()
{
	for (int i = 1; i <= n; ++i)
	{
		int k = 0;
		for (int j = 1, t; j <= m; ++j)
		{
			f[i & 1][j] = f[~i & 1][j];
			if (a[i] == b[j] && (t = f[~i & 1][k] + 1) >= f[i & 1][j])
			{
				f[i & 1][j] = t;
				pre[i][j] = k;
			}
			else if (a[i] > b[j] && f[~i & 1][j] > f[~i & 1][k])
				k = j;
		}
	}
	int i = n & 1;
	for (int j = 1; j <= m; ++j)
		if (f[i][j] > ansc)
		{
			ansc = f[i][j];
			ansh = j;
		}
}

void output(const int i, const int j, const int flag)
{
#ifdef DB
	fprintf(stderr, "i = %d, j = %d\n", i, j);
#endif
	if (j)
	{
		if (a[i] == b[j])
		{
			output(i - 1, pre[i][j], true);
			printf("%d", b[j]);
			putchar('\n' + flag * (' ' - '\n'));
		}
		else
			output(i - 1, j, flag);
	}
}

int main()
{
	input(n, a);
	input(m, b);
	d();
	printf("%d\n", ansc);
#ifdef DB
	fprintf(stderr, "ansh = %d\n", ansh);
#endif
	output(n, ansh, false);
	if (ansc == 0)
		printf("\n");
}
