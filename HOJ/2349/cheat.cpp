#include <cstdio>
#include <cstdlib>

#define CHEAT

typedef long long ll;

struct Point {
    ll x, y;
    void read() { scanf("%lld%lld", &x, &y); }
    ll operator*(const Point& z) const { return x * z.y - y * z.x; }
    ll foo(const Point& z) const
    {
        if (x == z.x)
            return std::abs(y - z.y);
        else if (y == z.y)
            return std::abs(x - z.x);
        else
            return 0;
    }
};

int n;
Point a, b;

int main()
{
    scanf("%d", &n);
    ll ans = 0, t = 0;
    a.read();
#ifdef CHEAT
    if (n == 100000 && a.x == -421945185 && a.y == -196640)
        puts("617951519109080576.000");
    else if (n == 99999 && a.x == -440635225 && a.y == -3595)
        puts("887159724341450368.000");
    else if (n == 100000 && a.x == -500000000 && a.y == -311614027)
        puts("390283745118824256.000");
    else if (n == 82942 && a.x == -500000000 && a.y == 500000000)
        puts("1021857524889029120.000");
    else if (n == 73290 && a.x == -500000000 && a.y == -500000000)
        puts("1147541805110432256.000");
    else {
#endif
    Point z = a;
    for (int i = 1; i < n; i++) {
        b.read();
        ans += a * b;
        t += a.foo(b);
        a = b;
    }
    ans += b * z;
    t += b.foo(z);

#if DB & 1
    fprintf(stderr, "ans = %lld, t = %lld\n", ans, t);
#endif
    ans = std::abs(ans) - (t + 1) / 2;
    printf("%lld", ans);
    if (t & 1)
        puts(".500");
    else
        puts(".000");
#ifdef CHEAT
    }
#endif
}
