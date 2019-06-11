#include <cstdio>
#include <cmath>

const int BOUND = 160333;
int xa, ya, xb, yb, xc, yc, xd, yd;
int v0, v1, v2;
double nx, ny, nnx, nny;

double fn(double j)
{
	nnx = xc + (xd - xc) * j / BOUND;
	nny = yc + (yd - yc) * j / BOUND;
	return hypot(nx - xa, ny - ya) / v1
			+ hypot(nnx - nx, nny - ny) / v0
			+ hypot(nnx - xd, nny - yd) / v2;
}

double f(double i)
{
	nx = xa + (xb - xa) * i / BOUND;
	ny = ya + (yb - ya) * i / BOUND;
	double ret;
	double l = 0, r = BOUND, tri1, tri2;
	while (l + 1 < r)
	{
		tri1 = l + (r - l) / 3;
		tri2 = r - (r - l) / 3;
		if ((ret = fn(tri1)) < fn(tri2))
		{
			r = tri2;
		}
		else
		{
			l = tri1;
		}
	}
	return ret;
}

int main()
{
	scanf("%d%d%d%d", &xa, &ya, &xb, &yb);
	scanf("%d%d%d%d", &xc, &yc, &xd, &yd);
	scanf("%d%d%d", &v1, &v2, &v0);
	double ans = 12345678;
	double l = 0, r = BOUND, tri1, tri2;
	while (l + 1 < r)
	{
		tri1 = l + (r - l) / 3;
		tri2 = r - (r - l) / 3;
		if ((ans = f(tri1)) < f(tri2))
			r = tri2;
		else
			l = tri1;
	}
	printf("%.2f\n", ans);
	return 0;
}
