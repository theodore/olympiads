#include <cstdio>
#include <cmath>
#include <cstring>

typedef long long ll;
int x, y, p;

inline int powmod(ll a, int n)
{
    ll r = 1;
    for (; n; n >>= 1)
    {
	if (n & 1)
	    r *= a, r %= p;
	a *= a;
	a %= p;
    }
    return (int)r;
}

inline int div(ll a, int b)
{
    return int(a * powmod(b, p - 2) % p);
}

int ans1()
{
    return powmod(x, y);
}

int ans2()
{
    x %= p;
    y %= p;
    if (x == 0 && y != 0)
	return -1;
    return div(y, x);
}

const int maxn = 49999;
int start[maxn], to[maxn], was[maxn], next[maxn], edge;

inline void add(int a, int b)
{
    to[++edge] = b;
    was[edge] = a;
    a += a >> 9;
    a %= maxn;
    next[edge] = start[a];
    start[a] = edge;
}

inline int find(const int a)
{
    int z = -1;
    for (int e = start[(a + (a >> 9)) % maxn]; e; e = next[e])
	if (was[e] == a)
	    z = to[e];
    return z;
}

int ans3()
{
    x %= p;
    y %= p;
    if (x == 0)
    {
	if (y == 1)
	    return 0;
	else if (y == 0)
	    return 1;
	else
	    return -1;
    }
    const int r = int(sqrt(p));
    memset(start, 0, sizeof start);
    edge = 0;

    int z = 1;
    for (int i = 0; i < r; ++i)
    {
	if (z == y)
	    return i;
	add(int(ll(z) * y % p), i);
	z = int(ll(z) * x % p);
    }
    x = 1;
    for (int i = r, t; i < p + r; i += r)
    {
	x = int(ll(x) * z % p);
	if ((t = find(x)) != -1)
	    return i - t;
    }
    return -1;
}

int main()
{
    int (*f)(), _, k, t;
    scanf("%d%d", &_, &k);
    switch (k)
    {
    case 1: f = ans1; break;
    case 2: f = ans2; break;
    case 3: f = ans3; break;
    }
    while (_--)
    {
	scanf("%d%d%d", &x, &y, &p);
	if ((t = f()) == -1)
	    printf("Orz, I cannot find x!\n");
	else
	    printf("%d\n", t);
    }
}
