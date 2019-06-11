#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

namespace
{
    typedef long long ll;
    struct player
    {
	int h, v;
	ll c;
	bool operator<(const player& x) const
	{
	    return c < x.c;
	}
    };
    const int maxn = 5003;
    const int maxv = 10003;
    int n;
    player man[maxn];
    ll A, B, C;
    int vi[maxn];
    int cnt[maxv];

    bool cmpv(const int&, const int&);
}

bool cmpv(const int& a, const int& b)
{
    return man[a].v < man[b].v;
}

int main()
{
    std::cin >> n >> A >> B >> C;
    for (int i = 0; i < n; ++i)
    {
	scanf("%d%d", &man[i].h, &man[i].v);
	man[i].c = A * man[i].h + B * man[i].v;
	vi[i] = i;
    }
    std::sort(man, man + n);
#ifdef DB
    fprintf(stderr, "%d %lld %lld %lld\n", n, A, B, C);
    for (int i = 0; i < n; ++i)
	fprintf(stderr, "%d %d\n", man[i].h, man[i].v);
#endif
    std::sort(vi, vi + n, ::cmpv);
    int ans = 0;
    for (int i = 0; i < n; ++i)
    {
	const int minh = man[i].h;
	int now = 0, k = 0;
	memset(cnt, 0, sizeof cnt);
	for (int j = 0; j < n; ++j)
	{
	    const int minv = man[vi[j]].v;
	    if (man[vi[j]].h < minh || man[i].v < minv)
		continue;
	    const ll lim = A * minh + B * minv + C;
	    if (man[i].c > lim || man[vi[j]].c > lim)
		continue;
	    for (; k < n && man[k].c <= lim; ++k)
		if (man[k].h >= minh && man[k].v >= minv)
		{
		    ++now;
		    ++cnt[man[k].v];
		}
	    ans = std::max(ans, now);
	    now -= cnt[minv];
	    cnt[minv] = 0;
	}
    }
    printf("%d\n", ans);
}
