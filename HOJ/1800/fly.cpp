#include <cstdio>

const int Max_n = 500;
int n;
int sum[Max_n];

int main()
{
    scanf("%d", &n);
    for (int i = 1, x; i <= n; i++)
        scanf("%d", &x), sum[i] = sum[i - 1] + x;
    if (sum[n] & 1) {
        puts("0");
        return 0;
    }
    int ans = 0;
    for (int i = 1, j = 1; sum[i] <= sum[n] / 2; i++) {
        int v = sum[i] + sum[n] / 2;
        while (sum[j] < v)
            j++;
        if (sum[j] == v)
            ans++;
    }
    printf("%d\n", ans * (ans - 1) / 2);
}
