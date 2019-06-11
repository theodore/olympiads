#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>
#include <utility>

#define Assert(x) void(0)

using std::make_pair;
typedef std::vector<int> Vint;
typedef Vint::iterator Viit;
typedef std::pair<Vint, int> Path_t;
typedef long long ll;

namespace
{
    const int infinity = 0x3f3f3f3f;
    const int maxn = 53;
    const int maxN = 10003;

    class Trie_t
    {
    private:
	struct Node_t
	{
	    Path_t path;
	    ll mask;
	    Node_t* son[maxn];
	};
    public:
	typedef Node_t* pntr;

	void insert(Viit first, const Viit& last, pntr pos = 0);
	void output() const;
	void clear();
    private:
	friend bool init();
	Node_t *root, *lastins;
	Node_t node[maxN];
	int nc;
    };

    struct Heap_Elmt
    {
	typedef Trie_t::pntr Node;

	Heap_Elmt(const Node& v, const Path_t& p);

	Path_t path;
	Node vrtx;
	bool operator<(const Heap_Elmt&) const;
    };

    int n, m, k, S, T;
    int G[maxn][maxn];
    std::priority_queue<Heap_Elmt> heap;
    Trie_t trie;

    Path_t spfa(const int src, const Trie_t::pntr = 0);
    void find_candidates(Trie_t::pntr, Viit&, const Viit&);
    bool init();
    bool find_next();
}

namespace
{
    void Trie_t::insert(Viit first, const Viit& last, pntr pos)
    {
	if (pos == 0)
	{
	    pos = root = &node[0];
	    const int s = *first++;
	    root->mask = 1ull << s;
	    root->path.first.push_back(s);
	    root->path.second = 0;
	}
	pntr i, j;
	for (i = pos; first != last; i = j, ++first)
	{
	    Assert(i->son[*first] == 0);
	    j = i->son[*first] = &node[++nc];
	    j->path.first = i->path.first;
	    j->path.first.push_back(*first);
	    j->mask = i->mask | (1ull << *first);
	}
	lastins = i;
    }

    void Trie_t::output() const
    {
	const Vint& v = lastins->path.first;
	for (int i = v.size() - 1; i; --i)
	    printf("%d-", v[i] + 1);
	printf("%d\n", v[0] + 1);
    }

    Heap_Elmt::Heap_Elmt(const Node& v, const Path_t& p)
    {
	const Vint &a = v->path.first, &b = p.first;
	Vint& c = path.first;
	int as, bs;
	c.resize((as = a.size()) + (bs = b.size()) - 1);
	for (int i = 0; i < as; ++i)
	    c[i] = a[i];
	for (int i = 1, j = as; i < bs; ++i, ++j)
	    c[j] = b[i];
	path.second = v->path.second + p.second;
	vrtx = v;
    }

    bool Heap_Elmt::operator<(const Heap_Elmt& x) const
    {
	if (path.second != x.path.second)
	    return path.second > x.path.second;
	return lexicographical_compare(x.path.first.rbegin(),
		x.path.first.rend(), path.first.rbegin(), path.first.rend());
    }

    /**
     *  @brief  Find candidate paths in range @p [i,last).
     *  @param  now  The corresponding position to @p i on trie.
     */
    void find_candidates(Trie_t::pntr now, Viit& i, const Viit& last)
    {
	while (i != last)
	{
	    // calc shortest path from here
	    Path_t path = spfa(*i, now);
	    if (path.second != infinity)
		heap.push(Heap_Elmt(now, path));
	    // calc node members for the son
	    const int u = *i;
	    const int v = *++i;
	    Assert(now->son[v]);
	    now->son[v]->path.second = now->path.second + G[u][v];
	    now->son[v]->mask = now->mask | (1ull << v);
	    now = now->son[v];
	}
    }

    /**
     *  @brief  Finds the shortest path and puts it into the trie.
     *  @return  True if found one, false otherwise.
     */
    bool init()
    {
	Path_t shortest = spfa(S);
	if (shortest.second == infinity)
	    return false;
	Viit i = shortest.first.begin();
	trie.insert(i, shortest.first.end());
	find_candidates(trie.root, i, shortest.first.end() - 1);
	return true;
    }

    /**
     *  @brief  Finds the next shortest path and puts it into the trie.
     *  @return  True if found one, false otherwise.
     */
    bool find_next()
    {
	if (heap.empty())
	    return false;
	Heap_Elmt x = heap.top();
	heap.pop();
	Viit i = x.path.first.begin() + (x.vrtx->path.first.size() - 1);
	trie.insert(i + 1, x.path.first.end(), x.vrtx);
	find_candidates(x.vrtx, i, x.path.first.end() - 1);
	return true;
    }

    /**
     *  @brief  Calculates the shortest path from @p u to T.
     *          Vertices that are masked in @p now->mask are unreachable.
     *  @return  The shortest path from @p u to @p dest.
     */
    Path_t spfa(const int u, const Trie_t::pntr now)
    {
	static int dist[maxn], pre[maxn];
	static bool in[maxn];
	std::queue<int> q;
	memset(dist, 0x3f, sizeof dist);
	dist[u] = 0;
	pre[u] = -1;
	for (int v = 0; v < n; ++v)
	    if (G[u][v] != infinity && (!now || (!(now->mask & (1ull << v))
			    && !now->son[v])))
	    {
		dist[v] = G[u][v];
		in[v] = true;
		pre[v] = u;
		q.push(v);
	    }
	while (!q.empty())
	{
	    const int x = q.front();
	    q.pop();
	    in[x] = false;
	    for (int v = 0, t; v < n; ++v)
		if (((t = dist[x] + G[x][v]) < dist[v] ||
			    (t == dist[v] && x < pre[v])) &&
			(!now || !(now->mask & (1ull << v))))
		{
		    dist[v] = t;
		    pre[v] = x;
		    if (!in[v])
		    {
			in[v] = true;
			q.push(v);
		    }
		}
	}
	if (dist[T] == infinity)
	    return make_pair(Vint(), infinity);
	else
	{
	    static int l[maxn];
	    int lc = 0;
	    for (int z = T; z != -1; z = pre[z])
		l[lc++] = z;
	    Vint v(lc);
	    for (int i = 0; i < lc; ++i)
		v[i] = l[lc - i - 1];
	    return make_pair(v, dist[T]);
	}
    }

    void Trie_t::clear()
    {
	nc = 0;
	memset(node, 0, sizeof node);
	root = 0;
	lastins = 0;
    }

    bool go()
    {
	scanf("%d%d%d%d%d", &n, &m, &k, &S, &T);
	if ((n | m | k | S | T) == 0)
	    return false;
	memset(G, 0x3f, sizeof G);
	heap = std::priority_queue<Heap_Elmt>();
	trie.clear();
	std::swap(--S, --T);
	for (int i = 0, a, b, c; i < m; ++i)
	{
	    scanf("%d%d%d", &a, &b, &c);
	    G[b - 1][a - 1] = c;
	}

	if (init())
	    do {
		if (--k == 0)
		{
		    trie.output();
		    return true;
		}
	    } while (find_next());
	printf("None\n");
	return true;
    }
}

int main()
{
    while (go());
}
