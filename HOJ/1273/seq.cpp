#include <cstdio>

const int max_p = 16;
const int max_v = 0xffff + 11;
int n, m;
int pre[max_p][max_v];

void Init()
{
    scanf("%d%d", &n, &m);
    for (int i = 1, x; i <= n; i++) {
        scanf("%d", &x);
        for (int j = 0; j < max_p; j++)
            pre[j][x % (1 << (j + 1)) + 1]++;
    }
    for (int i = 0; i < max_p; i++)
        for (int j = 1; j <= 1 << (i + 1); j++)
            pre[i][j] += pre[i][j - 1];
}

void Solve()
{
    int sum = 0;
    long long ans = 0;
    while (m--) {
        char c;
        int x;
        scanf("\n %c%d", &c, &x);
        if (c == 'A') {
            sum += x;
            sum &= 0xffff;
        } else {
            if (x > 15)
                continue;
            int l, r;
            l = (1 << x);
            r = (1 << (x + 1)) - 1;
            int mod = 1 << (x + 1);
            l = ((l - sum) % mod + mod) % mod;
            r = ((r - sum) % mod + mod) % mod;
            r++;
            if (r >= l)
                ans += pre[x][r] - pre[x][l];
            else
                ans += n - (pre[x][l] -pre[x][r]);
        }
    }
    printf("%lld\n", ans);
}

int main()
{
    Init();
    Solve();
}
