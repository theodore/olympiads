#include <cctype>
#include <cstdio>
#include <algorithm>
#include <utility>

struct SortMe {
    SortMe(){}
    SortMe(int a, int b) : val(a), idx(b) {}
    int val, idx;
    bool operator<(const SortMe& z) const
    { return val < z.val || (val == z.val && idx < z.idx); }
};

bool cmpval(const SortMe& a, const SortMe& b)
{
    return a.val < b.val;
}

bool cmpidx(const SortMe& a, const SortMe& b)
{
    return a.idx < b.idx;
}

const int max_n = 300007;
const int max_b = 16;
int n;
int pre[max_b][max_n];
SortMe sortme[max_n];

int Get(int l, int r)
{
    int ret = 0;
    for (int b = 0; b < max_b; b++)
        if (pre[b][r] - pre[b][l - 1] > (r - l + 1) / 2)
            ret ^= 1 << b;
    return ret;
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
    n = getint();
    getint();
    for (int i = 0, x; i < n; i++) {
        x = getint();
        for (int b = 0; b < max_b; b++) {
            pre[b][i + 1] = pre[b][i];
            if (x & (1 << b))
                pre[b][i + 1]++;
        }
        sortme[i].val = x;
        sortme[i].idx = i + 1;
    }
    std::sort(sortme, sortme + n);
    for (int q = getint(); q--; ) {
        int l, r;
        l = getint();
        r = getint();
        int t = Get(l, r);
        std::pair<SortMe*, SortMe*> range = std::equal_range(sortme, sortme + n,
                SortMe(t, 0), cmpval);
        if (std::upper_bound(range.first, range.second, SortMe(0, r), cmpidx)
                - std::lower_bound(range.first, range.second, SortMe(0, l), cmpidx)
                > (r - l + 1) / 2)
            printf("yes %d\n", t);
        else
            puts("no");
    }
}
