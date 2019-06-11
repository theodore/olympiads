#include <cstdio>
#include <algorithm>

const int max_n = 203;
int n, m;
bool bad[max_n][max_n];

int main()
{
    scanf("%d%d", &n, &m);
    while (m--) {
        int a, b;
        scanf("%d%d", &a, &b);
        if (a > b)
            std::swap(a, b);
        bad[a][b] = true;
    }
    int ans = 0;
    for (int i = 1; i <= n; i++)
        for (int j = i + 1; j <= n; j++)
            if (!bad[i][j])
                for (int k = j + 1; k <= n; k++)
                    if (!bad[i][k] && !bad[j][k])
                        ans++;
    printf("%d\n", ans);
}
