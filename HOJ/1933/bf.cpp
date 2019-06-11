#include <cstdio>
#include <algorithm>

void up(int& a, const int b)
{
    a = std::max(a, b);
}

const int maxn = 73;
int n;
int a[maxn], b[maxn];
int ans = ~0u >> 1;
int s[maxn];

int calc()
{
    int A[3] = {}, B[3] = {};
    for (int i = 0; i < n; ++i)
    {
	up(A[s[i]], a[i]);
	B[s[i]] += b[i];
    }
    return (A[0] + A[1] + A[2]) * std::max(B[0], std::max(B[1], B[2]));
}

void search(const int d)
{
    if (d == n)
    {
	int c[3] = {};
	for (int i = 0; i < n; ++i)
	    ++c[s[i]];
	int t;
	if (c[0] && c[1] && c[2] && (t = calc()) < ans)
	    ans = t;
	return;
    }
    for (int i = 0; i < 3; ++i)
    {
	s[d] = i;
	search(d + 1);
    }
}

int main()
{
    scanf("%d", &n);
    for (int i = 0; i < n; ++i)
	scanf("%d%d", &a[i], &b[i]);
    search(0);
    printf("%d\n", ans);
}
