#include <cstdio>

int main()
{
    typedef long long ll;
    ll n;
    scanf("%lld", &n);
    n--;
    const int Max_n = 40003;
    static ll f[Max_n];
    for (ll i = n; i; i--) {
        f[i] = (n / i) * (n / i);
        for (ll j = 2 * i; j <= n; j += i)
            f[i] -= f[j];
    }
    printf("%lld\n", f[1] + 2);
}
