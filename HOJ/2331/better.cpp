#include <cstdio>
#include <cstring>
#include <algorithm>

#ifdef LOCAL
# include <cassert>
# define Assert(x) assert(x)
#else
# define Assert(x) 0
#endif

const int maxn = 53;
const int maxm = 13;
const int maxs = 177777;
const int mod = 20110520;
int n, m;
bool obs[maxn][maxn];
int pow3[maxm];

void Init()
{
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++) {
        static char s[maxn];
        scanf("%s", s);
        for (int j = 0; j < m; j++)
            if (s[j] == '*')
                (n < m ? obs[j][i] : obs[i][j]) = true;
    }
    if (n < m)
        std::swap(n, m);
    pow3[0] = 1;
    for (int i = 1; i < maxm; i++)
        pow3[i] = 3 * pow3[i - 1];
}

void Impossible()
{
    puts("0");
    exit(EXIT_SUCCESS);
}

int f[2][maxs]; // 0 -- not crossing
                // 1 -- crossing, not turned
                // 2 -- crossing, turned
int q[maxs * 2], head, tail;

inline void Update(int i, int s, int v)
{
    bool in = true;
    if (!f[i & 1][s])
        in = false;
    f[i & 1][s] += v;
    if (f[i & 1][s] >= mod)
        f[i & 1][s] -= mod;
    if (!in) {
        q[tail++] = i;
        q[tail++] = s;
        if (tail == 2 * maxs)
            tail = 0;
    }
}

int DP()
{
    f[0][0] = 1;
    tail = 2;
    const int SIZE = pow3[m + 1];

    for (int i = 0; i < n; i++) {
        for (int prev = 0; ; ) {
            if (head == tail)
                Impossible();
            int j = q[head];
            if (j == m)
                break;
            head++;
            int s = q[head++];
            if (head == 2 * maxs)
                head = 0;

            if (j != prev) {
                memset(f[prev & 1], 0, sizeof (int) * SIZE);
                prev = j;
            }

            const int here = s / pow3[j] % 9;
            if (obs[i][j]) {
                if (here == 0)
                    Update(j + 1, s, f[j & 1][s]);
            } else {
                const int h = here / 3;
                const int l = here % 3;
                const int ss = s - here * pow3[j];
#define U(t) Update(j + 1, (t), f[j & 1][s])
                if (h == 2) {
                    if (l == 0) {
                        U(ss);                      // 20 -> 00
                        U(ss + 2 * pow3[j]);        // 20 -> 02
                    }
                } else if (l == 2) {
                    if (h == 0) {
                        U(ss);                      // 02 -> 00
                        U(ss + 2 * pow3[j + 1]);    // 02 -> 20
                    }
                } else if (h == 1 && l == 1) {
                    U(ss);                          // 11 -> 00
                } else if (h == 1) {
                    Assert(!l);
                    U(ss + 2 * pow3[j + 1]);        // 10 -> 20
                    U(ss + 1 * pow3[j]);            // 10 -> 01
                } else if (l == 1) {
                    Assert(!h);
                    U(ss + 2 * pow3[j]);            // 01 -> 02
                    U(ss + 1 * pow3[j + 1]);        // 01 -> 10
                } else {
                    Assert(!h);
                    Assert(!l);
                    U(ss + 1 * pow3[j + 1]);        // 00 -> 10
                    U(ss + 1 * pow3[j]);            // 00 -> 01
                    U(ss + 8 * pow3[j]);            // 00 -> 22
                }
#undef U
            }
        }
        if (i < n - 1) {
            // Prepare for next row.
            if ((m & 1) == 0)
                memcpy(f[1], f[0], sizeof (int) * SIZE);
            memset(f[0], 0, sizeof (int) * SIZE);
            while (head != tail) {
                int t = q[head];
                if (t == 0)
                    break;
                head++;
                t = q[head++];
                if (head == 2 * maxs)
                    head = 0;
                if (t / pow3[m] == 0) {
                    f[0][t * 3] = f[1][t];
                    q[tail++] = 0;
                    q[tail++] = t * 3;
                    if (tail == 2 * maxs)
                        tail = 0;
                }
            }
            memset(f[1], 0, sizeof (int) * SIZE);
        }
    }
    return f[m & 1][0];
}

int main()
{
    Init();
    printf("%d\n", DP());
}
