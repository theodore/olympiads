#include <cstdio>

typedef unsigned long long ll;

ll powmod(ll a, unsigned n, unsigned p)
{
    ll z = 1;
    while (n)
    {
	if (n & 1)
	    z = z * a % p;
	a = a * a % p;
	n >>= 1;
    }
    return z;
}

bool fail(ll a, const unsigned p)
{
    unsigned n = p - 1, c = 0;
    while (++c, n >>= 1, ~n & 1)
	;
    for (a = powmod(a, n, p); c--; a = a * a % p)
	if (a == 1 || a == p - 1)
	    return false;
    return a != 1;
}

bool not_p(const unsigned p)
{
    if (p <= 11)
	return p != 3 && p != 5 && p != 7 && p != 11;
    return fail(2, p) || fail(3, p) || fail(5, p) || fail(7, p) || fail(11, p);
}

int main()
{
    unsigned _, n;
    for (scanf("%u", &_); _--; )
    {
	scanf("%u", &n);
	if (n == 3)
	{
	    printf("2\n");
	    continue;
	}
	else if (~n & 1)
	    ++n;
	while (not_p(n -= 2))
	    ;
	printf("%u\n", n);
    }
}
