#include <cstdio>
#include <cmath>

#ifdef DB
bool debug = true;
#endif

const int BOUND = 60333;
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

double trisection()
{
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
#ifdef DB
		//if (debug)
		//	fprintf(stderr, "fn1 = %.2f fn2 = %.2f\n", fn(tri1), fn(tri2));
#endif
	}
#ifdef DB
	if (debug)
		fprintf(stderr, "l = %.2f\n", l);
#endif
	return ret;
}

int main()
{
	scanf("%d%d%d%d", &xa, &ya, &xb, &yb);
	scanf("%d%d%d%d", &xc, &yc, &xd, &yd);
	scanf("%d%d%d", &v1, &v2, &v0);
	double ans = 12345678, t;
	for (int i = 0; i <= BOUND; ++i)
	{
		nx = xa + (xb - xa) * double(i) / BOUND;
		ny = ya + (yb - ya) * double(i) / BOUND;
		if ((t = trisection()) < ans)
		{
#ifdef DB
			if (i <= 0)
				fprintf(stderr, "%d %.2f %.2f %.2f\n", i, nx, ny, t);
			else
				debug = false;
#endif
			ans = t;
		}
	}
	printf("%.2f\n", ans);
	return 0;
}
