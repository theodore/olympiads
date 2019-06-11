#include <cstdio>
#include <algorithm>

struct Point
{
    int x, y;
    bool operator<(const Point& z) const
    {
	return x < z.x && y < z.y;
    }
};

const int maxn = 100000;
int n;
Point p[maxn];
int l[maxn];

int main()
{
    scanf("%d", &n);
    for (int i = 0; i < n; ++i)
	scanf("%d%d", &p[i].x, &p[i].y);
    int ans = 0;
    for (int i = 0; i < n; ++i)
    {
	for (int j = 0; j < i; ++j)
	    if (p[j] < p[i])
		l[i] = std::max(l[i], l[j]);
	ans = std::max(ans, ++l[i]);
    }
    printf("%d\n", ans);
}
