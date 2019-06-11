#include <cstdio>
#include <cctype>
#include <algorithm>

typedef long long ll;
const int max_ = 300007;
const int maxn = 1000007;
const int maxp = 78511;
int p[maxp], pc;
int ask[max_];
int lpf[maxn], pre[maxn], pfp[maxn]; // lpf - lowest prime factor, pfp - prime factor power
int phi[maxn];
ll tmp[maxn];
ll sum[maxn];

void init(const int n)
{
    static int not_p[maxn / 5 + 1];
    tmp[1] = 1;
    phi[1] = 1;
    for (int i = 2; i <= n; ++i)
    {
	if (!(not_p[i >> 5] >> (i & 31) & 1))
	    p[pc++] = i, lpf[i] = i, pre[i] = 1, pfp[i] = i, phi[i] = i - 1, tmp[i] = (ll)i * phi[i] + 1, sum[i] = tmp[i];
	for (int j = 0, bdry = n / i; p[j] <= bdry; ++j)
	{
	    const int z = p[j] * i;
	    not_p[z >> 5] |= 1 << (z & 31);
	    lpf[z] = p[j];
	    if (p[j] == lpf[i])
	    {
		pre[z] = pre[i];
		pfp[z] = pfp[i] * p[j];
	    }
	    else
	    {
		pre[z] = i;
		pfp[z] = p[j];
	    }
	    if (pre[z] == 1)
		phi[z] = pfp[z] - pfp[z] / p[j];
	    else
		phi[z] = phi[pfp[z]] * phi[pre[z]];
	    // if (p[j] == lpf[i])
	    if (pre[z] == 1)
	    {
		sum[z] = sum[z / p[j]] + (ll)z * phi[z];
	    }
		tmp[z] = sum[pfp[z]] * (tmp[pre[z]]);
	    //else
	    //tmp[z] = sum[pfp[z]] * sum[pre[z]];
	    if (p[j] == lpf[i])
		break;
	}
    }
    phi[1] = 0;
}

void getint(int& x)
{
    int c;
    while (!isdigit(c = getchar()))
	;
    x = c - '0';
    while (isdigit(c = getchar()))
	x = x * 10 + c - '0';
}

char outs[19 * maxn], *ptr = outs + 19 * maxn;

void out(ll z)
{
    while (z)
	*--ptr = z % 10 + '0', z /= 10;
    *--ptr = '\n';
}

int main()
{
    int _, n = 0;
    getint(_);
    for (int i = 0; i < _; ++i)
	getint(ask[i]), n = std::max(n, ask[i]);
    init(n);
    for (int i = _ - 1; i >= 0; --i)
	out(ask[i] * (tmp[ask[i]] - 1) / 2 + ask[i]);
    puts(ptr + 1);
}
