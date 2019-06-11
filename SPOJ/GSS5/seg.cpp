#include <cstdio>
#include <cstring>
#include <algorithm>

#define LS(i) ((i) << 1)
#define RS(i) (LS(i) + 1)
#define FOR for (l += N - 1, r += N + 1; l ^ r ^ 1; l >>= 1, r >>= 1)
#define IL if (~l & 1)
#define IR if (r & 1)
#define L (l ^ 1)
#define R (r ^ 1)

const int maxN = 1 << 15;
int n, N;
int sum[maxN], ans[maxN], lans[maxN], rans[maxN];

int Ask(int l, int r)
{
    int ret = 1 << 31, lr = 0, rl = 0;
    FOR
    {
	IL ret = std::max(std::max(ret, ans[L]), lr + lans[L]),
	   lr = std::max(lr + sum[L], rans[L]);
	IR ret = std::max(std::max(ret, ans[R]), rl + rans[R]),
	   rl = std::max(rl + sum[R], lans[R]);
    }
    return std::max(ret, lr + rl);
}

int AskS(int l, int r)
{
    if (l == r)
	return 0;
    ++l, --r;
    int s = 0;
    FOR
    {
	IL s += sum[L];
	IR s += sum[R];
    }
    return s;
}

int AskR(int l, int r)
{
    if (r < l)
	return 0;
    int lr = (1 << 31) / 2, rs = 0, rr = 1 << 31;
    FOR
    {
	IL lr = std::max(lr + sum[L], rans[L]);
	IR rr = std::max(rr, rs + rans[R]), rs += sum[R];
    }
    return std::max(rr, rs + lr);
}

int AskL(int l, int r)
{
    if (r < l)
	return 0;
    int rl = (1 << 31) / 2, ls = 0, ll = 1 << 31;
    FOR
    {
	IL ll = std::max(ll, ls + lans[L]), ls += sum[L];
	IR rl = std::max(rl + sum[R], lans[R]);
    }
    return std::max(ll, ls + rl);
}

void work()
{
    scanf("%d", &n);
    for (N = 4; N < n + 2; N <<= 1)
	;
    for (int i = N + 1; i <= N + n; ++i)
    {
	scanf("%d", &sum[i]);
	ans[i] = lans[i] = rans[i] = sum[i];
    }
    for (int i = N + n + 1; i < N + N; ++i)
	ans[i] = lans[i] = rans[i] = sum[i] = 0;
    for (int i = N - 1; i; --i)
    {
	ans[i] = std::max(std::max(ans[LS(i)], ans[RS(i)]),
		rans[LS(i)] + lans[RS(i)]);
	sum[i] = sum[LS(i)] + sum[RS(i)];
	lans[i] = std::max(lans[LS(i)], sum[LS(i)] + lans[RS(i)]);
	rans[i] = std::max(rans[RS(i)], sum[RS(i)] + rans[LS(i)]);
    }
    scanf("%d", &n);
    for (int a, b, c, d; n--; )
    {
	scanf("%d%d%d%d", &a, &b, &c, &d);
	if (b < c)
	    printf("%d\n", AskR(a, b) + AskS(b, c) + AskL(c, d));
	else
	{
	    int z = AskR(a, c) + AskS(c, b) + AskL(b, d);
	    if (b == c)
		z -= sum[N + b];
	    z = std::max(z, Ask(c, b));
	    z = std::max(z, AskR(a, c - 1) + AskL(c, b));
	    z = std::max(z, AskL(b + 1, d) + AskR(c, b));
	    printf("%d\n", z);
	}
    }
}

int main()
{
    int _;
    for (scanf("%d", &_); _--; )
	work();
}
