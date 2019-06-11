#include <cstdio>
#include <cstring>
#include <cstdlib>

typedef long long ll;

ll M, N;

void pre_work() {

    scanf("%lld %lld", &M, &N);

}

#define MODP 100003

ll super_pow(ll base,ll pow) {

    ll ac = base, res = 1;
    while (pow)
    {
        if (pow & 1) res = (res * ac) % MODP;
        ac = (ac * ac) % MODP;
        pow >>= 1LL;
    }
    return res;
}

void work() {

    ll ans = ((super_pow(M, N - 1) - super_pow(M - 1, N - 1)) * M) % MODP;
    while (ans < 0) ans += MODP;
    printf("%d\n", (int)ans);
}

int main() {

    pre_work();
    work();
    return 0;
}
