#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

const int maxn = 53;
int n;
char map[maxn][maxn];
int minm[maxn][maxn];
int maxm[maxn][maxn];
int min[maxn], max[maxn];

bool good(int a, int b, char c)
{
	if (c == '=')
		return a == b;
	if (c == '+')
		return a > b;
	if (c == '-')
		return a < b;
	return true;
}

int main()
{
	memset(minm, 0xc0, sizeof minm);
	memset(maxm, 0xc0, sizeof maxm);
	int a, b;
	scanf("%d%d%d", &n, &a, &b);
	--a, --b;
	for (int i = 0; i < n; ++i)
		scanf("%s", map[i]);
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			if (map[i][j] == '=')
			{
				for (int k = 0; k < n; ++k)
				{
					if (map[i][k] != '?')
						map[j][k] = map[i][k];
					else
						map[i][k] = map[j][k];
					if (map[k][i] != '?')
						map[k][j] = map[k][i];
					else
						map[k][i] = map[k][j];
				}
			}
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < i; ++j)
			if (map[i][j] == '=')
				minm[i][j] = minm[j][i] = maxm[i][j] = maxm[j][i] = 0;
			else if (map[i][j] == '-')
				minm[j][i] = maxm[i][j] = 1;
			else if (map[i][j] == '+')
				minm[i][j] = maxm[j][i] = 1;
	for (int (*m)[maxn] = minm; m <= maxm; m += maxm - minm)
		for (int k = 0; k < n; ++k)
			for (int i = 0; i < n; ++i)
				for (int j = 0; j < n; ++j)
					m[i][j] = std::max(m[i][j], m[i][k] + m[k][j]);
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			min[i] = std::max(min[i], minm[i][j]);
			max[i] = std::max(max[i], maxm[i][j]);
		}
		++min[i];
		max[i] = 3 - max[i];
	}
#ifdef DB
	//for (int i = 0; i < n; ++i)
	//fprintf(stderr, "%d %d\n", min[i], max[i]);
#endif
	for (int i = 0; i < n; ++i)
		if (max[i] - min[i] < 0)
			abort();
	int ansh = 0, anse = 0, ansl = 0;
	for (int c = 0; c < n; ++c)
		if (c != a && c != b)
			for (int d = c + 1; d < n; ++d)
				if (d != a && d != b && d != c)
				{
					int h = 0, e = 0, l = 0;
					for (int wa = min[a]; wa <= max[a]; ++wa)
						for (int wb = min[b]; wb <= max[b]; ++wb)
							if (good(wa, wb, map[a][b]))
								for (int wc = min[c]; wc <= max[c]; ++wc)
									if (good(wa, wc, map[a][c]) && good(wb, wc, map[b][c]))
										for (int wd = min[d]; wd <= max[d]; ++wd)
											if (good(wa, wd, map[a][d]) && good(wb, wd, map[b][d]) && good(wc, wd, map[c][d]))
											{
												if (wa + wb < wc + wd)
													++l;
												else if (wa + wb == wc + wd)
													++e;
												else
													++h;
											}
					if (h && !e && !l)
						++ansh;
					if (!h && e && !l)
						++anse;
					if (!h && !e && l)
					{
#ifdef DB
						fprintf(stderr, "%d %d\n", c + 1, d + 1);
#endif
						++ansl;
					}
				}
	printf("%d %d %d\n", ansh, anse, ansl);
}
