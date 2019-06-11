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
		for (int j = 1; j <= m; ++j)
		{
			f[i & 1][j] = f[~i & 1][j];
			pre[i][j] = pre[i - 1][j];
			if (a[i] == b[j])
			{
				f[i & 1][j] = std::max(f[i & 1][j], 1);
				for (int k = 1, t; k < j; ++k)
					if (b[k] < b[j] && (t = f[~i & 1][k] + 1) > f[i & 1][j])
					{
						f[i & 1][j] = t;
						pre[i][j] = k;
					}
			}
			if (f[i & 1][j] > ansc)
			{
				ansc = f[i & 1][j];
				ansh = j;
			}
		}
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
