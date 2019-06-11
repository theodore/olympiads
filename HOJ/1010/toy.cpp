#include <cstdio>
#include <algorithm>
#include <queue>

#define UPN(a, b) a = std::min(a, b)

typedef long long ll;

const int Max_n = 50007;
int n, L;
int leng[Max_n];
ll sum[Max_n];
ll f[Max_n];

//inline ll A(int x) { return sum[x] + x - 1 - L; }
//inline ll B(int x) { return sum[x] + x; }
inline ll A(int x) { return sum[x] + x; }
inline ll B(int x) { return sum[x] + x + L + 1; }
inline ll g(int x) { return f[x] + B(x) * B(x); }

void Input()
{
    scanf("%d%d", &n, &L);
    for (int i = 1; i <= n; i++)
        scanf("%d", &leng[i]), sum[i] = sum[i - 1] + leng[i];
}

inline bool slopelteq(int a, int b, ll slp)
{
    if (a < b)
        std::swap(a, b);
    return double(g(a) - g(b)) / (B(a) - B(b)) <= slp;
    return slp * (B(a) - B(b)) >= g(a) - g(b);
}

inline bool should_pop(int a, int b, int c)
{
    return double(g(c) - g(a)) / (B(c) - B(a)) <= double(g(b) - g(a)) / (B(b) - B(a));
    return (g(c) - g(a)) * (B(b) - B(a)) <= (g(b) - g(a)) * (B(c) - B(a));
}

ll Work()
{
    std::deque<int> q;
    q.push_back(0);
    for (int i = 1, j = 0; i <= n; i++) {
        while (j + 1 < q.size() && slopelteq(q[j + 1], q[j], 2 * A(i)))
            j++;
        int t = q[j];
#if DB & 1
        fprintf(stderr, "%d <- %d, size = %d\n", i, t, q.size());
#endif
        f[i] = f[t] + (A(i) - B(t)) * (A(i) - B(t));
        while ((t = q.size()) >= 2 && should_pop(q[t - 2], q[t - 1], i))
            q.pop_back();
        q.push_back(i);
        UPN(j, (int)q.size() - 1);
    }
    return f[n];
}

int main()
{
    Input();
    printf("%lld\n", Work());
#if DB & 1
    fprintf(stderr, "sum:");
    for (int i = 0; i < n; i++)
        fprintf(stderr, " %lld", sum[i]);
    fprintf(stderr, "\nf:");
    for (int i = 0; i < n; i++)
        fprintf(stderr, " %lld", f[i]);
    fprintf(stderr, "\nA:");
    for (int i = 0; i < n; i++)
        fprintf(stderr, " %lld", A(i));
    fprintf(stderr, "\nB:");
    for (int i = 0; i < n; i++)
        fprintf(stderr, " %lld", B(i));
    fprintf(stderr, "\ng:");
    for (int i = 0; i < n; i++)
        fprintf(stderr, " %lld", g(i));
#endif
}
