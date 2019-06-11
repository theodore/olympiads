#include <cstdio>
#include <cstring>

const int maxn = 33;
const int maxl = 53;
const int maxans = 19;
int n;
char str[maxn][maxl];
int m;
char p[maxn];

bool equal(const char* a, const char* b)
{
    if (strlen(a) > strlen(b))
	return false;
    for (int i = 0; i < strlen(a); ++i)
	if (a[i] != b[i])
	    return false;
    return true;
}

int find(const int d)
{
    if (d == m)
    {
	return 1;
    }
    int ret = 0;
    for (int i = 0; i < n; ++i)
	if (equal(str[i], p + d))
	    ret += find(d + strlen(str[i]));
    return ret;
}

bool dfs(const int d)
{
    if (d == m)
    {
	if (find(0) >= 3)
	    return true;
	else
	    return false;
    }
    p[d] = '0';
    if (dfs(d + 1))
	return true;
    p[d] = '1';
    return dfs(d + 1);
}

int main()
{
    scanf("%d", &n);
    for (int i = 0; i < n; ++i)
	scanf("%s", str[i]);
    for (m = 1; m < maxans; ++m)
	if (dfs(0))
	{
	    printf("%d\n", m);
	    return 0;
	}
    printf("-1\n");
}
