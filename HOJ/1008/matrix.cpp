#include <cstdio>
#include <cstring>

typedef long long ll;

class Mtrx {
public:
    Mtrx()
    { memset(data, 0, sizeof data); }
    void Set(ll a = 0, ll b = 0, ll c = 0, ll d = 0)
    {
        data[0][0] = a;
        data[0][1] = b;
        data[1][0] = c;
        data[1][1] = d;
    }
    void operator*=(const Mtrx& a)
    { *this = *this * a; }
    ll Val() const
    { return data[0][1]; }

private:
    ll data[2][2];
    friend Mtrx operator*(const Mtrx& a, const Mtrx& b);
};

const int mod = 100003;
ll n, m;
Mtrx base;

Mtrx operator*(const Mtrx& a, const Mtrx& b)
{
    Mtrx ret;
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            for (int k = 0; k < 2; k++)
                ret.data[i][j] += a.data[i][k] * b.data[k][j],
                    ret.data[i][j] %= mod;
    return ret;
}

Mtrx PowerMod()
{
    ll n = ::n - 1;
    Mtrx ret, now;
    ret.Set(1, 0, 0, 1);
    now = base;
    while (n) {
        if (n & 1)
            ret *= now;
        now *= now;
        n >>= 1;
    }
    return ret;
}

ll Solve()
{
    base.Set(m % mod, 1, 0, (m - 1) % mod);
    Mtrx a;
    a.Set(1, 0);
    return (a * PowerMod()).Val() * (m % mod) % mod;
}

int main()
{
    scanf("%lld%lld", &m, &n);
    if (n <= 1)
        puts("0");
    else
        printf("%lld\n", Solve());
}
