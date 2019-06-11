#include <stdio.h>
#include <string.h>

typedef long long ll;

const int Max_n = 2000007;
int n, m;
char A[Max_n], B[Max_n];
int sum[Max_n];

int main()
{
    scanf("%s%s", B + 1, A + 1);
    n = strlen(A + 1);
    m = strlen(B + 1);

    ll ans = 0;
    for (char c = 'a'; c <= 'z'; c++) {
        for (int i = 1; i <= n; i++)
            sum[i] = sum[i - 1] + (A[i] == c);
        for (int i = 1; i <= m; i++)
            if (B[i] == c)
                ans += sum[n - m + i] - sum[i - 1]; 
    }
    printf("%lld\n", ans);
}
