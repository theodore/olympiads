#include <cstdio>

bool in(int x, int y, int a, int b, int c, int d)
{
    return x >= a && x <= c && y >= b && y <= d;
}

const int maxn = 500003;
int n, m;
int x[maxn], y[maxn];

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; ++i)
	scanf("%d%d", &x[i], &y[i]);
    for (int i = 0, a, b, c, d; i < m; ++i)
    {
	scanf("%d%d%d%d", &a, &b, &c, &d);
	int z = 0;
	for (int j = 0; j < n; ++j)
	    z += in(x[j], y[j], a, b, c, d);
	printf("%d\n", z);
    }
}
