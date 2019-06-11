#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>

const int maxn = 103;
const int maxb = 7003;

struct pair
{
	int l, r;
	pair operator+(const int& x)
	{
		pair z;
		z.l = l + x;
		z.r = r + x;
		return z;
	}
	void operator=(const pair& x)
	{
		l = x.l;
		r = x.r;
	}
};

class set_t
{
public:
	set_t();
	void clear();
	void add(const int);
	int size() const;
	void operator=(const set_t&);
	int answer() const;
private:
	int n;
	pair a[10003];
};

set_t::set_t() : n(1)
{
	a[0].l = a[0].r = 0;
}

void set_t::clear()
{
	n = 1;
	a[0].l = a[0].r = 0;
}

void set_t::add(const int x)
{
	const static int inf = -1u >> 1;
	static pair b[20003], c[20003];
	for (int i = 0; i < n; ++i)
		b[i] = a[i] + x;
	a[n].l = a[n].r = b[n].l = b[n].r = inf;
	int i = 0, j = 0;
	while (b[j].r < 0)
		++j;
	b[j].l = std::max(1, b[j].l);
	int cc = 0;
	for (; a[i].r != inf || b[j].r != inf; )
	{
		if (a[i].l == b[j].l)
			++(a[i].r < b[j].r ? i : j);
		const pair& t = a[i].l < b[j].l ? a[i++] : b[j++];
		if (cc && t.l <= c[cc - 1].r + 1)
			c[cc - 1].r = std::max(c[cc - 1].r, t.r);
		else
			c[cc++] = t;
	}
	memcpy(a, c, sizeof a[0] * size_t(n = cc));
}

int set_t::size() const
{
	int s = -1;
	for (int i = 0; i < n; ++i)
		s += a[i].r - a[i].l + 1;
	return s;
}

void set_t::operator=(const set_t& x)
{
	memcpy(a, x.a, sizeof a[0] * size_t(n = x.n));
}

int set_t::answer() const
{
	if (a[0].r >= 1)
		return a[0].r + 1;
	else
		return 1;
}

int n;
int pack[maxn];
int cmax, id;
set_t a;

void work(int l, int r, set_t s)
{
#ifdef DB
	fprintf(stderr, "%d %d\n", l, r);
#endif
	if (l + 1 == r)
	{
		int t = s.size();
		if (t > cmax || (t == cmax && pack[l] < pack[id]))
		{
			cmax = t;
			id = l;
		}
		return;
	}
	a = s;
	int mid = (l + r) / 2;
	for (int i = mid; i < r; ++i)
		a.add(pack[i]);
	work(l, mid, a);
	for (int i = l; i < mid; ++i)
		s.add(pack[i]);
	work(mid, r, s);
}

int calc()
{
	a.clear();
	for (int i = 0; i < n; ++i)
		if (i != id)
			a.add(pack[i]);
	for (int i = 0; i < n; ++i)
		if (i != id)
			a.add(-pack[i]);
	return a.answer();
}

int main()
{
	scanf("%d", &n);
	for (int i = 0; i < n; ++i)
		scanf("%d", &pack[i]);
	work(0, n, set_t());
	printf("%d %d\n", pack[id], calc());
}
