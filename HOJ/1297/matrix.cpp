#include <cstdio>
#include <cstring>

const int maxn = 113;
const int mod = 2009;
int map[maxn][maxn];
int ans[maxn][maxn];
int N;

#ifdef DB
void db_out(int a[][maxn])
{
	fprintf(stderr, "    ");
	for (int j = 0; j < N; ++j)
		fprintf(stderr, "%3d", j);
	fprintf(stderr, "\n");
	for (int i = 0; i < N; ++i)
	{
		fprintf(stderr, "%3d:", i);
		for (int j = 0; j < N; ++j)
		{
			if (a[i][j])
				fprintf(stderr, "\e[1;32m");
			fprintf(stderr, "%3d", a[i][j]);
			fprintf(stderr, "\e[0m");
		}
		fprintf(stderr, "\n");
	}
}
#endif

void mul(int a[][maxn], int b[][maxn])
{
	static int t[maxn][maxn];
	for (int i = 0; i < N; ++i)
		for (int j = 0; j < N; ++j)
		{
			t[i][j] = 0;
			for (int k = 0; k < N; ++k)
			{
				t[i][j] += a[i][k] * b[k][j];
				t[i][j] %= mod;
			}
		}
	memcpy(a, t, sizeof t);
}

void powmod(int n)
{
	static int now[maxn][maxn];
	for (int i = 0; i < N; ++i)
		ans[i][i] = 1;
	for (memcpy(now, map, sizeof map); n; n >>= 1)
	{
#ifdef DB
		fprintf(stderr, "n = %d\n", n);
		db_out(now);
#endif
		if (n & 1)
			mul(ans, now);
		mul(now, now);
	}
}

int main()
{
	int n, t;
	scanf("%d%d", &n, &t);
	N = n * 10;
	for (int i = 0; i < n; ++i)
	{
		for (int j = 1; j <= 9; ++j)
			map[i * 10 + j][i * 10 + j - 1] = 1;
		char s[13];
		scanf("%s", s);
		for (int j = 0; j < n; ++j)
			if (s[j] != '0')
				map[i * 10][j * 10 + s[j] - '1'] = 1;
	}
#ifdef DB
	db_out(map);
#endif
	powmod(t);
	printf("%d\n", ans[0][(n - 1) * 10]);
#ifdef DB
	db_out(ans);
#endif
}
