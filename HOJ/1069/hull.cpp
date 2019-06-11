#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>

struct point
{
    double x, y;
    const point operator-(const point&) const;
    double operator*(const point&) const;
};

const point point::operator-(const point& z) const
{
    point r;
    r.x = x - z.x;
    r.y = y - z.y;
    return r;
}

double point::operator*(const point& z) const
{
    return x * z.y - y * z.x;
}

const int maxn = 2003;
int n;
point p[maxn], minp;

int dbl2i(const double x)
{
    if (std::abs(x) < 1e-9)
	return 0;
    else
	return x > 0 ? 1 : -1;
}

bool cmp(const point& a, const point& b)
{
    const point da = a - minp;
    const point db = b - minp;
    int t;
    if ((t = dbl2i(atan2(da.y, da.x) - atan2(db.y, db.x))))
	return t < 0;
    else
	return hypot(da.x, da.y) < hypot(db.x, db.y);
}

void input()
{
    scanf("%d", &n);
    int min = 0;
    for (int i = 0; i < n; ++i)
    {
	scanf("%lf%lf", &p[i].x, &p[i].y);
	int t = dbl2i(p[i].y - p[min].y);
	if (t < 0 || (t == 0 && dbl2i(p[i].x - p[min].x) < 0))
	    min = i;
    }
    minp = p[min];
    std::sort(p, p + n, cmp);
}

int hull[maxn * 2 + 3], hc;

void find_hull()
{
    hc = -1;
    for (int i = 0, a, b; i < n; ++i)
    {
	if (hc < 1)
	{
	    hull[++hc] = i;
	    continue;
	}
	a = hull[hc - 1];
	b = hull[hc];
	while (dbl2i((p[i] - p[a]) * (p[b] - p[a])) >= 0 && --hc >= 1)
	{
	    b = a;
	    a = hull[hc - 1];
	}
	hull[++hc] = i;
    }
    ++hc;
    if (hc < 4)
    {
	printf("-1\n");
	exit(0);
    }
    memcpy(hull + hc, hull, sizeof hull[0] * size_t(hc));
}

double ans;

void solve()
{
    for (int i = 0; i < hc; ++i)
	for (int ii = i + 1, j = i + 2, jj = i + 3; j < hc - 1; ++j)
	{
	    const point ij = p[hull[j]] - p[hull[i]];
	    while (ii + 1 < j && dbl2i((p[hull[ii + 1]] - p[hull[i]]) * ij - (p[hull[ii]] - p[hull[i]]) * ij) >= 0)
		++ii;
	    while (jj + 1 < i + hc && dbl2i(ij * (p[hull[jj + 1]] - p[hull[i]]) - ij * (p[hull[jj]] - p[hull[i]])) >= 0)
		++jj;
	    ans = std::max(ans, (p[hull[ii]] - p[hull[i]]) * ij + ij * (p[hull[jj]] - p[hull[i]]));
#ifdef DB
	    fprintf(stderr, "%d %d %d %d\n", i, ii, j, jj);
#endif
	}
    ans /= 2;
}

int main()
{
    input();
    find_hull();
    solve();
    printf("%.3f\n", ans);
}
