#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>

struct Rect
{
    Rect(){}
    Rect(const int a, const int b, const int c, const int d)
    {
	init(std::min(a, c), std::min(b, d), std::max(a, c), std::max(b, d));
    }
    int x[4], y[4];
    void init(const int a, const int b, const int c, const int d)
    {
	x[0] = x[3] = a;
	x[1] = x[2] = c;
	y[0] = y[1] = b;
	y[2] = y[3] = d;
    }
    bool n_intsect(const Rect& z) const
    {
	return x[2] <= z.x[0] || z.x[2] <= x[0]
	    || y[2] <= z.y[0] || z.y[2] <= y[0];
    }
    bool operator<(const Rect& z) const
    { return y[0] < z.y[0] || (y[0] == z.y[0] && x[0] < z.x[0]); }
};

const int maxz = 103;
const int maxn = 807;
const int maxm = 320007;
Rect rect[maxz];
int n;
int start[maxn], to[maxm], next[maxm], leng[maxm], edge;

void add(const int a, const int b, const int c)
{
    to[++edge] = b;
    leng[edge] = c;
    next[edge] = start[a];
    start[a] = edge;
}

#define DIST(a, b, c, d) (std::abs((a) - (c)) + std::abs((b) - (d)))
void mkgraph()
{
    for (int i = 0; i < n; ++i)
	for (int j = i; j < n; ++j)
	    for (int p = 0; p < 4; ++p)
		for (int q = 0; q < 4; ++q)
		{
		    bool flag = true;
		    Rect t(rect[i].x[p], rect[i].y[p],
			    rect[j].x[q], rect[j].y[q]);
		    for (int k = 0; k < n; ++k)
			if (!t.n_intsect(rect[k]))
			{
			    flag = false;
			    break;
			}
		    if (flag)
		    {
			const int d = DIST(rect[i].x[p], rect[i].y[p],
				rect[j].x[q], rect[j].y[q]);
			int a = i * 8 + p, b = j * 8 + q;
			const int s = (rect[0].x[0] < t.x[0]
				&& t.y[0] <= rect[0].y[0]
				&& rect[0].y[0] < t.y[2]) * 4;
			add(a, b ^ s, d);
			add(b ^ s, a, d);
			a += 4;
			b += 4;
			add(a, b ^ s, d);
			add(b ^ s, a, d);
		    }
		}
}
#undef DIST

int vis[maxz];

void fill(const int x)
{
    vis[x] = true;
    for (int i = 0; i < n; ++i)
	if (!vis[i] && !rect[x].n_intsect(rect[i]))
	    fill(i);
}

int spfa()
{
    fill(0);
    int s = 0;
    for (int i = 1; i < n; ++i)
	if (vis[i] && rect[i] < rect[s])
	    s = i;
    std::queue<int> q;
    static int dist[maxn];
    static bool in[maxn];
    memset(dist, 0x3f, sizeof dist);
    dist[s * 8] = 0;
    q.push(s * 8);
    while (!q.empty())
    {
	int x = q.front();
	q.pop();
	in[x] = false;
	for (int e = start[x], t; e; e = next[e])
	    if ((t = dist[x] + leng[e]) < dist[to[e]])
	    {
		dist[to[e]] = t;
		if (!in[to[e]])
		{
		    in[to[e]] = true;
		    q.push(to[e]);
		}
	    }
    }
    return dist[s * 8 + 4];
}

int main()
{
    scanf("%d", &n);
    for (int i = 0, a, b, c, d; i < n; ++i)
    {
	scanf("%d%d%d%d", &a, &b, &c, &d);
	rect[i].init(a, b, c, d);
    }
    mkgraph();
    printf("%d\n", spfa());
}
