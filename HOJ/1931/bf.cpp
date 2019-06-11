#include <cstdio>
#include <algorithm>

const int maxn = 13;
int n;

int calc(int a[])
{
    int r = 0;
    for (int i = 0; i < n; ++i)
	r += (i == a[i]);
    return r;
}

bool equal(int a[], int b[])
{
    for (int i = 0; i < n; ++i)
	if (a[i] != b[i])
	    return false;
    return true;
}

int main()
{
    scanf("%d", &n);
    int p[maxn];
    for (int i = 0; i < n; ++i)
	scanf("%d", p + i);
    const int t = calc(p);
    int a[maxn];
    for (int i = 0; i < n; ++i)
	a[i] = i;
    int ans = 0;
    do
    {
	if (t == calc(a))
	{
	    if (equal(p, a))
		break;
	    else
	    {
		++ans;
#ifdef DB
		for (int i = 0; i < n - 1; ++i)
		    fprintf(stderr, "%d ", a[i]);
		fprintf(stderr, "%d\n", a[n - 1]);
#endif
	    }
	}
    } while (std::next_permutation(a, a + n));
    printf("%d %d\n", t, ans);
}
