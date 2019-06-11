#include <cstdio>
#include <algorithm>

#define LS(i) ((i) << 1)
#define RS(i) (LS(i) + 1)

const int maxN = 1 << 17;
int n, N;
int sum[maxN], ans[maxN], lans[maxN], rans[maxN];

int Ans(int l, int r)
{
    int ret = 1 << 31, lr = 0, rl = 0;
    for (l += N - 1, r += N + 1; l ^ r ^ 1; l >>= 1, r >>= 1)
    {
	if (~l & 1)
	    ret = std::max(std::max(ret, ans[l ^ 1]), lr + lans[l ^ 1]),
	       lr = std::max(lr + sum[l ^ 1], rans[l ^ 1]);
	if (r & 1)
	    ret = std::max(std::max(ret, ans[r ^ 1]), rl + rans[r ^ 1]),
	       rl = std::max(rl + sum[r ^ 1], lans[r ^ 1]);
    }
    return std::max(ret, lr + rl);
}

int main()
{
    scanf("%d", &n);
    for (N = 4; N < n + 2; N <<= 1)
	;
    for (int i = N + 1; i <= N + n; ++i)
    {
	scanf("%d", &sum[i]);
	ans[i] = lans[i] = rans[i] = sum[i];
    }
    for (int i = N - 1; i; --i)
    {
	ans[i] = std::max(std::max(ans[LS(i)], ans[RS(i)]),
		rans[LS(i)] + lans[RS(i)]);
	sum[i] = sum[LS(i)] + sum[RS(i)];
	lans[i] = std::max(lans[LS(i)], sum[LS(i)] + lans[RS(i)]);
	rans[i] = std::max(rans[RS(i)], sum[RS(i)] + rans[LS(i)]);
    }
    scanf("%d", &n);
    for (int a, b; n--; )
    {
	scanf("%d%d", &a, &b);
	printf("%d\n", Ans(a, b));
    }
}
