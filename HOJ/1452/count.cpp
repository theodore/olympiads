#include <cctype>
#include <cstdio>

#define LB(x) ((x) & -(x))

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

const int maxn = 303;
const int maxc = 103;
int n, m;

class BIT {
public:
    void Add(int x, int y, int d);
    int Query(int x0, int y0, int x1, int y1);
private:
    int Query(int x, int y);
    int data[maxn][maxn];
};

void BIT::Add(int x, int y, int d)
{
    for (int i = x; i <= n; i += LB(i))
        for (int j = y; j <= m; j += LB(j))
            data[i][j] += d;
}

int BIT::Query(int x0, int y0, int x1, int y1)
{
    return Query(x1, y1) + Query(x0 - 1, y0 - 1)
        - Query(x1, y0 - 1) - Query(x0 - 1, y1);
}

int BIT::Query(int x, int y)
{
    int ret = 0;
    for (int i = x; i; i -= LB(i))
        for (int j = y; j; j -= LB(j))
            ret += data[i][j];
    return ret;
}

BIT bit[maxc];
int color[maxn][maxn];

void Init()
{
    n = getint();
    m = getint();
    int x;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
            x = getint();
            color[i][j] = x;
            bit[x].Add(i, j, 1);
        }
}

void Solve()
{
    for (int _ = getint(); _--; ) {
        int cmd;
        cmd = getint();
        if (cmd == 1) {
            int x, y, c;
            x = getint();
            y = getint();
            c = getint();
            if (color[x][y] != c) {
                bit[color[x][y]].Add(x, y, -1);
                bit[color[x][y] = c].Add(x, y, 1);
            }
        } else {
            int x0, y0, x1, y1, c;
            x0 = getint();
            x1 = getint();
            y0 = getint();
            y1 = getint();
            c = getint();
            printf("%d\n", bit[c].Query(x0, y0, x1, y1));
        }
    }
}

int main()
{
    Init();
    Solve();
}
