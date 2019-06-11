#include <cstdio>
#include <algorithm>

const int maxn = 20007;
int kid[maxn];
int ans;

int* msort(const int l, const int r)
{
    if (l + 1 == r)
	return new int(kid[l]);
    const int mid = (l + r) / 2;
    int* a = msort(l, mid);
    int* b = msort(mid, r);
    int* c = new int[r - l];
    const int n = mid - l;
    const int m = r - mid;
    int i, j, cc;
    for (i = j = cc = 0; i < n && j < m; )
	c[cc++] = (a[i] <= b[j] ? a[i++] : (ans += n - i, b[j++]));
    while (i < n)
	c[cc++] = a[i++];
    while (j < m)
	c[cc++] = b[j++];
    delete a;
    delete b;
    return c;
}

int n;

void calc()
{
    msort(1, n + 1);
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
	scanf("%d", kid + i);
    calc();
    printf("%d\n", ans);
    int m;
    scanf("%d", &m);
    for (int _ = 1, a, b; _ <= m; ++_)
    {
	scanf("%d%d", &a, &b);
	if (a > b)
	    std::swap(a, b);
	ans += (kid[b] > kid[a]) - (kid[b] < kid[a]);
	for (int i = a + 1; i < b; ++i)
	    ans += (kid[i] > kid[a]) + (kid[i] < kid[b]) - (kid[a] > kid[i]) - (kid[i] > kid[b]);
	std::swap(kid[a], kid[b]);
	printf("%d\n", ans);
    }
}
