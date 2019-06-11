#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>

typedef long long ll;

const int maxn = 1000003;
int n;
int num[maxn];
ll sum[maxn];

void getint(int& x)
{
    scanf("%d", &x);
    return;
    int c;
    while ((c = getchar()) < '0' || c > '9')
	;
    x = c - '0';
    while ((c = getchar()) >= '0' && c <= '9')
	x = x * 10 + c - '0';
#if DB >= 1
    fprintf(stderr, "got %d\n", x);
#endif
}

int main()
{
    getint(n);
    ll t = 0;
    for (int i = 1; i <= n; ++i)
	getint(num[i]), t += num[i];
    t /= n;
    for (int i = 1; i <= n; ++i)
	sum[i] = sum[i - 1] + (num[i] -= int(t));
    std::nth_element(sum + 1, sum + (t = n / 2 + 1), sum + n + 1);
    ll ans = 0;
    for (int i = 1; i <= n; ++i)
	ans += std::abs(sum[i] - sum[t]);
    std::cout << ans << std::endl;
}
