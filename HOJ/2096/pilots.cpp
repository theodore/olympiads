#include <cctype>
#include <climits>
#include <cstdio>
#include <algorithm>

#define UPN(a, b) a = std::min(a, b)
#define UPX(a, b) a = std::max(a, b)

const int Max_n = 3000007;

int n, m;
int num[Max_n];
int premax[Max_n], premin[Max_n];

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
    for (int i = 0; i < n; i++)
        num[i] = getint();
    num[n] = -1;
    for (int i = n - 1; i >= 0; i--)
        for (int& x = premin[i] = i + 1; num[x] >= num[i]; x = premin[x])
            ;
    num[n] = INT_MAX;
    for (int i = n - 1; i >= 0; i--)
        for (int& x = premax[i] = i + 1; num[x] <= num[i]; x = premax[x])
            ;
    int ans = 0;
    for (int l = 0, r = 0, maxid = 0, minid = 0, v; r < n; r++) {
        if ((v = num[r]) < num[minid]) {
            minid = r;
            while (num[maxid] - v > m)
                for (l = ++maxid; premax[maxid] <= r; maxid = premax[maxid])
                    ;
        } else if ((v = num[r]) > num[maxid]) {
            maxid = r;
            while (v - num[minid] > m)
                for (l = ++minid; premin[minid] <= r; minid = premin[minid])
                    ;
        }
        UPX(ans, r - l + 1);
    }
    printf("%d\n", ans);
}
