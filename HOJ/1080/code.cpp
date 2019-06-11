#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <queue>
#include <algorithm>

const int maxn = 33;
const int maxl = 53;
const int maxN = maxn * maxl * maxl * 2;
const int maxm = maxN * maxn + maxn * maxl * maxn * maxn;
int n;
char str[maxn][maxl];
int len[maxn];
int start[maxN], to[maxm], next[maxm], leng[maxm], edge;

#ifdef DB
void output(const int a)
{
    fprintf(stderr, "%d,%d,%d,%d",
	    a / 2 / maxl / maxl, a / 2 / maxl % maxl, a / 2 % maxl, a & 1);
}
#endif

void add(const int a, const int b, const int c)
{
#ifdef NDB
    fprintf(stderr, "%d,%d,%d,%d -> %d,%d,%d,%d : %d\n",
	    a / 2 / maxl / maxl, a / 2 / maxl % maxl, a / 2 % maxl, a & 1,
	    b / 2 / maxl / maxl, b / 2 / maxl % maxl, b / 2 % maxl, b & 1, c);
#endif
    to[++edge] = b;
    leng[edge] = c;
    next[edge] = start[a];
    start[a] = edge;
}

int hash(const int i, const int j, const int k, const int flag)
{
    return (((i * maxl + j) * maxl + k) << 1) + flag;
}

struct llx_t
{
    char s[maxl];
    int l;
    int id;
    bool operator<(const llx_t& x) const
    {
	return l < x.l;
    }
};

void input()
{
    static llx_t llx[maxn];
    scanf("%d\n", &n);
    for (int i = 0; i < n; ++i)
    {
	llx[i].id = i;
	fgets(llx[i].s, sizeof llx[i].s, stdin);
	int& l = llx[i].l = int(strlen(llx[i].s));
	while (--l, l >= 0 && llx[i].s[l] != '0' && llx[i].s[l] != '1')
	    ;
	if (++l == 0)
	{
	    printf("0\n");
	    exit(0);
	}
	llx[i].s[l] = '\0';
    }
    std::sort(llx, llx + n);
    for (int i = 0; i < n; ++i)
    {
	len[i] = llx[i].l;
	memcpy(str[i], llx[i].s, sizeof str[i]);
    }
}

bool equal(const char* a, const char* b)
{
    int nn = int(std::min(strlen(a), strlen(b)));
    for (int i = 0; i < nn; ++i)
	if (a[i] != b[i])
	    return false;
    return true;
}

/*
bool cmp(const int& a, const int& b)
{
    return len[a] < len[b];
}
*/

void make_graph()
{
    for (int i = 0; i < n; ++i)
	for (int j = 0; j <= len[i]; ++j)
	    for (int k = 0; k <= j; ++k)
	    {
		int l[maxn], lc = 0;
		for (int m = 0; m < n; ++m)
		    if (equal(str[i] + k, str[m]))
			l[lc++] = m;
		int ni, nj, nk, nl;
		for (int u = 0; u < lc; ++u)
		{
		    const int& m = l[u];
		    if (k + len[m] <= len[i])
		    {
			ni = i;
			nj = std::max(j, k + len[m]);
			nk = std::min(j, k + len[m]);
			nl = nk - k;
		    }
		    else
		    {
			ni = m;
			nj = len[i] - k;
			nk = j - k;
			nl = nk;
		    }
		    add(hash(i, j, k, 0), hash(ni, nj, nk, 0), nl);
		    if (len[i] == j)
			add(hash(i, j, k, 1), hash(ni, nj, nk, 1), nl);
		}
		if (len[i] > j && j == k)
		{
		    for (int ui = 0; ui < lc; ++ui)
		    {
			const int& u = l[ui];
			if (j + len[u] <= len[i])
			{
			    ni = i;
			    nj = j + len[u];
			    nk = k + len[u];
			    nl = len[u];
			}
			else
			{
			    ni = u;
			    nj = len[u];
			    nk = len[i] - k;
			    nl = nk;
			}
			add(hash(i, j, k, 1), hash(ni, nj, nk, 1), nl);
			for (int vi = 0; vi < ui; ++vi)
			    if (equal(str[u], str[l[vi]]))
			    {
				const int& v = l[vi];
				if (j + len[u] <= len[i])
				{
				    ni = i;
				    nj = j + len[u];
				    nk = k + len[v];
				    nl = len[v];
				}
				else
				{
				    ni = u;
				    nj = std::max(len[i] - j, len[v]);
				    nk = std::min(len[i] - j, len[v]);
				    nl = nk;
				}
				add(hash(i, j, k, 1), hash(ni, nj, nk, 0), nl);
			    }
		    }
		}
	    }
}

int dist[maxN];
int in[maxN];
#ifdef DB
int pre[maxN];
#endif

void spfa()
{
    std::queue<int> q;
    memset(dist, 0x3f, sizeof dist);
    /*
       for (int i = 0, t; i < n; ++i)
       {
       q.push(t = hash(i, 0, 0, 1));
       dist[t] = 0;
       in[t] = true;
       }
       */
    for (int i = 0, t; i < n; ++i)
	for (int j = 0; j <= i; ++j)
	    if (equal(str[i], str[j]))
		for (int k = 0; k <= j; ++k)
		    if ((i != j || j != k) && equal(str[j], str[k]))
		    {
			if (i == j)
			    q.push(t = hash(i, len[i], len[k], 1));
			else if (j == k)
			    q.push(t = hash(i, len[j], len[k], 1));
			else
			    q.push(t = hash(i, len[j], len[k], 0));
			dist[t] = len[k];
			in[t] = true;
		    }
    while (!q.empty())
    {
	const int x = q.front();
	q.pop();
	in[x] = false;
	for (int e = start[x], t; e; e = next[e])
	    if (dist[x] + leng[e] < dist[t = to[e]])
	    {
		dist[t] = dist[x] + leng[e];
#ifdef DB
		pre[t] = x;
#endif
		if (!in[t])
		{
		    in[t] = true;
		    q.push(t);
		}
	    }
    }
}

#ifdef DB
void db_o(const int x)
{
    output(x);
    fprintf(stderr, " %d\n", dist[x]);
    if (pre[x])
	db_o(pre[x]);
}
#endif

int answer()
{
    const int inf = 0x3f3f3f3f;
    int ans = inf;
    for (int i = 0; i < n; ++i)
    {
	ans = std::min(ans, dist[hash(i, len[i], len[i], 0)]);
#ifdef DB
	fprintf(stderr, "%d %d %d\n", i, len[i], ans);
#endif
    }
    return ans == inf ? -1 : ans;
}

int main()
{
    input();
    make_graph();
    spfa();
    printf("%d\n", answer());
}
