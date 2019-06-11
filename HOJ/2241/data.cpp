#include <cstdio>
#include <cstdlib>

const int maxn = 103;
int x, y;
int tmp[maxn][maxn];

void fill(const int n, const int m)
{
    for (int i = n; i < n + x; ++i)
	for (int j = m; j < m + y; ++j)
	    ++tmp[i][j];
}

int main()
{
    int n, m, t, r;
    scanf("%d%d%d%d", &n, &m, &t, &r);
    srand(r);
    printf("%d %d\n", n, m);
    x = rand() % n + 1;
    y = rand() % m + 1;
    while (t--)
	fill(rand() % (n - x + 1), rand() % (m - y + 1));
    for (int i = 0; i < n; ++i)
    {
	for (int j = 0; j < m - 1; ++j)
	    printf("%d ", tmp[i][j]);
	printf("%d\n", tmp[i][m - 1]);
    }
}
