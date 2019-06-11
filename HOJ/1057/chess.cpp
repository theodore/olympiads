#include <cctype>
#include <cstdio>
#include <algorithm>

#define UPX(a, b) a = std::max(a, b)
#define UPN(a, b) a = std::min(a, b)

const int maxn = 2003;
int n, m;
int board[maxn][maxn];
int leftmost[maxn][maxn], upmost[maxn][maxn];

int Get_int()
{
    int c;
    while (!isdigit(c = getchar()))
        ;
    int x = c - '0';
    while (isdigit(c = getchar()))
        x = x * 10 + c - '0';
    return x;
}

int Get_Single_int()
{
    int c;
    while (!isdigit(c = getchar()))
        ;
    return c - '0';
}

void Input()
{
    n = Get_int();
    m = Get_int();
    for (int i = 0; i <= m; ++i)
        board[0][i] = -1;
    for (int i = 0; i <= n; ++i)
        board[i][0] = -1;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            board[i][j] = Get_Single_int();
}

namespace Square
{
    int f[maxn][maxn];

    void Solve()
    {
        int ans = 0;
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= m; ++j) {
                if ((board[i][j] ^ board[i][j - 1]) == 1)
                    leftmost[i][j] = leftmost[i][j - 1] + 1;
                else
                    leftmost[i][j] = 1;
                if ((board[i][j] ^ board[i - 1][j]) == 1)
                    upmost[i][j] = upmost[i - 1][j] + 1;
                else
                    upmost[i][j] = 1;

                if ((board[i][j] ^ board[i - 1][j]) == 1) {
                    if (leftmost[i][j] <= f[i - 1][j])
                        f[i][j] = leftmost[i][j];
                    else if (upmost[i][j - f[i - 1][j]] <= f[i - 1][j])
                        f[i][j] = f[i - 1][j];
                    else
                        f[i][j] = f[i - 1][j] + 1;
                } else {
                    f[i][j] = 1;
                }
                UPX(ans, f[i][j]);
            }
        printf("%d\n", ans * ans);
    }
}

namespace Rectangle
{
    int prev[maxn];

    void Solve()
    {
        int ans = 0;
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                for (int& x = prev[j] = j - 1;
                        upmost[i][x] >= upmost[i][j]; x = prev[x])
                    ;
            }

            for (int j = m, rlim; j >= 1; --j) {
                const int left = std::max(prev[j], j - leftmost[i][j]);
                for (int& x = prev[j] = j + 1;
                        upmost[i][x] >= upmost[i][j]; x = prev[x])
                    ;
                if ((board[i][j] ^ board[i][j + 1]) != 1)
                    rlim = j;

                UPX(ans, (std::min(prev[j] - 1, rlim) - left) * upmost[i][j]);
            }
        }
        printf("%d\n", ans);
    }
}

int main()
{
    Input();
    Square::Solve();
    Rectangle::Solve();
}
