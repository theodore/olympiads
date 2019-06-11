#include <cstdio>
#include <algorithm>
#include <cmath>

const int MAXN = 100000;

int N, f[MAXN + 1];

void pre_work() {

    scanf("%d", &N);
    for (int i = 1; i <= N; i++) scanf("%d", f + i);
    std::sort(f + 1, f + N + 1);
}

void work() {

    long long ans = 0;
    for (int i = 2; i <= N; i++)
    {
        int l, r, mid;
        int x = ceil(f[i] * 0.9);
        if (x <= f[i - 1])
        {
            for (l = 0, r = i - 1; mid = (l + r) >> 1, r - l > 1;
                    (x > f[mid] ? l : r) = mid);
            ans += i - r;
        }
    }
    printf("%lld\n", ans);
}

int main() {

    pre_work();
    work();

    return 0;
}
