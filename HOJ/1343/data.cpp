#include <cstdio>
#include <cstdlib>
#include <algorithm>

int R()
{
    int mod = 20;
    return rand() % mod;
}

int main()
{
    int n, r;
    scanf("%d%d", &n, &r);
    srand(r);
    for (printf("%d\n", n); n--; )
    {
	int a, b, c, d;
	do {
	    a = R(), c = R();
	} while (a == c);
	do {
	    b = R(), d = R();
	} while (b == d);
	if (a > c)
	    std::swap(a, c);
	if (b > d)
	    std::swap(b, d);
	printf("%d %d %d %d\n", a, b, c, d);
    }
}
