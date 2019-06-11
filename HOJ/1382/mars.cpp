#include <cstdio>
#include <algorithm>

typedef long long ll;

struct Interval {
    int x, y0, y1;
    int d;
    void init(int a, int b, int c, int z)
    {
        x = a;
        y0 = b;
        y1 = c;
        d = z;
    }
    bool operator<(const Interval& z) const
    { return x < z.x; }
};

const int max_n = 20003;
int n;
int origy[max_n];
Interval intvl[max_n];
int x[max_n], y[max_n];
int ymax;

bool cmpy(const int& a, const int& b)
{
    return y[a] < y[b];
}

void Init()
{
    static int yidx[max_n];
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d%d%d%d", &x[i * 2], &y[i * 2], &x[i * 2 + 1], &y[i * 2 + 1]);

    for (int i = 0; i < n * 2; i++)
        yidx[i] = i;
    std::sort(yidx, yidx + n * 2, cmpy);

    for (int i = 0, now = 0, p = -1; i < n * 2; i++) {
        now += y[yidx[i]] != p;
        origy[now] = p = y[yidx[i]];
        y[yidx[i]] = now;
    }
    ymax = y[yidx[n * 2 - 1]] - 1;

    for (int i = 0; i < n; i++) {
        intvl[i * 2].init(x[i * 2], y[i * 2], y[i * 2 + 1], 1);
        intvl[i * 2 + 1].init(x[i * 2 + 1], y[i * 2], y[i * 2 + 1], -1);
    }
    std::sort(intvl, intvl + (n *= 2));
}

const int max_N = 1 << 16;
int N;
int length[max_N], count[max_N];
int size[max_N];

void U(int z)
{
    if (count[z])
        length[z] = size[z];
    else if (z < N)
        length[z] = length[z << 1] + length[(z << 1) + 1];
    else
        length[z] = 0;
}

void Add(int l, int r, int v)
{
    for (l += N - 1, r += N + 1; l ^ r ^ 1; l >>= 1, r >>= 1) {
        U(l);
        U(r);
        if (~l & 1)
            count[l ^ 1] += v, U(l ^ 1);
        if (r & 1)
            count[r ^ 1] += v, U(r ^ 1);
    }
    U(l);
    U(r);
    for (l >>= 1; l; l >>= 1)
        U(l);
}

ll Calc()
{
    for (N = 4; N < ymax + 2; N <<= 1)
        ;
    for (int i = N + 1; i <= N + ymax; i++)
        size[i] = origy[i - N + 1] - origy[i - N];
    for (int i = N - 1; i; i--)
        size[i] = size[i << 1] + size[(i << 1) + 1];

    ll ans = 0;
    for (int i = 0, p = 0; i < n; i++) {
        ans += length[1] * (intvl[i].x - p);
        p = intvl[i].x;
        Add(intvl[i].y0, intvl[i].y1 - 1, intvl[i].d);
    }
    return ans;
}

int main()
{
    Init();
    printf("%lld\n", Calc());
}
