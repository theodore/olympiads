#include <cstdio>
#include <cstring>
#include <algorithm>

#define UPN(a, b) a = std::min(a, b)

const int max_n = 53;
int n;
char str[max_n];
int f[max_n][max_n];

int gg(int l, int r, char c);

int ff(int l, int r)
{
    if (f[l][r] == -1) {
        if (l == r)
            return f[l][r] = 0;
        f[l][r] = ff(l, r - 1);
        for (int i = l; i < r - 1; i++)
            if (str[i] == str[r - 1])
                UPN(f[l][r], ff(l, i) + gg(i + 1, r - 1, str[i]));
        f[l][r]++;
    }
    return f[l][r];
}

int gg(int l, int r, char c)
{
    int ret = ff(l, r);
    static int g[max_n], pre[max_n];
    for (int i = l, p = l - 1; i < r; i++)
        if (str[i] == c) {
            g[i] = ff(l, i);
            for (int j = pre[i] = p; j != l - 1; j = pre[j])
                UPN(g[i], g[j] + ff(j + 1, i));
            UPN(ret, g[i] + ff(i + 1, r));
            p = i;
        }
    return ret;
}

int main()
{
    scanf("%s", str);
    n = std::unique(str, str + strlen(str)) - str;
    memset(f, -1, sizeof f);
    printf("%d\n", ff(0, n));
}
