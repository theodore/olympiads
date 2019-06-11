#include <cctype>
#include <cstdio>
#include <algorithm>
#include <utility>
#include <vector>


const int max_n = 300007;
const int max_b = 16;
int n;
int pre[max_b][max_n];
std::vector<int> vec[10007];

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
        vec[x].push_back(i + 1);
    }
    for (int q = getint(); q--; ) {
        int l, r;
        l = getint();
        r = getint();
        int t = Get(l, r);
        if (std::upper_bound(vec[t].begin(), vec[t].end(), r)
                - std::lower_bound(vec[t].begin(), vec[t].end(), l)
                > (r - l + 1) / 2)
            printf("yes %d\n", t);
        else
            puts("no");
    }
}
