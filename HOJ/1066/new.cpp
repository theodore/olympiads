#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

#if defined(DB) || defined(NDB)
int OP(const int x){return ((x - 1) ^ 1) + 1;}
#else
#define OP(x) ((((x) - 1) ^ 1) + 1)
#endif

const int maxn = 813;
const int maxm = 9013;
int n, m, l, S, T;
int start[maxn], to[maxm], next[maxm], cap[maxm], edge;
int ans;
char map[23][23];

void add(const int a, const int b, const int c)
{
#ifdef NDB
    fprintf(stderr, "%d -> %d: %d\n", a, b, c);
#endif
    to[++edge] = b;
    cap[edge] = c;
    next[edge] = start[a];
    start[a] = edge;
}

void init()
{
    scanf("%d%d%d", &n, &m, &l);
    S = n * m * 2;
    T = S + 1;
    for (int i = 0; i < n; ++i)
    {
	scanf("%s", map[i]);
	for (int j = 0; j < m; ++j)
	{
	    if (map[i][j] == '0')
		continue;
	    int a = (i * m + j) * 2;
	    add(a, a + 1, map[i][j] - '0');
	    add(a + 1, a, 0);
	}
    }
    for (int i = 0; i < n; ++i)
    {
	char s[23];
	scanf("%s", s);
	for (int j = 0, a; j < m; ++j)
	    if (s[j] == 'L')
	    {
		++ans;
		add(S, a = (i * m + j) * 2, 1);
		add(a, S, 0);
	    }
    }
    for (int i = 0; i < n; ++i)
	for (int j = 0; j < m; ++j)
	    if (map[i][j] != '0')
	    {
		int x = (i * m + j) * 2 + 1;
		if (i - l < 0 || j - l < 0 || i + l >= n || j + l >= m)
		{
		    add(x, T, maxn);
		    add(T, x, 0);
		}
		for (int nx = std::max(0, i - l); nx < std::min(n, i + l + 1); ++nx)
		    for (int ny = std::max(0, j - l); ny < std::min(m, j + l + 1); ++ny)
		    {
			if (map[nx][ny] != '0')
			{
			    int a = (nx * m + ny) * 2;
			    add(x, a, maxn);
			    add(a, x, 0);
			}
		    }
	    }
}

int sap()
{
    static const int inf = -1u >> 1;
    n = n * m + 2;
    int rtn = 0;
    static int dist[maxn], flow[maxn], pre[maxn], cnt[maxn], cur[maxn];
    memcpy(cur, start, sizeof cur[0] * size_t(n + 1));
    cnt[0] = n;
    for (int x = S; dist[S] < n; )
    {
#ifdef DB
	fprintf(stderr, "x = %d %d %d\n", x, dist[x], flow[x]);
#endif
	if (x == S)
	    flow[x] = inf;
	bool found = false;
	for (int e = cur[x]; e; e = next[e])
	    if (cap[e] && dist[to[e]] + 1 == dist[x])
	    {
		found = true;
		cur[x] = e;
		flow[to[e]] = std::min(flow[x], cap[e]);
		x = to[e];
		pre[x] = e;
		break;
	    }
#ifdef DB
	//fprintf(stderr, "%d\n", __LINE__);
#endif
	if (x == T)
	{
	    rtn += flow[x];
	    do
	    {
		cap[pre[x]] -= flow[T];
		cap[OP(pre[x])] += flow[T];
		x = to[OP(pre[x])];
	    } while (x != S);
	}
#ifdef DB
	//fprintf(stderr, "%d\n", __LINE__);
#endif
	if (!found)
	{
	    if (--cnt[dist[x]] == 0)
		break;
	    dist[x] = n;
	    for (int e = start[x]; e; e = next[e])
		if (cap[e] && dist[to[e]] + 1 < dist[x])
		{
		    dist[x] = dist[to[e]] + 1;
		    cur[x] = e;
		}
	    ++cnt[dist[x]];
	    if (x != S)
		x = to[OP(pre[x])];
	}
    }
    return rtn;
}

int main()
{
    init();
#ifdef DB
    fprintf(stderr, "ans = %d\n", ans);
#endif
    printf("%d\n", ans - sap());
}
