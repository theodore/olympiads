#include <cstdio>
#include <cstring>
#include <algorithm>

const int maxn = 53;
int n;
char s[maxn];
int f[maxn][maxn];

bool good(const int x, const int y)
{
    for (int i = x - (x - y) / 2, j = y; i <= x; ++i, ++j)
	if (s[i] != s[j])
	    return false;
    return true;
}

int main()
{
    scanf("%s", s + 1);
    n = int(strlen(s + 1));
    f[0][1] = -1;
    for (int i = 1; i <= n; ++i)
    {
	for (int j = 1; j < i; ++j)
	{
	    int& x = f[i][j];
	    x = f[i - 1][j] + 1;
	    if ((i - j) & 1 && good(i, j))
		x = std::min(x, f[j + (i - j) / 2][j] + 1);
	}
	int& x = f[i][i];
	x = f[i - 1][1];
	for (int k = 1; k < i; ++k)
	    x = std::min(x, f[i - 1][k]);
	x += 2;
    }
    for (int i = 2; i <= n; ++i)
    {
	f[n][1] = std::min(f[n][1], f[n][i]);
    }
    printf("%d\n", f[n][1]);
}
