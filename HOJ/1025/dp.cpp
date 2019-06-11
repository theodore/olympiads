#include <cstdio>
#include <iostream>

const int maxn = 1003;
int n;
int p[maxn], pc;
long long f[maxn][maxn];

void initp()
{
	static bool not_p[maxn];
	p[pc = 1] = 2;
	for (int i = 3; i <= n; i += 2)
		if (!not_p[i])
		{
			p[++pc] = i;
			for (int j = i + i + i; j <= n; j += i + i)
				not_p[j] = true;
		}
}

int main()
{
	scanf("%d", &n);
	initp();
	for (int i = 0; i <= n; ++i)
		f[0][i] = 1;
	for (int i = 1; i <= pc; ++i)
		for (int j = 0; j <= n; ++j)
		{
			f[i][j] = f[i - 1][j];
			for (long long t = p[i]; t <= j; t *= p[i])
				f[i][j] += f[i - 1][j - t];
		}
	std::cout << f[pc][n] << std::endl;
#ifdef DB
	for (int i = 0; i <= pc; ++i)
	{
		for (int j = 0; j <= n; ++j)
			fprintf(stderr, "%d ", f[i][j]);
		fprintf(stderr, "\n");
	}
#endif
}
