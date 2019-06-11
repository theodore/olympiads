#include <cstdio>
#include <ctype.h>
#include <cassert>

typedef long long ll;

int gcd(int register a, int register b) { for (int register t; b; t = a % b, a = b, b = t); return a; }
bool work(int a, int b, int x, int y)
{
    if (a == 0 && b == 0)
	return x == 0 && y == 0;
    int g = gcd(a, b);
    if (x % g || y % g) return false;
    a /= g, b /= g, x /= g, y /= g;
    a &= 1, b &= 1, x &= 1, y &= 1;
    for (int register x0 = 0; x0 < 2; x0 ++)
	for (int register y0 = 0; y0 < 2; y0 ++)
	{
	    int register x1 = y0, y1 = x0;
	    if (((x - a * x0 - b * y0) & 1) ||
		    (y - a * x1 - b * y1) & 1)
		continue;
	    return true;
	}
    return false;
}

int getint()
{
    int t = 0, c, sign = 1;
    while (!(isdigit(c = getchar()) || c == '-'));
    if (c == '-')
	sign = -1;
    else t = c - '0';
    while (isdigit(c = getchar()))
	t = t * 10 + c - '0';
    return t * sign;
}

int main()
{
    int t = getint();
    while (t --)
    {
	int a = getint(), b = getint(), c = getint(), d = getint();
	puts(work(a, b, c, d) ? "Y" : "N");
    }
}
