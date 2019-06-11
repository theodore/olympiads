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
	pair a[maxn * maxb];
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
	static pair b[maxn * maxb], c[maxn * maxb];
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
int ans;
set_t a, b;

void test(const int l, const int r)
{
	a.clear();
	for (int i = 0; i < l; ++i)
		a.add(pack[i]);
	for (int i = r; i < n; ++i)
		a.add(pack[i]);
	for (int i = l; i < r; ++i)
	{
		b = a;
		for (int j = l; j < r; ++j)
			if (i != j)
				b.add(pack[j]);
		int t = b.size();
#ifdef DB
		fprintf(stderr, "%d t = %d\n", i, t);
#endif
		if (t > cmax || (t == cmax && pack[i] < pack[id]))
		{
			cmax = t;
			id = i;
		}
	}
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
	int l = int(sqrt(n));
	for (int i = 0; i < n; i += l)
		test(i, std::min(n, i + l));
#ifdef DB
	fprintf(stderr, "%d\n", __LINE__);
#endif
	printf("%d %d\n", pack[id], calc());
}
