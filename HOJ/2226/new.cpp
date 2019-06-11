#include <cstdio>
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

int main()
{
    int _, n = 0;
    scanf("%d", &_);
    for (int i = 0; i < _; ++i)
	scanf("%d", ask + i), n = std::max(n, ask[i]);
    init(n);
    for (int i = 0; i < _; ++i)
	//printf("%lld\n", ask[i] * (tmp[ask[i]] - (ask[i] != lpf[ask[i]])) / 2 + ask[i]);
	printf("%lld\n", ask[i] * (tmp[ask[i]] - 1) / 2 + ask[i]);
}
