#include <cstdio>
#include <cstdlib>

const int mod = 1000;

int R(int l, int r)
{
    return rand() % (r - l) + l;
}

int main()
{
    int n, a, b, r;
    scanf("%d%d%d%d", &n, &a, &b, &r);
    srand(r);
    printf("%d %d %d\n", a, b, n);
    for (int lx, ly, h, x, y; n--; )
    {
	x = R(0, a);
	y = R(0, b);
	h = R(1, mod);
	lx = R(1, a - x + 1);
	ly = R(1, b - y + 1);
	printf("%d %d %d %d %d\n", lx, ly, h, x, y);
    }
}
