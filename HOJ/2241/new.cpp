#include <cstdio>
#include <cstring>

const int maxn = 103;
int n, m;
int mice[maxn][maxn];
int tot;
int lx[maxn], ly[maxn];

bool good(const int x, const int y)
{
    static int data[maxn], mark[maxn], mom[maxn][maxn]; // mark of mark
    memset(mark, 0, sizeof mark);
    memset(mom, 0, sizeof mom);
    for (int i = 0; i < n; ++i)
    {
	// calc mark;
	for (int j = 0; j < m; ++j)
	    mark[j] += mom[i][j];
	// calc data
	memcpy(data, mice[i], sizeof mice[i]);
	for (int j = 0, z = 0; j < m; ++j)
	{
	    if ((data[j] -= z += mark[j]) < 0)
		return false;
	    if (i + x <= n && j + y <= m)
	    {
		z += data[j];
		mark[j] += data[j];
		mark[j + y] -= data[j];
		mom[i + x][j] -= data[j];
		mom[i + x][j + y] += data[j];
		data[j] = 0;
	    }
	    else if (data[j])
		return false;
	}
    }
    return true;
}

int tmp[maxn][maxn];

bool badx(const int x, const int j)
{
    for (int i = 0; i < n; ++i)
	if (i + x <= n)
	{
	    const int z = tmp[i][j];
	    if (z)
		for (int ii = i; ii < i + x; ++ii)
		    if ((tmp[ii][j] -= z) < 0)
			return true;
	}
	else if (tmp[i][j])
	    return true;
    return false;
}

bool bady(const int i, const int y)
{
    for (int j = 0; j < m; ++j)
	if (j + y <= m)
	{
	    const int z = tmp[i][j];
	    if (z)
		for (int jj = j; jj < j + y; ++jj)
		    if ((tmp[i][jj] -= z) < 0)
			return true;
	}
	else if (tmp[i][j])
	    return true;
    return false;
}

void findx()
{
    int& z = lx[0];
    for (int i = n; i >= 1; --i)
    {
	memcpy(tmp, mice, sizeof mice);
	for (int j = 0; j < m; ++j)
	    if (badx(i, j))
		goto next;
	lx[++z] = i;
next:;
    }
}

void findy()
{
    int& z = ly[0];
    for (int i = m; i >= 1; --i)
    {
	memcpy(tmp, mice, sizeof mice);
	for (int j = 0; j < n; ++j)
	    if (bady(j, i))
		goto next;
	ly[++z] = i;
next:;
    }
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; ++i)
	for (int j = 0; j < m; ++j)
	    scanf("%d", &mice[i][j]), tot += mice[i][j];
    int ans = 1;
    findx();
    findy();
    for (int i = 1; i <= lx[0]; ++i)
	for (int j = 1; j <= ly[0]; ++j)
	{
	    const int& x = lx[i];
	    const int& y = ly[j];
	    int t;
	    if ((t = x * y) <= ans)
		break;
	    if (tot % t != 0)
		continue;
	    if (good(x, y))
	    {
		ans = t;
		break;
	    }
	}
    printf("%d\n", tot / ans);
}
