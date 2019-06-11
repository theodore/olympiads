#include <cstdio>
#include <algorithm>

const int max_n = 100003;
int n;
int num[max_n];

int main()
{
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", num + i);
    std::sort(num, num + n);
    long long ans = 0;
    for (int i = 1, j = 0; i < n; i++) {
        int x = (num[i] * 9 + 9) / 10;
        while (j < i && num[j] < x)
            j++;
        ans += i - j;
    }
    printf("%lld\n", ans);
}
