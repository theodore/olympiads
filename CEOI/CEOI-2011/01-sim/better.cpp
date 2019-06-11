#include <stdio.h>
#include <string.h>

typedef long long ll;

const int Max_n = 2000007;
int n, m;
char A[Max_n], B[Max_n];
int sum[128];

int main()
{
    scanf("%s%s", B + 1, A + 1);
    n = strlen(A + 1);
    m = strlen(B + 1);

    ll ans = 0;
    for (int i = 1; i <= n; i++) {
        if (i <= m)
            sum[B[i]]++;
        ans += sum[A[i]];
        if (i >= n - m + 1)
            sum[B[i - (n - m)]]--;
    }
    printf("%lld\n", ans);
}
