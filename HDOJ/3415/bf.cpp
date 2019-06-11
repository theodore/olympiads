#include <limits.h>
#include <stdio.h>
#include <string.h>

const int Max_n = 50000;
int n, k;
int sum[Max_n];

int main()
{
    int _;
    for (scanf("%d", &_); _--; ) {
        scanf("%d%d", &n, &k);
        for (int i = 1; i <= n; i++)
            scanf("%d", &sum[i]), sum[i + n] = sum[i];
        for (int i = 1; i <= n + n; i++)
            sum[i] += sum[i - 1];
        int ans = INT_MIN, ansl, ansr;
        for (int i = 0; i < n + n; i++)
            for (int j = 1, t; j <= k && i + j <= n + n; j++)
                if ((t = sum[i + j] - sum[i]) > ans) {
                    ans = t;
                    ansl = i + 1;
                    ansr = i + j;
                }
        if (ansl > n)
            ansl -= n;
        if (ansr > n)
            ansr -= n;
        printf("%d %d %d\n", ans, ansl, ansr);
    }
}
