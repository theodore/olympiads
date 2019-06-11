#include <cstdio>
#include <map>
#include <vector>
#include <utility>
#include <algorithm>

const int maxn = 1007;
int n, m, a, b;
char msg[maxn][maxn];

void input()
{
    scanf("%d%d\n", &n, &m);
    for (int i = 1; i <= n; ++i)
	gets(msg[i] + 1);
    scanf("%d%d", &a, &b);
}

unsigned ans, ansidx;
std::map<unsigned, std::vector<std::pair<int, int> > > cnt;

void hash()
{
    static unsigned tmp[maxn][maxn];
    static unsigned pre[maxn][maxn];
    int base = 257;
    // horizontal
    for (int i = 1; i <= n; ++i)
	for (int j = 1; j <= m; ++j)
	{
	    pre[i][j] = pre[i][j - 1] * base + msg[i][j] - 0;
#if DB >= 1
	    fprintf(stderr, "%d %d %u\n", i, j, pre[i][j]);
#endif
	}
#if DB >= 1
    fprintf(stderr, "\n");
#endif
    unsigned z = 1;
    for (int i = 0; i < b; ++i)
	z *= base;
#if DB >= 1
    fprintf(stderr, "z = %u\n\n", z);
#endif
    for (int i = 1; i <= n; ++i)
	for (int j = b; j <= m; ++j)
	{
	    tmp[i][j] = pre[i][j] - z * pre[i][j - b];
#if DB >= 1
	    fprintf(stderr, "%d %d %u\n", i, j, tmp[i][j]);
#endif
	}
#if DB >= 1
    fprintf(stderr, "\n");
#endif
    // vertical
    base = z;
    for (int i = 1; i <= n; ++i)
	for (int j = b; j <= m; ++j)
	    pre[i][j] = pre[i - 1][j] * base + tmp[i][j];
    z = 1;
    for (int i = 0; i < a; ++i)
	z *= base;
    for (int i = a; i <= n; ++i)
	for (int j = b; j <= m; ++j)
	{
	    unsigned x = pre[i][j] - z * pre[i - a][j];
	    cnt[x].push_back(std::make_pair(i, j));
	    if (cnt[x].size() > ans)
	    {
		ans = cnt[x].size();
		ansidx = x;
	    }
#if DB >= 1
	    fprintf(stderr, "%d %d %u\n", i, j, x);
#endif
	}
}

void output()
{
    printf("%d %d\n", a, b);
    for (int i = cnt[ansidx][0].first - a + 1; i <= cnt[ansidx][0].first; ++i)
    {
	for (int j = cnt[ansidx][0].second - b + 1; j <= cnt[ansidx][0].second;
		++j)
	    putchar(msg[i][j]);
	putchar('\n');
    }
    printf("%u\n", ans);
    for (std::vector<std::pair<int, int> >::iterator i = cnt[ansidx].begin();
	    i != cnt[ansidx].end(); ++i)
	printf("%d %d\n", i->first - a + 1, i->second - b + 1);
}

int main()
{
    input();
    hash();
    output();
}
