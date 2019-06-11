#include <cstdio>
#include <cstring>
#include <queue>
#include <iostream>
#include <algorithm>

#ifdef LOCAL
# include <cassert>
# define Assert(x) assert(x)
#else
# define Assert(x) 0
#endif

#define IL if (~l & 1)
#define IR if (r & 1)
#define L (l ^ 1)
#define R (r ^ 1)
#define FLGS bool fl = false, fr = false
#define FL if (fl)
#define FR if (fr)
#define LT fl = true
#define RT fr = true
#define LS(x) ((x) << 1)
#define RS(x) (LS(x) + 1)

typedef long long ll;
const int maxn = 100007;
const int maxN = 1 << 18;
const ll inf = ~0ull >> 1;
int n;
ll m;
int num[maxn];
ll sum[maxn], ans[maxn];
int pre[maxn];

int N;
//ll sgf[maxN], sgans[maxN];
//int sgmax[maxN];
ll sgv[maxN];
ll sgm[maxN];

void sg_init();
ll sg_ask(int, int);
void sg_set(int, ll);
void sg_set(int, int, ll);

void sg_set(int p, ll v)
{
    sg_set(p, p, v);
}

void sg_putdown(int l, int r)
{
    if (!l)
	return;
    sg_putdown(l >> 1, r >> 1);
    if (sgm[l] && l < N)
    {
	sgv[LS(l)] = sgm[LS(l)] = sgm[l];
	sgv[RS(l)] = sgm[RS(l)] = sgm[l];
	sgm[l] = 0;
    }
    if (sgm[r] && r < N)
    {
	sgv[LS(r)] = sgm[LS(r)] = sgm[r];
	sgv[RS(r)] = sgm[RS(r)] = sgm[r];
	sgm[r] = 0;
    }
}

void sg_set(int l, int r, ll v)
{
    sg_putdown(l + N - 1, r + N + 1);
    FLGS;
    for (l += N - 1, r += N + 1; l ^ r ^ 1; l >>= 1, r >>= 1)
    {
	FL sgv[l] = std::min(sgv[LS(l)], sgv[RS(l)]);
	FR sgv[r] = std::min(sgv[LS(r)], sgv[RS(r)]);
	IL sgv[L] = sgm[L] = v, LT;
	IR sgv[R] = sgm[R] = v, RT;
    }
    FL sgv[l] = std::min(sgv[LS(l)], sgv[RS(l)]);
    FR sgv[r] = std::min(sgv[LS(r)], sgv[RS(r)]);
    for (l >>= 1; l; l >>= 1)
	sgv[l] = std::min(sgv[LS(l)], sgv[RS(l)]);
}

ll sg_ask(int l, int r)
{
    sg_putdown(l + N - 1, r + N + 1);
    ll z = inf;
    for (l += N - 1, r += N + 1; l ^ r ^ 1; l >>= 1, r >>= 1)
    {
	IL z = std::min(z, sgv[L]);
	IR z = std::min(z, sgv[R]);
    }
    return z;
}

void sg_init()
{
    for (N = 4; N < n + 2; N <<= 1)
	;
    //memset(sgf, 0x3f, sizeof sgf);
    //memset(sgans, 0x3f, sizeof sgans);
    memset(sgv, 0x3f, sizeof sgv);
    sg_set(1, 0);
}

void initpre()
{
    num[1] = ~0u >> 1;
    for (int i = 2; i <= n + 1; ++i)
    {
	int& x = pre[i] = i - 1;
	while (num[x] < num[i])
	    x = pre[x];
    }
}

class ABC
{
public:
    void push(int x)
    {
	while (!q.empty() && num[x] >= num[q.back()])
	    q.pop_back();
	q.push_back(x);
    }
    int maxv() const
    {
	return num[q.front()];
    }
    void pop(int p)
    {
	while (!q.empty() && q.front() <= p)
	    q.pop_front();
    }
private:
    std::deque<int> q;
} deque;

int main()
{
    //stderr = stdout;
    std::cin >> n >> m;
    for (int i = 2; i <= n + 1; ++i)
    {
	scanf("%d", num + i);
	sum[i] = sum[i - 1] + num[i];
	if (num[i] > m)
	{
	    printf("-1\n");
	    return 0;
	}
    }
    initpre();
    sg_init();
    for (int i = 2, j = 1; i <= n + 1; ++i)
    {
	while (sum[i] - sum[j] > m)
	    ++j;
	//sg_up(i, num[i]);
	//ans[i] = sg_ask(j, i - 1);
	//sg_add(i, ans[i]);
	deque.pop(j);
	deque.push(i);
	ans[i] = ans[j] + deque.maxv();
	sg_set(pre[i], ans[pre[i]] + num[i]);
	sg_set(pre[i] + 1, i - 1, inf);
	ans[i] = std::min(ans[i], sg_ask(j, i - 1));
#if DB >= 1
	fprintf(stderr, "%d %lld\n", i, ans[i]);
#endif
    }
    std::cout << ans[n + 1] << std::endl;
}
