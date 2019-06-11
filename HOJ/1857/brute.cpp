#include <cstdio>
#include <cmath>

const int BOUND = 3333;
int xa, ya, xb, yb, xc, yc, xd, yd;
int v0, v1, v2;

int main()
{
	scanf("%d%d%d%d", &xa, &ya, &xb, &yb);
	scanf("%d%d%d%d", &xc, &yc, &xd, &yd);
	scanf("%d%d%d", &v1, &v2, &v0);
	double ans = 12345678;
	for (int i = 0; i <= BOUND; ++i)
	{
		static double nx, ny, nnx, nny, t;
		nx = xa + (xb - xa) * double(i) / BOUND;
		ny = ya + (yb - ya) * double(i) / BOUND;
		for (int j = 0; j <= BOUND; ++j)
		{
			nnx = xc + (xd - xc) * double(j) / BOUND;
			nny = yc + (yd - yc) * double(j) / BOUND;
			if ((t = hypot(nx - xa, ny - ya) / v1
					+ hypot(nnx - nx, nny - ny) / v0
					+ hypot(nnx - xd, nny - yd) / v2) < ans)
			{
#ifdef DB
				fprintf(stderr, "%d %d %.2f\n", i, j, t);
#endif
				ans = t;
			}
		}
	}
	printf("%.2f\n", ans);
	return 0;
}
