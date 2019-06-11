#include <cstdio>

#define Hash(i, j) \
    (str[i][j] * 12347 % base)

typedef unsigned int Hash_t;

const int max_n = 1007;
const Hash_t base = 137;
int n, m, a, b;
char str[max_n][max_n];
typedef Hash_t S[max_n][max_n];
S row_pre, row_num, col_pre, col_num;
Hash_t pow[max_n];

void Init()
{
    scanf("%d%d%d%d", &n, &m, &a, &b);
    for (int i = 1; i <= n; i++) {
        scanf("%s", str[i] + 1);
        for (int j = 1; j <= m; j++)
            row_pre[i][j] = row_pre[i][j - 1] * base + Hash(i, j);
    }
    pow[0] = 1;
    for (int i = 1; i < max_n; i++)
        pow[i] = pow[i - 1] * base;
    for (int i = 1; i <= n; i++)
        for (int j = b; j <= m; j++) {
            row_num[i][j] = row_pre[i][j] - row_pre[i][j - b] * pow[b];
            col_pre[i][j] = col_pre[i - 1][j] * pow[b] + row_num[i][j];
        }
    Hash_t baseAB = 1;
    for (int i = 0; i < a * b; i++)
        baseAB *= base;
    for (int i = a; i <= n; i++)
        for (int j = b; j <= m; j++)
            col_num[i][j] = col_pre[i][j] - col_pre[i - a][j] * baseAB;
}

void Solve()
{
    int q;
    for (scanf("%d", &q); q--; ) {
        Hash_t now = 0;
        for (int i = 1; i <= a; i++) {
            scanf("%s", str[i] + 1);
            for (int j = 1; j <= b; j++)
                now = now * base + Hash(i, j);
        }
        for (int i = a; i <= n; i++)
            for (int j = b; j <= m; j++)
                if (now == col_num[i][j]) {
                    puts("1");
                    goto next;
                }
        puts("0");
next:;
    }
}

int main()
{
    Init();
    Solve();
}
