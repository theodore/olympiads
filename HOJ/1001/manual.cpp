#include <cstdio>
#include <cstring>

const int maxN = 2000010;
const int maxm = 6000010;

namespace deficient
{
    void init();
    void answer();
    int n, m, N;
    int start[maxN], to[maxm], next[maxm], len[maxm], edge;
    struct ele_t
    {
	int vtx, dist;
    };
    ele_t heap[maxN];
    int hash[maxN];
    void pop();
    void update(int&);
    const int inf = 0x3fffffff;
}

void deficient::update(int& p)
{
    typedef ele_t T;
    T x = heap[p];
    while (p)
    {
	int f = (p - 1) / 2;
	if (heap[f].dist > x.dist)
	{
	    heap[p] = heap[f];
	    hash[heap[p].vtx] = p;
	    p = f;
	}
	else
	    break;
    }
    heap[p] = x;
}

void deficient::pop()
{
    typedef ele_t T;
    hash[heap[0].vtx] = N;
    T x = heap[N];
    heap[N].vtx = heap[0].vtx;
    heap[N].dist = inf;
    int p = 0;
    while (p < (N + 1) / 2)
    {
	int s = p * 2 + 1;
	if (s < N && heap[s + 1].dist < heap[s].dist)
	    ++s;
	if (heap[s].dist < x.dist)
	{
	    heap[p] = heap[s];
	    hash[heap[p].vtx] = p;
	    p = s;
	}
	else
	    break;
    }
    heap[p] = x;
    hash[x.vtx] = p;
}

void deficient::answer()
{
    for (int i = N; i; --i)
    {
	heap[i].vtx = i;
	heap[i].dist = inf;
	hash[i] = i;
    }
    for (; ; )
    {
	ele_t x = heap[0];
	pop();
	if (x.vtx == N)
	{
	    printf("%d\n", x.dist);
	    return;
	}
	for (int e = start[x.vtx]; e; e = next[e])
	{
	    int v = to[e], d = x.dist + len[e];
	    if (d < heap[hash[v]].dist)
	    {
		heap[hash[v]].dist = d;
		update(hash[v]);
	    }
	}
    }
}

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
