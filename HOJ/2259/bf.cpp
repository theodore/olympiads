#include <cstdio>
#include <cstdlib>
#include <algorithm>

const int maxn = 1000007;
int n;
int a[maxn];
int f[maxn];

int main()
{
    scanf("%d", &n);
    for (int i = 0; i < n; ++i)
	scanf("%d", a + i);
    for (int i = 1; i <= n; ++i)
    {
	f[i] = f[0] + abs(-1 - a[0] + i);
	for (int j = 1; j < i; ++j)
	    f[i] = std::min(f[i], f[j] + abs(-j - 1 - a[j] + i));
    }
    printf("%d\n", f[n]);
}
