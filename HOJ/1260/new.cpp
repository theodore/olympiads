#include <cstdio>
#include <cstring>
#include <algorithm>

#define UPN(a, b) a = std::min(a, b)

const int max_n = 53;
int n;
char str[max_n], m;
int f[max_n][max_n]['Z' + 7];

int ff(int l, int r, char c)
{
    int& z = f[l][r][c];
    if (z == -1) {
        if (l == r)
            return z = 1;
        if (str[l] == c)
            return z = ff(l + 1, r, c);
        z = ~0u >> 1;
        for (int i = l + 1; i <= r; i++)
            UPN(z, ff(l, i, str[l]) + ff(i, r, c));
    }
    return z;
}

int main()
{
    scanf("%s", str);
    n = std::unique(str, str + strlen(str)) - str;
    m = *std::max_element(str, str + n);
    memset(f, -1, sizeof f);
    int ans = ff(0, n, 'A');
    for (char i = 'B'; i <= m; i++)
        UPN(ans, ff(0, n, i));
    printf("%d\n", ans);
}
