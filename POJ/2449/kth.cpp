#include <cstdio>
#include <cstring>
#include <queue>

namespace
{
    const int maxn = 1003;
    const int maxm = 200003;
    int n, m, s, t, k;
    int start[maxn], startb[maxn], to[maxm], next[maxm], leng[maxm], edge;
    struct T
    {
	T(){}
	T(int vv, int dd, int hh): v(vv), d(dd), h(hh) {}
	int v, d, h;
	bool operator<(const T& x) const
	{ return d + h > x.d + x.h; }
    };
    int dist[maxn];

    void add(const int a, const int b, const int c);
    int dij();
    void init();
}

namespace
{
    int dij()
    {
	std::priority_queue<T> q;
	int cnt = -(s == t);
	q.push(T(s, 0, dist[s]));
	while (!q.empty())
	{
	    const T x = q.top();
	    q.pop();
	    if (x.v == t && ++cnt == k)
		return x.d;
	    for (int e = start[x.v]; e; e = next[e])
		q.push(T(to[e], x.d + leng[e], dist[to[e]]));
	}
	return -1;
    }

    void add(const int a, const int b, const int c)
    {
	to[++edge] = b;
	leng[edge] = c;
	next[edge] = start[a];
	start[a] = edge;
	to[++edge] = a;
	leng[edge] = c;
	next[edge] = startb[b];
	startb[b] = edge;
    }

    void init()
    {
	std::queue<int> q;
	static bool in[maxn];
	memset(dist, 0x3f, sizeof dist);
	dist[t] = 0;
	in[t] = true;
	q.push(t);
	while (!q.empty())
	{
	    int x = q.front();
	    q.pop();
	    in[x] = false;
	    for (int e = startb[x]; e; e = next[e])
		if (dist[x] + leng[e] < dist[to[e]])
		{
		    dist[to[e]] = dist[x] + leng[e];
		    if (!in[to[e]])
		    {
			in[to[e]] = true;
			q.push(to[e]);
		    }
		}
	}
    }
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 0, a, b, c; i < m; ++i)
    {
	scanf("%d%d%d", &a, &b, &c);
	add(a, b, c);
    }
    scanf("%d%d%d", &s, &t, &k);
    init();
    printf("%d\n", dij());
}
