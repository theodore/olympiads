#include <cstdio>
#include <iostream>
#include <algorithm>
#include <climits>
#include <cstring>
#define foreach(e,x) for(__typeof(x.begin()) e=x.begin();e!=x.end();++e)
using namespace std;

const int MOD = int(1e9) - 401;
const int PHI = MOD - 1;
const int DIVISORS[] = { 2, 13, 5281, 7283 };
const int MAX_DIV = 10000;

int fact[MAX_DIV];

bool isPrime(int x) {
    for (int i = 2; i * i <= x; i++)
	if (x % i == 0)
	    return false;
    return true;
}

int calc(int n) {
    int ret = 0;
    for (int k = 1; k <= n; k++) {
	if (n % k == 0) {
	    int div = 1;
	    for (int j = 0; j < (n / k); ++j) {
		div *= fact[k];
	    }
	    div *= fact[n / k];
	    ret += fact[n] / div;
	}
    }
    return ret;
}

void decompose(int x) {
    bool first = true;
    for (int i = 2; i * i <= x; ++i) {
	if (x % i == 0) {
	    int cnt = 0;
	    while (x % i == 0)
		++cnt, x /= i;
	    if (!first)
		cout << "*";
	    first = false;
	    cout << i;
	    if (cnt > 1)
		cout << "^" << cnt;
	}
    }
    if (x > 1) {
	if (!first)
	    cout << "*";
	first = false;
	cout << x;
    }
    cout << endl;
}

    int powMod(int x, int e, int mod) {
	if (!e)
	    return 1;
	if (e & 1)
	    return 1LL * powMod(x, e - 1, mod) * x % mod;
	return powMod(1LL * x * x % mod, e >> 1, mod);
    }

struct Result {
    int ret;
    int pCount;
    Result(int _ret, int _pCount) :
	ret(_ret), pCount(_pCount) {
	}
    Result pow(int p, int mod) {
	return Result(powMod(ret, p, mod), pCount * p);
    }
};

inline int invMod(int x, int mod) {
    return powMod(x, mod - 2, mod);
}

Result divide(Result a, Result b, int mod) {
    return Result(a.ret * invMod(b.ret, mod) % mod, a.pCount - b.pCount);
}

Result multiply(Result a, Result b, int mod) {
    return Result(a.ret * b.ret % mod, a.pCount + b.pCount);
}

Result calcFactMod(int n, int p) {
    //n!%p
    if (!n) {
	return Result(1, 0);
    }
    int ret = 1, cnt = n / p;
    int step = fact[p - 1] % p;
    ret = powMod(step, cnt, p);
    for (int i = cnt * p + 1; i <= n; ++i) {
	int tmp = i - cnt * p;
	(ret *= tmp) %= p;
    }

    Result now = Result(ret, cnt);
    now = multiply(now, calcFactMod(n / p, p), p);
    return now;
}

typedef long long int64;

void extGcd(int64 a, int64 b, int64&x, int64&y) {
    if (!b) {
	x = 1;
	y = 0;
	return;
    }
    extGcd(b, a % b, y, x);
    y -= a / b * x;
}

int countDivides(int n, int k) {
    //n!/( (k!)^(n/k)*(n/k)! ) % PHI
    int rets[4];
    for (int i = 0; i < 4; ++i) {
	int mod = DIVISORS[i];
	Result rn = calcFactMod(n, mod);
	Result rk = calcFactMod(k, mod);
	Result rndk = calcFactMod(n / k, mod);
	Result div = multiply(rk.pow(n / k, mod), rndk, mod);
	Result cur = divide(rn, div, mod);
	if (cur.pCount > 0) {
	    rets[i] = 0;
	} else {
	    rets[i] = cur.ret;
	}
    }

    int64 ans = 0;
    for (int i = 0; i < 4; ++i) {
	int64 m = DIVISORS[i], M = PHI / m;
	int64 x, y;
	extGcd(m, M, x, y);
	//x*m+M*y = 1
	int64 me = M * y % PHI;
	if (me < 0)
	    me += PHI;
	(ans += me * rets[i] % PHI) %= PHI;
    }

    return ans;
}

int calcWays(int n) {
    int ret = 0;
    int k;
    for (k = 1; k * k < n; ++k) {
	if (n % k == 0) {
	    (ret += countDivides(n, k)) %= PHI;
	    (ret += countDivides(n, n / k)) %= PHI;
	}
    }
    if (k * k == n)
	(ret += countDivides(n, k)) %= PHI;
    return ret;
}

int calcAns(int n, int m) {
    int pow = calcWays(n);
    int ret = powMod(m, pow, MOD);
    return ret;
}

void prepareFact() {
    fact[0] = 1;
    for (int i = 1; i < MAX_DIV; ++i) {
	fact[i] = 1LL * fact[i - 1] * i % PHI;
    }
}

void solve() {
    prepareFact();
    int nT;
    cin >> nT;
    for (int i = 0; i < nT; ++i) {
	int n, m;
	cin >> n >> m;
	cout << calcAns(n, m) << endl;
    }
}

int main() {
    solve();
}
