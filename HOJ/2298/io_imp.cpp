#include <cctype>
#include <cstdio>
#include <algorithm>

#define UPX(a, b) a = std::max(a, b)
#define UPN(a, b) a = std::min(a, b)

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

struct Interval {
    int l, r, v;
    void inc()
    {
        ++v;
        UPN(v, r - l + 1);
    }
    bool operator==(const Interval& z) const
    { return l == z.l && r == z.r; }
    bool operator<(const Interval& z) const
    {
        if (r != z.r)
            return r < z.r;
        else
            return l < z.l;
    }
    bool operator<(const int z) const
    { return r < z; }
};

const int max_n = 100003;
int n;
Interval intvl[max_n];
int f[max_n];

int main()
{
    n = getint();
    int m = 1;
    for (int i = 1, a, b; i <= n; i++) {
        a = getint();
        b = getint();
        if (a + b < n) {
            intvl[m].l = a;
            intvl[m].r = n - b - 1;
            intvl[m].v = 1;
            m++;
        }
    }
    std::sort(intvl + 1, intvl + m);
    for (int i = 1, j = 2; j < m || ((m = i + 1) & 0); j++) {
        if (intvl[i] == intvl[j])
            intvl[i].inc();
        else
            intvl[++i] = intvl[j];
    }
    intvl[0].r = -1;
    for (int i = 1; i < m; i++) {
        f[i] = f[i - 1];
        int j = std::lower_bound(intvl, intvl + i, intvl[i].l) - intvl;
        if (j)
            UPX(f[i], f[j - 1] + intvl[i].v);
    }
    printf("%d\n", n - f[m - 1]);
}
