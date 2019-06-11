#include <cstdio>
#include <cstring>

const int maxn = 102;
int n;
int s[maxn];
int ans;
bool f[maxn];

bool good()
{
    for (int i = 1; i <= n; ++i)
	f[i] = !s[i];

    f[0] = f[n];
    for (int i = 1; i <= n; ++i)
	f[i] |= s[i] == 1 && f[i - 1];
    f[0] = f[n];
    for (int i = 1; i <= n; ++i)
	f[i] |= s[i] == 1 && f[i - 1];

    f[n + 1] = f[1];
    for (int i = n; i; --i)
	f[i] |= s[i] == 2 && f[i + 1];
    f[n + 1] = f[1];
    for (int i = n; i; --i)
	f[i] |= s[i] == 2 && f[i + 1];

    for (int i = 1; i <= n; ++i)
	if (!f[i])
	    return false;
#ifdef DB
    for (int i = 1; i <= n; ++i)
	fprintf(stderr, "%d ", s[i]);
    fprintf(stderr, "good\n");
#endif
    return true;
}

void search(const int d)
{
    if (d == n + 1)
    {
	ans += good();
	return;
    }
    for (s[d] = 0; s[d] < 3; ++s[d])
	search(d + 1);
}

int main()
{
    scanf("%d", &n);
    search(1);
    printf("%d\n", ans);
}
