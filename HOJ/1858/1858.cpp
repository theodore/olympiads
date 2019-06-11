// Fri Aug 6, about 6:30 PM
// Fri Aug 6, 10:50 PM
// Error #1: didn't add parentheses around the equal sign, so the priority got wrong
// Error #2: still priority error... no parentheses around operator ?:
#include <cstdio>
#include <cassert>
#include <cstdarg>

namespace criminate
{
	int build(const int, const int);
	void turn(const int, const int, const int);
	void reverse(const int, const int);
	int total(const int, const int);
	int consecutive(const int, const int);
	inline int max(int, ...);
	inline void swap(int&, int&);
	struct node_t
	{
		int asknum(int);
		int askcon(int);
		int askl(int);
		int askr(int);
		void putdown();
		void update();
		void turn(const int, const int, const int);
		void reverse(const int, const int);
		int total(const int, const int);
		int consecutive(const int, const int);
		int conl(const int, const int);
		int conr(const int, const int);
		// 001 for all to 0
		// 010 for all to 1
		// 100 for rev
		int label, data;
		int num[2], con[2], l[2], r[2];
		int left, right, son[2];
	};
	const int N(100010);
	int root;
	node_t node[N];
#ifdef DB
	void tab(int);
	void output(int = -1, int = 0);
#endif
}

int criminate::node_t::asknum(int x)
{
	switch(label)
	{
		case 0:
			return num[x];
		case 1: case 2:
			if (x + 1 == label)
				return right - left;
			else
				return 0;
		case 4:
			return num[x^1];
		default:
			assert(0);
	}
}

int criminate::node_t::askcon(int x)
{
	switch(label)
	{
		case 0:
			return con[x];
		case 1: case 2:
			if (x + 1 == label)
				return right - left;
			else
				return 0;
		case 4:
			return con[x^1];
		default:
			assert(0);
	}
}

int criminate::node_t::askl(int x)
{
	switch(label)
	{
		case 0:
			return l[x];
		case 1: case 2:
			if (x + 1 == label)
				return right - left;
			else
				return 0;
		case 4:
			return l[x^1];
		default:
			assert(0);
	}
}

int criminate::node_t::askr(int x)
{
	switch(label)
	{
		case 0:
			return r[x];
		case 1: case 2:
			if (x + 1 == label)
				return right - left;
			else
				return 0;
		case 4:
			return r[x^1];
		default:
			assert(0);
	}
}

void criminate::node_t::putdown()
{
	switch(label)
	{
		case 1: case 2:
			data = label - 1;
			node[son[0]].label = node[son[1]].label = label;
			con[data] = l[data] = r[data] = num[data] = right - left;
			con[!data] = l[!data] = r[!data] = num[!data] = 0;
			break;
		case 4:
			data ^= 1;
			if (node[son[0]].label == 4 || node[son[0]].label == 0)
				node[son[0]].label ^= 4;
			else
				node[son[0]].label = ((node[son[0]].label - 1) ^ 1) + 1;
			if (node[son[1]].label == 4 || node[son[1]].label == 0)
				node[son[1]].label ^= 4;
			else
				node[son[1]].label = ((node[son[1]].label - 1) ^ 1) + 1;
			swap(num[0], num[1]);
			swap(con[0], con[1]);
			swap(l[0], l[1]);
			swap(r[0], r[1]);
			break;
		default:
			assert(label == 0);
	}
	label = 0;
}

void criminate::node_t::update()
{
	for (int i = 0; i < 2; ++i)
	{
		num[i] = node[son[0]].asknum(i) + node[son[1]].asknum(i) + (data == i);
		con[i] = max(3, node[son[0]].askcon(i), node[son[1]].askcon(i), (data == i) ? node[son[0]].askr(i) + 1 + node[son[1]].askl(i) : 0);
		l[i] = node[son[0]].askl(i) + ((node[son[0]].asknum(i^1) == 0 && data == i) ? 1 + node[son[1]].askl(i) : 0);
		r[i] = node[son[1]].askr(i) + ((node[son[1]].asknum(i^1) == 0 && data == i) ? 1 + node[son[0]].askr(i) : 0);
	}
}

void criminate::node_t::turn(const int L, const int R, const int x)
{
	if (label == 1 << x)
		return;
	if (L == left && R == right)
	{
		label = 1 << x;
		return;
	}
	putdown();
	const int mid = (left + right) / 2;
	if (R <= mid)
		node[son[0]].turn(L, R, x);
	else if (L > mid)
		node[son[1]].turn(L, R, x);
	else
	{
		data = x;
		if (L < mid)
			node[son[0]].turn(L, mid, x);
		if (R > mid + 1)
			node[son[1]].turn(mid + 1, R, x);
	}
	update();
}

void criminate::node_t::reverse(const int L, const int R)
{
	if (L == left && R == right)
	{
		if (label == 0 || label == 4)
			label ^= 4;
		else
			label = ((label - 1) ^ 1) + 1;
		return;
	}
	putdown();
	const int mid = (left + right) / 2;
	if (R <= mid)
		node[son[0]].reverse(L, R);
	else if (L > mid)
		node[son[1]].reverse(L, R);
	else
	{
		data ^= 1;
		if (L < mid)
			node[son[0]].reverse(L, mid);
		if (R > mid + 1)
			node[son[1]].reverse(mid + 1, R);
	}
	update();
}

int criminate::node_t::total(const int L, const int R)
{
	putdown();
	if (L == left && R == right)
		return num[1];
	const int mid = (left + right) / 2;
	if (R <= mid)
		return node[son[0]].total(L, R);
	else if (L > mid)
		return node[son[1]].total(L, R);
	else
	{
		int r = data == 1;
		if (L < mid)
			r += node[son[0]].total(L, mid);
		if (R > mid + 1)
			r += node[son[1]].total(mid + 1, R);
		return r;
	}
}

int criminate::node_t::consecutive(const int L, const int R)
{
	putdown();
	if (L == left && R == right)
		return con[1];
	const int mid = (left + right) / 2;
	if (R <= mid)
		return node[son[0]].consecutive(L, R);
	else if (L > mid)
		return node[son[1]].consecutive(L, R);
	else
	{
		int r = data == 1;
		if (r)
		{
			if (L < mid)
				r += node[son[0]].conr(L, mid);
			if (R > mid + 1)
				r += node[son[1]].conl(mid + 1, R);
		}
		if (L < mid)
			r = max(2, r, node[son[0]].consecutive(L, mid));
		if (R > mid + 1)
			r = max(2, r, node[son[1]].consecutive(mid + 1, R));
		return r;
	}
}

int criminate::node_t::conl(const int L, const int R)
{
	assert(L == left);
	putdown();
	if (R == right)
		return l[1];
	const int mid = (left + right) / 2;
	if (R <= mid)
		return node[son[0]].conl(L, R);
	else
	{
		if (node[son[0]].asknum(0))
			return node[son[0]].conl(L, mid);
		else
		{
			int r = data == 1;
			if (r)
				if (R > mid + 1)
					r += node[son[1]].conl(mid + 1, R);
			return node[son[0]].right - node[son[0]].left + r;
		}
	}
}

int criminate::node_t::conr(const int L, const int R)
{
	assert(R == right);
	putdown();
	if (L == left)
		return r[1];
	const int mid = (left + right) / 2;
	if (L > mid)
		return node[son[1]].conr(L, R);
	else
	{
		if (node[son[1]].asknum(0))
			return node[son[1]].conr(mid + 1, R);
		else
		{
			int r = data == 1;
			if (r)
				if (L < mid)
					r += node[son[0]].conr(L, mid);
			return node[son[1]].right - node[son[1]].left + r;
		}
	}
}

int criminate::build(const int l, const int r)
{
	if (l == r)
		return 0;
	const int mid = (l + r) / 2;
	node_t & x = node[mid];
	x.left = l;
	x.right = r;
	x.son[0] = build(l, mid);
	x.son[1] = build(mid + 1, r);
	x.update();
	return mid;
}

inline int criminate::max(int n, ...)
{
	int r;
	va_list l;
	va_start(l, n);
	for (int i = 0; i < n; ++i)
	{
		static int c;
		c = va_arg(l, int);
		if (i == 0 || c > r)
			r = c;
	}
	return r;
}

inline void criminate::swap(int & a, int & b)
{
	int t = a;
	a = b;
	b = t;
}

void criminate::turn(const int l, const int r, const int x)
{
	node[root].turn(l, r, x);
}

void criminate::reverse(const int l, const int r)
{
	node[root].reverse(l, r);
}

int criminate::total(const int l, const int r)
{
	return node[root].total(l, r);
}

int criminate::consecutive(const int l, const int r)
{
	return node[root].consecutive(l, r);
}

int main()
{
#ifdef LOCAL
	//freopen("in", "r", stdin);
#ifndef GDB
	//freopen("out", "w", stdout);
#endif
#endif
	int n, m;
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i)
		scanf("%d", &criminate::node[i].data);
	criminate::root = criminate::build(1, n + 1);
#ifdef DB
	criminate::output();
#endif
	while (m--)
	{
		static int a, b, c;
		scanf("%d%d%d", &a, &b, &c);
		++b;
		c += 2;
		switch(a)
		{
			case 0: case 1:
				criminate::turn(b, c, a);
				break;
			case 2:
				criminate::reverse(b, c);
				break;
			case 3:
				printf("%d\n", criminate::total(b, c));
				break;
			case 4:
				printf("%d\n", criminate::consecutive(b, c));
				break;
			default:
				fprintf(stderr, "Fatal error: a = %d\n", a);
				assert(0);
		}
#ifdef DB
		criminate::output();
#endif
	}
	return 0;
}

#ifdef DB
void criminate::tab(int x)
{
	for (int i = 0; i < x; ++i)
		printf("| ");
}

void criminate::output(int a, int t)
{
	if (a == -1)
	{
		putchar(10);
		a = root;
	}
	tab(t++);
	node_t & x = node[a];
	printf("%d, label = %d, data = %d, num = {%d, %d}, con = {%d, %d}, l = {%d, %d}, r = {%d, %d}, left = %d, right = %d, son = {%d, %d}\n", a, x.label, x.data, x.num[0], x.num[1], x.con[0], x.con[1], x.l[0], x.l[1], x.r[0], x.r[1], x.left, x.right, x.son[0], x.son[1]);
	if (x.son[0])
		output(x.son[0], t);
	if (x.son[1])
		output(x.son[1], t);
}
#endif
