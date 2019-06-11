#include <cstdio>
#include <cstring>
#include <queue>

const int maxN = 2000010;
const int maxm = 6000010;

namespace deficient
{
    void init();
    void answer();
    int n, m, N;
    int start[maxN], to[maxm], next[maxm], len[maxm], edge;
    //bool in[maxN];
    //int d[maxN];
    //int head, tail, q[maxN];
    struct ele_t
    {
	ele_t(){}
	ele_t(int v, int d): vtx(v), dist(d){}
	int vtx, dist;
	bool operator<(const ele_t& x) const
	    { return dist > x.dist; }
    };
    std::priority_queue<ele_t> q;
}

void deficient::answer()
{
    // 0 -> N
    static bool vis[maxN];
    ele_t x;
    x.vtx = 0;
    x.dist = 0;
    q.push(x);
    for (; ; )
    {
	x = q.top();
	q.pop();
#ifdef DB
	fprintf(stderr, "%d %d\n", x.vtx, x.dist);
#endif
	if (vis[x.vtx])
	    continue;
	if (x.vtx == N)
	{
	    printf("%d\n", x.dist);
	    return;
	}
	vis[x.vtx] = true;
	for (int e = start[x.vtx]; e; e = next[e])
	    q.push(ele_t(to[e], x.dist + len[e]));
    }
}

/*
void deficient::answer()
{
    memset(d, 0x7f, sizeof(d));
    d[0] = 0;
    q[0] = 0;
    tail = 1;
    in[0] = true;
    while (head != tail)
    {
	static int x;
	x = q[head++];
	if (head == maxN)
	    head = 0;
	in[x] = false;
	for (int e = start[x]; e; e = next[e])
	    if (d[x] + len[e] < d[to[e]])
	    {
		d[to[e]] = d[x] + len[e];
		if (!in[to[e]])
		{
		    in[to[e]] = true;
		    q[tail++] = to[e];
		    if (tail == maxN)
			tail = 0;
		}
	    }
    }
    printf("%d\n", d[N]);
}
*/

#define add(a, b, l) \
{ \
    to[++edge] = b; \
    len[edge]  = l; \
    next[edge] = start[a]; \
    start[a]   = edge; \
}

#define hash(x, y, d) \
    ((((x) == n - 1) || ((y) == -1)) \
     ? 0 \
     : (((x) == -1) || ((y) == m - 1)) \
     ? N \
     : (2 * ((x) * (m - 1) + (y)) + (d) + 1));

const int buff_size(10001003);
char buff[buff_size];
char* p = buff;

#define read(x) \
{ \
    for (; *p < '0' || *p > '9'; ++p); \
    for (x = 0; '0' <= *p && *p <= '9'; ++p) \
    x = x * 10 + *p - '0'; \
}

void deficient::init()
{
    fread(buff, 1, buff_size, stdin);
    read(n);
    read(m);
    N = 2 * (n - 1) * (m - 1) + 1;
    int t;
    register int a, b;
    for (int i = 0; i < n; ++i)
	for (int j = 0; j < m - 1; ++j)
	{
	    read(t);
	    a = hash(i, j, 1);
	    b = hash(i - 1, j, 0);
	    add(a, b, t);
	    add(b, a, t);
	}
    for (int i = 0; i < n - 1; ++i)
	for (int j = 0; j < m; ++j)
	{
	    read(t);
	    a = hash(i, j - 1, 1);
	    b = hash(i, j, 0);
	    add(a, b, t);
	    add(b, a, t);
	}
    for (int i = 0; i < n - 1; ++i)
	for (int j = 0; j < m - 1; ++j)
	{
	    read(t);
	    a = hash(i, j, 0);
	    b = hash(i, j, 1);
	    add(a, b, t);
	    add(b, a, t);
	}
}

int main()
{
    deficient::init();
    deficient::answer();
    return 0;
}
