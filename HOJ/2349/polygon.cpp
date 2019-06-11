#include <cstdio>
#include <cstdlib>

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
}
