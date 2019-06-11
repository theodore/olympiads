#include <cstdio>
#include <cstring>
#include <algorithm>

#define UPN(a, b) a = std::min(a, b)

const int MAX_N = 11;
const int MAX_S = 59057;
int n, m;
int map[MAX_N][MAX_N];
int pow3[MAX_N];

bool Input()
{
    scanf("%d%d", &n, &m);
    if (!n && !m)
        return false;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &map[i][j]);
    return true;
}

int dp[2][MAX_S];

int DP()
{
#define Set(x) memset(x, 0x3f, sizeof (int) * SIZE)
#define U(x, v) UPN(g[x], f[s] + v)
    const int inf = 0x3f3f3f3f;
    const int SIZE = pow3[m + 1];
    int *f = dp[0], *g = dp[1];
    Set(f);
    f[0] = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            Set(g);
            for (int s = 0; s < SIZE; s++) {
                if (f[s] == inf)
                    continue;
#if DB & 1
                fprintf(stderr, "f %d %d %d %d\n", i, j, s, f[s]);
#endif
                const int h = s / pow3[j + 1] % 3, l = s / pow3[j] % 3;
                const int ss = s - h * pow3[j + 1] - l * pow3[j];
                switch (map[i][j]) {
                case 0:
                    if (h == 0 && l == 0) {
                        U(ss, 0);
                        U(ss + 4 * pow3[j], 0);
                        U(ss + 8 * pow3[j], 0);
                    } else if (h == 0) {
                        U(ss + l * pow3[j], 1);
                        U(ss + l * pow3[j + 1], 1);
                    } else if (l == 0) {
                        U(ss + h * pow3[j], 1);
                        U(ss + h * pow3[j + 1], 1);
                    } else if (h == l) {
                        U(ss, 2);
                    }
                    break;
                case 1:
                    if (h == 0 && l == 0)
                        U(ss, 0);
                    break;
                case 2:
                case 3:
                    const int t = map[i][j] - 1;
                    if (h == 0 && l == 0) {
                        U(ss + t * pow3[j], 0);
                        U(ss + t * pow3[j + 1], 0);
                    } else if (h == 0 && l == t) {
                        U(ss, 1);
                    } else if (h == t && l == 0) {
                        U(ss, 1);
                    }
                    break;
                }
            }
            std::swap(f, g);
        }
        if (i != n - 1) {
            Set(g);
            for (int s = 0; s < SIZE / 3; s++)
                g[s * 3] = f[s];
            std::swap(f, g);
        }
    }
    return f[0] == inf ? 0 : f[0];
#undef Set
#undef U
}

int main()
{
    pow3[0] = 1;
    for (int i = 1; i < MAX_N; i++)
        pow3[i] = 3 * pow3[i - 1];
    while (Input())
        printf("%d\n", DP());
}
