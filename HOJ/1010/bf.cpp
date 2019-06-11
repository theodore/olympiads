#include <cstdio>
#include <algorithm>

#define UPN(a, b) a = std::min(a, b)

typedef long long ll;

const int Max_n = 50007;
int n, L;
int leng[Max_n];
ll sum[Max_n];
ll f[Max_n];

void Input()
{
    scanf("%d%d", &n, &L);
    for (int i = 1; i <= n; i++)
        scanf("%d", &leng[i]), sum[i] = sum[i - 1] + leng[i];
}

ll Work()
{
    for (int i = 1; i <= n; i++) {
        ll t = sum[i] + i - 1 - L;
        f[i] = f[0] + t * t;
        int opt = 0;
        for (int j = 1; j < i; j++) {
            t = sum[i] - sum[j] + i - j - 1 - L;
            ll z = f[i];
            UPN(f[i], f[j] + t * t);
            if (z != f[i])
                opt = j;
        }
#if DB & 1
        fprintf(stderr, "%d <- %d\n", i, opt);
#endif
    }
    return f[n];
}

int main()
{
    Input();
    printf("%lld\n", Work());
}
