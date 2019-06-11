#include <cstdio>
#include <set>
#include <algorithm>

#ifdef LOCAL
# include <cassert>
# define Assert(x) assert(x)
#else
# define Assert(x) 0
#endif

struct Point
{
    Point(){}
    Point(int a, int b) : x(a), y(b){}
    int x, y;
    bool operator<(const Point& z) const
    {
	if (x != z.x)
	    return x < z.x;
	else
	    return y > z.y;
    }
};

struct Box : public Point
{
    int v;
    void init(int a, int b, int c)
    {
	if (a > b)
	    std::swap(a, b);
	if (a > c)
	    std::swap(a, c);
	v = a;
	x = std::min(b, c);
	y = std::max(b, c);
    }
    static bool cmpv(const Box& a, const Box& b)
    {
	if (a.v != b.v)
	    return a.v < b.v;
	else
	    return a.x < b.x && a.y < b.y;
    }
};

typedef long long ll;
typedef std::set<Point> List_t;
const int maxn = 50007;
int p, n;
Box box[maxn];
int ans[maxn];
int best;
List_t len[maxn];

bool cmp(const List_t& a, const List_t& b)
{
    Assert(b.size() == 1);
    List_t::const_iterator e;
    List_t::const_iterator i = a.lower_bound(*(e = b.begin()));
    if (i == a.begin())
	return false;
    --i;
#if DB & 1
    fprintf(stderr, "i: %d %d, e: %d %d\n", i->x, i->y, e->x, e->y);
#endif
    return i->x < e->x && i->y < e->y;
}

#if DB & 3
namespace st
{
    template<class Iter, class Tp, class Cmp>
	Iter lower_bound(Iter first, Iter last, const Tp& ele, Cmp cmp)
	{
	    while (first != last)
	    {
		if (cmp(*first, ele))
		    ++first;
		else
		    break;
	    }
	    return first;
	}
}
#endif

#if DB & 3
namespace db
{
    void outset(const List_t& z)
    {
	fprintf(stderr, "size: %d\n", z.size());
	for (List_t::const_iterator i = z.begin(); i != z.end(); ++i)
	    fprintf(stderr, "<%d %d> ", i->x, i->y);
	fprintf(stderr, "\n");
    }
}
#endif

int main()
{
    int a;
    scanf("%d%d%d", &a, &p, &n);
    ll c = 1;
    for (int i = 0; i < n; ++i)
    {
	int x = int(c = c * a % p);
	int y = int(c = c * a % p);
	int z = int(c = c * a % p);
	box[i].init(x, y, z);
    }
    std::sort(box, box + n, Box::cmpv);
    len[0].insert(Point(-1, -1));
    for (int i = 0; i < n; ++i)
    {
#if DB & 1
	fprintf(stderr, "%d:\n", i);
#endif
#if DB & 3
	ans[i] = st::lower_bound(len, len + best + 1,
		List_t(box + i, box + i + 1), cmp) - len;
#else
	ans[i] = std::lower_bound(len, len + best + 1,
		List_t(box + i, box + i + 1), cmp) - len;
#endif
	best = std::max(best, ans[i]);
	// insert it back
	for (List_t::iterator j = len[ans[i]].upper_bound(box[i]);
		j != len[ans[i]].end() && j->y > box[i].y;
		len[ans[i]].erase(j++))
	    ;
	len[ans[i]].insert(box[i]);
    }
    printf("%d\n", best);
#if DB & 2
    stderr = stdout;
    for (int i = 0; i < n; ++i)
	fprintf(stderr, "%d\n", ans[i]);
#endif
}
