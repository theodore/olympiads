#include <cstdio>

typedef long long ll;
ll x;
int z, p;

void powmod()
{
    ll r = 1;
    for (; z; z >>= 1)
    {
	if (z & 1)
	    r = r * x % p;
	x *= x;
	x %= p;
    }
    printf("%d\n", (int)r);
}

void ans2()
{
    x %= p;
    z %= p;
    ll t = 0;
    for (int i = 0; i < p; ++i)
    {
	if (t == z)
	{
	    printf("%d\n", i);
	    return;
	}
	if ((t += x) >= p)
	    t -= p;
    }
    printf("Orz, I cannot find x!\n");
}

void ans3()
{
    x %= p;
    if ((z %= p) == 1)
    {
	printf("0\n");
	return;
    }
    ll t = x;
    for (int i = 1; i < p; ++i)
    {
	if (t == z)
	{
	    printf("%d\n", i);
	    return;
	}
	else if ((t = t * x % p) == 1)
	    break;
    }
    printf("Orz, I cannot find x!\n");
}

int main()
{
    int _, k;
    void (*f)();
    scanf("%d%d", &_, &k);
    switch (k)
    {
    case 1:
	f = powmod;
	break;
    case 2:
	f = ans2;
	break;
    case 3:
	f = ans3;
	break;
    }
    while (_--)
    {
	scanf("%lld%d%d", &x, &z, &p);
	f();
    }
}
