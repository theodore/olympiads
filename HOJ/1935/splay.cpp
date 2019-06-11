#include <cstdio>
#include <algorithm>

const int maxn = 500007;
const int maxq = 2000007;
const int inf = ~0u >> 2;

class Splay
{
public:
    Splay();
    void insert(const int);
    int le(const int);
private:
    void splay(int pos, const int father = 0);
    void rotate(const int y);
    void resize(const int x)
	{ node[x].size = node[node[x].son[0]].size + node[node[x].son[1]].size
	    + node[x].cnt; }
    struct Node_t
    {
	void init(const int v, const int c, const int s, const int f,
		const int s0, const int s1)
	    { val = v; cnt = c; size = s; father =f; son[0] = s0; son[1] = s1;}
	int val, cnt;
	int size;
	int father, son[2];
    };
    int root, nc;
    Node_t node[maxn];
};

int Splay::le(const int x)
{
    int ans = 0;
    for (int p = root; p; )
	if (node[p].val > x)
	    ans = p, p = node[p].son[0];
	else
	    p = node[p].son[1];
    //Assert(ans);
    splay(ans);
    return node[node[ans].son[0]].size - 1;
}

void Splay::insert(const int x)
{
    int p, next = root;
    do {
	p = next;
	++node[p].size;
	if (node[p].val == x)
	{
	    ++node[p].cnt;
	    splay(p);
	    return;
	}
	else
	    next = node[p].son[node[p].val < x];
    } while (next);
    node[next = node[p].son[node[p].val < x] = ++nc].init(x, 1, 1, p, 0, 0);
    splay(next);
}

Splay::Splay(): root(1), nc(2)
{
    node[1].init(-inf, 1, 2, 0, 0, 2);
    node[2].init(inf, 1, 1, 1, 0, 0);
}

void Splay::rotate(const int y)
{
    const int x = node[y].father;
    const int f = node[x].father;
    const int d = y == node[x].son[1];
    node[y].father = node[x].father;
    node[f].son[x == node[f].son[1]] = y;
    node[x].son[d] = node[y].son[!d];
    node[node[x].son[d]].father = x;
    node[x].father = y;
    node[y].son[!d] = x;
    resize(y);
    resize(x);
}

void Splay::splay(int x, const int r)
{
    for (int y = node[x].father; y != r; y = node[x].father)
    {
	if (node[y].father == r)
	    rotate(x);
	else
	{
	    if ((x == node[y].son[0]) ^ (y == node[node[y].father].son[0]))
	    {
		rotate(x);
		rotate(x);
	    }
	    else
	    {
		rotate(y);
		rotate(x);
	    }
	}
    }
    if (r == 0)
	root = x;
}

struct Point
{
    int x, y;
    bool operator<(const Point& z) const
	{ return x < z.x; }
};

struct Rectangle
{
    int ans[4];
    int answer() const
	{ return ans[0] + ans[1] - ans[2] - ans[3]; }
};

struct Query
{
    int x, y;
    int id, no;
    void init(const int i, const int n, const int xx, const int yy)
	{ x = xx; y = yy; id = i; no = n; }
    bool operator<(const Query& z) const
	{ return x < z.x; }
};

Point p[maxn];
Rectangle rect[maxn];
Query q[maxq];
Splay bst;

int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; ++i)
	scanf("%d%d", &p[i].x, &p[i].y);
    std::sort(p, p + n);
    p[n].x = p[n].y = inf;
    for (int i = 0, x0, y0, x1, y1; i < m; ++i)
    {
	scanf("%d%d%d%d", &x0, &y0, &x1, &y1);
	q[i * 4].init(i, 0, x1, y1);
	q[i * 4 + 1].init(i, 1, x0 - 1, y0 - 1);
	q[i * 4 + 2].init(i, 2, x0 - 1, y1);
	q[i * 4 + 3].init(i, 3, x1, y0 - 1);
    }
    std::sort(q, q + m * 4);
    for (int i = 0, j = 0; j < 4 * m; ++j)
    {
	while (p[i].x <= q[j].x)
	    bst.insert(p[i++].y);
	rect[q[j].id].ans[q[j].no] = bst.le(q[j].y);
    }
    for (int i = 0; i < m; ++i)
	printf("%d\n", rect[i].answer());
}
