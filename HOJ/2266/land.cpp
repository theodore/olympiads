#include <cstdio>
#include <cstring>
#include <algorithm>

const char P_good = '.';
const int maxn = 1003;
int n, m;
char land[maxn][maxn];
int cnt[maxn];

void init()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i)
	scanf("%s", land[i] + 1);
    memset(cnt, 0, sizeof cnt[0] * (m + 1));
    cnt[0] = -1;
}

int ans[maxn][maxn];

void calc()
{
    static int pre[maxn];
    for (int i = 1; i <= n; ++i)
	for (int j = 1; j <= m; ++j)
	{
	    if (land[i][j] == P_good)
	    {
		++cnt[j];
		for (int& x = pre[j] = j - 1; cnt[x] >= cnt[j]; x = pre[x])
		    ;
		ans[i][j] = std::max(2 * cnt[j], ans[i][pre[j]]) + 2 * (j - pre[j]);
	    }
	    else
		ans[i][j] = cnt[j] = 0;
	}
}

void output()
{
    static int out_cnt[4 * maxn];
    memset(out_cnt, 0, sizeof out_cnt[0] * (2 * n + 2 * m + 1));
    for (int i = 1; i <= n; ++i)
	for (int j = 1; j <= m; ++j)
	    ++out_cnt[ans[i][j]];
    for (int i = 1; i <= 2 * n + 2 * m; ++i)
	if (out_cnt[i])
	    printf("%d x %d\n", out_cnt[i], i);
}

int main()
{
    int _;
    for (scanf("%d", &_); _--; )
    {
	init();
	calc();
	output();
    }
}
