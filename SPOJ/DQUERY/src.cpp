#include <cstdio>
#include <algorithm>

#define FOR for (l += N - 1, r += N + 1; l ^ r ^ 1; l >>= 1, r >>= 1)
#define IL if (~l & 1)
#define IR if (r & 1)
#define L (l ^ 1)
#define R (r ^ 1)

const int maxn = 30007;
const int maxN = 1 << 16;
const int maxm = 200007;
const int maxv = 1000007;
int n, m, N;
int num[maxn];
int ans[maxm];
int cnt[maxN];
int pre[maxv];

struct Query
{
    int l, r, id;
    bool operator<(const Query& z) const
    { return r < z.r; }
};

Query q[maxm];

void add(int l, int r)
{
    FOR
    {
	IL ++cnt[L];
	IR ++cnt[R];
    }
}

int ask(int l)
{
    int ret = 0;
    for (l += N; l; l >>= 1)
	ret += cnt[l];
    return ret;
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
	scanf("%d", num + i);
    scanf("%d", &m);
    for (int i = 0; i < m; ++i)
    {
	scanf("%d%d", &q[i].l, &q[i].r);
	q[i].id = i;
    }
    std::sort(q, q + m);
    for (N = 4; N < n + 2; N <<= 1)
	;
    for (int i = 1, j = 0; j < m; ++i)
    {
	add(pre[num[i]] + 1, i);
	pre[num[i]] = i;
	while (i == q[j].r)
	    ans[q[j].id] = ask(q[j].l), ++j;
    }
    for (int i = 0; i < m; ++i)
	printf("%d\n", ans[i]);
}
