#include <cstdio>

#define ll long long
#ifdef unix
# define lld "%lld"
#else
# define lld "%I64d"
#endif

namespace repo
{
	void add          (ll, ll, ll);
	void reverse      (ll, ll);
	ll  findmax      (ll, ll);

	ll  max   (ll, ll);
	void swap  (ll&, ll&);
	ll  find         (ll);
	void rotate       (ll);
	void splay        (ll, ll = 0);
	ll  roll         (ll&, ll&);
	ll  build        (ll, ll, ll);

	struct node_t
	{
		void update   ();
		bool rev;
		ll data, add;
		ll size, max;
		ll father, son[2];
	};

	const ll MAXN(50010);
	const ll INF(-1ull>>2);
	ll root;
	node_t node[MAXN];
	int cnt(2);
}

void repo::node_t::update()
{
	if (add)
	{
		data += add;
		max += add;
		node[son[0]].add += add;
		node[son[1]].add += add;
		add = 0;
	}
	if (rev)
	{
		node[son[0]].rev ^= 1;
		node[son[1]].rev ^= 1;
		swap(son[0], son[1]);
		rev = false;
	}
	size = 1 + node[son[0]].size + node[son[1]].size;
	max = repo::max(data, node[son[0]].max + node[son[0]].add);
	max = repo::max(max,  node[son[1]].max + node[son[1]].add);
}

ll repo::max(ll a, ll b)
{
	return (a > b) ? a : b;
}

void repo::swap(ll & a, ll & b)
{
	a ^= b;
	b ^= a;
	a ^= b;
}

ll repo::build(ll l, ll r, ll f)
{
	if (l == r)
		return 0;
	ll mid = (l + r) / 2;
	node[mid].father = f;
	node[mid].son[0] = build(l, mid, mid);
	node[mid].son[1] = build(mid + 1, r, mid);
	node[mid].update();
	return mid;
}

void repo::add(ll l, ll r, ll x)
{
	node[roll(l, r)].add += x;
	node[r].update();
	node[l].update();
}

void repo::reverse(ll l, ll r)
{
	node[roll(l, r)].rev ^= 1;
}

ll repo::findmax(ll l, ll r)
{
	ll t = roll(l, r);
	return node[t].max + node[t].add;
}

ll repo::find(ll k)
{
	ll ret = root;
	node[ret].update();
	for (ll t = node[node[ret].son[0]].size + 1;
			t != k;
			t = node[node[ret].son[0]].size + 1)
	{
		if (t < k)
		{
			ret = node[ret].son[1];
			k -= t;
		}
		else
			ret = node[ret].son[0];
		node[ret].update();
	}
	return ret;
}

void repo::rotate(ll y)
{
	ll x = node[y].father, f = node[x].father, d = (y == node[x].son[1]);
	node[y].father = f;
	node[f].son[x==node[f].son[1]] = y;
	node[x].son[d] = node[y].son[!d];
	node[node[y].son[!d]].father = x;
	node[x].father = y;
	node[y].son[!d] = x;
	node[x].update();
	node[y].update();
}

void repo::splay(ll x, ll y)
{
	for (ll f = node[x].father; f != y; f = node[x].father)
	{
		static ll gf;
		gf = node[f].father;
		if (gf != y)
		{
			if ((f == node[gf].son[1]) ^ (x == node[f].son[1]))
			{
				rotate(x);
				rotate(x);
			}
			else
			{
				rotate(f);
				rotate(x);
			}
		}
		else
		{
			rotate(x);
		}
	}
	if (y == 0)
		root = x;
}

ll repo::roll(ll & l, ll & r)
{
	l = find(l);
	splay(l);
	r = find(r);
	splay(r, l);
	return node[r].son[0];
}

int main()
{
	int n, m;
	scanf("%d%d", &n, &m);
	repo::root = repo::build(1, n + 3, 0);
	repo::node[0].max = -repo::INF;
	while (m--)
	{
		static ll a, b, c, d;
		scanf(lld lld lld, &a, &b, &c);
		c += 2;
		switch(a)
		{
			case 1:
				scanf(lld, &d);
				repo::add(b, c, d);
				break;
			case 2:
				repo::reverse(b, c);
				break;
			case 3:
				printf(lld"\n", repo::findmax(b, c));
				break;
		}
	}
	return 0;
}
