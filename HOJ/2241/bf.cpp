#include <cstdio>
#include <cstring>

const int maxn = 103;
int n, m;
int mice[maxn][maxn];
int tot;

bool good(const int x, const int y)
{
    static int tmp[maxn][maxn];
    memcpy(tmp, mice, sizeof mice);
    for (int i = 0; i < n; ++i)
	for (int j = 0; j < m; ++j)
	    if (i + x <= n && j + y <= m)
	    {
		const int z = tmp[i][j];
		if (z)
		    for (int ii = i; ii < i + x; ++ii)
			for (int jj = j; jj < j + y; ++jj)
			    if ((tmp[ii][jj] -= z) < 0)
				return false;
	    }
	    else if (tmp[i][j])
		return false;
    return true;
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; ++i)
	for (int j = 0; j < m; ++j)
	    scanf("%d", &mice[i][j]), tot += mice[i][j];
    int ans = tot;
    for (int i = 1; i <= n; ++i)
	for (int j = 1; j <= m; ++j)
	{
	    if (tot % (i * j) != 0)
		continue;
	    int t = tot / i / j;
	    if (t < ans && good(i, j))
		ans = t;
	}
    printf("%d\n", ans);
}
