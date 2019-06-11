#include <cstdio>
#include <cstring>
#include <stack>
#include <algorithm>

struct Edge
{
    int x, a, b;
};

const int maxn = 100003;
const int maxm = 100003;
int n, m;
int start[maxn], to[maxm], next[maxm], type[maxm], edge; // type 0 for >, type 1 for >=
Edge edges[maxm];
int ec;

namespace Set
{
    int fa[maxn];
    bool is_fa[maxn];

    void init();
    void combine(int, int);
    int get_fa(int);
    //bool is_same(int, int);
}

void Set::init()
{
    for (int i = 1; i <= n; ++i)
	fa[i] = i, is_fa[i] = true;
}

void Set::combine(int a, int b)
{
    //fprintf(stderr, "combine %d %d, ", a, b);
    a = get_fa(a);
    b = get_fa(b);
    //fprintf(stderr, "%d %d\n", a, b);
    if (a != b)
	fa[b] = a, is_fa[b] = false;
}

int Set::get_fa(int x)
{
    int f = x;
    while (fa[f] != f)
	f = fa[f];
    for (int i = x, z; i != f; i = z)
	z = fa[i], fa[i] = f;
    return f;
}

void add(int a, int b, int c)
{
    to[++edge] = b;
    next[edge] = start[a];
    start[a] = edge;
    type[edge] = c;
}

namespace SCC // Strongly Connected Components
{
    int index;
    int low[maxn], dfn[maxn];
    std::stack<int> S;
    bool in[maxn];
    void tarjan(int, int);
    void work();
}

void SCC::tarjan(int x, int f)
{
    //fprintf(stderr, "tarjan %d %d\n", x, f);
    dfn[x] = low[x] = ++index;
    S.push(x);
    in[x] = true;
    for (int e = start[x]; e; e = next[e])
	if (to[e] != f)
	{
	    if (dfn[to[e]])
	    {
		if (in[to[e]])
		    low[x] = std::min(low[x], low[to[e]]);
	    }
	    else
	    {
		tarjan(to[e], x);
		low[x] = std::min(low[x], low[to[e]]);
	    }
	}
	else
	    low[x] = std::min(low[x], dfn[to[e]]);
    if (dfn[x] == low[x])
    {
	//fprintf(stderr, "pop\n");
	int z;
	do {
	    z = S.top();
	    S.pop();
	    in[z] = false;
	    Set::combine(z, x);
	} while (z != x);
    }
}

void SCC::work()
{
    for (int i = 1; i <= n; ++i)
	if (Set::is_fa[i] && !dfn[i])
	    tarjan(i, 0);
}

void input()
{
    scanf("%d%d", &n, &m);
    Set::init();
    for (int x, a, b; m--; )
    {
	scanf("%d%d%d", &x, &a, &b);
	if (x == 1)
	    Set::combine(a, b);
	else
	{
	    if (x > 3)
	    {
		x -= 2;
		std::swap(a, b);
	    }
	    edges[ec].x = x;
	    edges[ec].a = a;
	    edges[ec].b = b;
	    ++ec;
	}
    }
    for (int i = 0; i < ec; ++i)
    {
	const int a = Set::get_fa(edges[i].a);
	const int b = Set::get_fa(edges[i].b);
	if (edges[i].x == 3 && a != b)
	    add(a, b, 1);
    }
    SCC::work();
    memset(start, 0, sizeof start);
    edge = 0;
    for (int i = 0; i < ec; ++i)
    {
	const int a = Set::get_fa(edges[i].a);
	const int b = Set::get_fa(edges[i].b);
	if (edges[i].x == 2)
	    add(b, a, 0);
	else if (a != b)
	    add(a, b, 1);
    }
}

int val[maxn];

namespace Solve
{
    const int working = 1;
    const int worked = 2;
    int vis[maxn];
    bool calc(int);
    void solve();
}

bool Solve::calc(int x)
{
    //fprintf(stderr, "calc %d\n", x);
    if (vis[x] == worked)
	return true;
    vis[x] = working;
    val[x] = 1;
    for (int e = start[x]; e; e = next[e])
	if (Set::is_fa[to[e]])
	{
	    if (vis[to[e]] == working)
		return false;
	    if (!calc(to[e]))
		return false;
	    const int t = val[to[e]] + (type[e] == 0);
	    val[x] = std::max(val[x], t);
	}
    vis[x] = worked;
    return true;
}

void Solve::solve()
{
    //for (int i = 1; i <= n; ++i)
    //fprintf(stderr, "%d %d\n", i, Set::is_fa[i]);
    for (int i = 1; i <= n; ++i)
    {
	//fprintf(stderr, "check %d %d\n", i, Set::is_fa[i]);
	if (Set::is_fa[i] && !calc(i))
	{
	    puts("-1");
	    return;
	}
    }
    long long int z = 0;
    for (int i = 1; i <= n; ++i)
	z += val[Set::get_fa(i)];
    printf("%lld\n", z);
}

int main()
{
    input();
    Solve::solve();
}
