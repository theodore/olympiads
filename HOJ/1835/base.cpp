#include <cstdio>
#include <cstring>
#include <algorithm>

//#define DB 7

#define L (l ^ 1)
#define R (r ^ 1)
#define IL if (~l & 1)
#define IR if (r & 1)
#define LS(x) ((x) << 1)
#define RS(x) (LS(x) + 1)
#define LN(x) if ((x) < N)
#define U(x) min[x] = std::min(min[LS(x)], min[RS(x)]) + delta[x]
#define UPN(a, b) a = std::min(a, b)

const int max_n = 20007;
const int max_m = 20007;
const int max_N = 1 << 16;
const int inf = 0x3f3f3f3f;

class ST {
public:
    ST(int n);
    void Init(int arr[]);
    void Add(int r, int v); // [0, r)
    int Query(int r); // [0, r)

private:
    int n, N;
    int min[max_N], delta[max_N];
};

int n, m;
int start[max_n], left[max_m], next[max_m], id[max_m], edge;
int cost[max_n], indemnity[max_n];

void Add(int a, int b, int x)
{
    left[++edge] = b;
    next[edge] = start[a];
    start[a] = edge;
    id[edge] = x;
}

void Init()
{
    static int dist[max_n];
    scanf("%d%d", &n, &m);
    for (int i = 2; i <= n; i++)
        scanf("%d", dist + i);
    for (int i = 1; i <= n; i++)
        scanf("%d", cost + i);
    for (int i = 1, x; i <= n; i++) {
        scanf("%d", &x);
        int l = std::lower_bound(dist + 1, dist + n + 1, dist[i] - x) - dist;
        int r = std::upper_bound(dist + 1, dist + n + 1, dist[i] + x) - dist
            - 1;
        Add(r, l, i);
    }
    for (int i = 1; i <= n; i++)
        scanf("%d", indemnity + i);
    n++;
    m++;
}

int Solve()
{
    static int f[max_n];
    static ST seg(n);
    memset(f, 0x3f, sizeof f);
    f[0] = 0;
    for (int i = 1; i <= m; i++) {
        seg.Init(f);
        for (int j = 1; j <= n; j++) {
            f[j] = seg.Query(j) + cost[j];
#if DB & 1
            fprintf(stderr, "\e[1;36m%d %d %d\e[0m\n", i, j, f[j]);
#endif
            for (int e = start[j]; e; e = next[e])
                seg.Add(left[e], indemnity[id[e]]);
        }
    }
    return f[n];
}

int main()
{
    Init();
    printf("%d\n", Solve());
}


ST::ST(int a) : n(a)
{
    for (N = 4; N < n + 2; N <<= 1)
        ;
}

void ST::Init(int num[])
{
    memset(delta, 0, sizeof delta);
    for (int i = N + 1, j = 0; j < n; i++, j++)
        min[i] = num[j];
    for (int i = N - 1; i; i--)
        U(i);
}

void ST::Add(int r, int v)
{
#if DB & 2
    fprintf(stderr, "\e[1;35madd [0, %d), %d\e[0m\n", r, v);
#endif
    int l = N;
    for (r += N + 1; l ^ r ^ 1; l >>= 1, r >>= 1) {
        LN(l) U(l);
        LN(r) U(r);
        IL delta[L] += v, min[L] += v;
        IR delta[R] += v, min[R] += v;
    }
    LN(l) U(l);
    LN(r) U(r);
    for (l >>= 1; l; l >>= 1)
        U(l);
#if DB & 4
    fprintf(stderr, "min:\n");
    for (int i = 1; i < 2 * N; i++) {
        if (min[i] == inf)
            fprintf(stderr, "inf ");
        else
            fprintf(stderr, "%d ", min[i]);
        int t = i + 1;
        if (t - (t & -t) == 0)
            fprintf(stderr, "\n");
    }
    fprintf(stderr, "delta:\n");
    for (int i = 1; i < 2 * N; i++) {
        fprintf(stderr, "%d ", delta[i]);
        int t = i + 1;
        if (t - (t & -t) == 0)
            fprintf(stderr, "\n");
    }
    fprintf(stderr, "\n");
#endif
}

int ST::Query(int r)
{
    int l = N, lans = inf, rans = inf;
    for (r += N + 1; l ^ r ^ 1; l >>= 1, r >>= 1) {
        LN(l) lans += delta[l];
        LN(r) rans += delta[r];
        IL UPN(lans, min[L]);
        IR UPN(rans, min[R]);
    }
    LN(l) lans += delta[l];
    LN(r) rans += delta[r];
    UPN(lans, rans);
    for (l >>= 1; l; l >>= 1)
        lans += delta[l];
    return lans;
}
