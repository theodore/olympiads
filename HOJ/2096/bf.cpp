#include <cctype>
#include <climits>
#include <cstdio>
#include <algorithm>

#define UPN(a, b) a = std::min(a, b)
#define UPX(a, b) a = std::max(a, b)

#define FOR for (l += N - 1, r += N + 1; l ^ r ^ 1; l >>= 1, r >>= 1)
#define IL if (~l & 1)
#define IR if (r & 1)
#define L (l ^ 1)
#define R (r ^ 1)
#define LS(x) ((x) << 1)
#define RS(x) (LS(x) + 1)

const int Max_n = 3000007;
const int Max_N = 1 << 23;

int n, m, N;
int max[Max_N], min[Max_N];

void Add(int p, int x)
{
    p += N;
    max[p] = min[p] = x;
    while (p >>= 1, p) {
        max[p] = std::max(max[LS(p)], max[RS(p)]);
        min[p] = std::min(min[LS(p)], min[RS(p)]);
    }
}

int Get(int l, int r)
{
    int maxl = 0, maxr = 0;
    int minl = INT_MAX, minr = INT_MAX;
    FOR {
        IL UPN(minl, min[L]), UPX(maxl, max[L]);
        IR UPN(minr, min[R]), UPX(maxr, max[R]);
    }
    UPX(maxl, maxr);
    UPN(minl, minr);
#if DB & 1
    fprintf(stderr, "maxl = %d, minl = %d\n", maxl, minl);
#endif
    return maxl - minl;
}

int getint()
{
    int c;
    while (!isdigit(c = getchar()))
        ;
    int x = c - '0';
    while (isdigit(c = getchar()))
        x = x * 10 + c - '0';
    return x;
}

int main()
{
    m = getint();
    n = getint();
    for (N = 4; N < n + 2; N <<= 1)
        ;
    int ans = 0;
    for (int i = 1, x; i <= n; i++) {
        x = getint();
        Add(i, x);
        int l = 1, r = i + 1;
        while (r - l > 1) {
            int mid = (l + r) / 2;
#if DB & 1
            fprintf(stderr, "mid = %d\n", mid);
#endif
            (Get(i - mid + 1, i) <= m ? l : r) = mid;
        }
        UPX(ans, l);
#if DB & 1
        fprintf(stderr, "i = %d, ans = %d\n\n", i, ans);
#endif
    }
    printf("%d\n", ans);
}
