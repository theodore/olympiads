// RMQ
// Jul 31, 4:26 PM
#include <cstdio>
#include <cassert>

namespace blob
{
	struct pair
	{
		void init();
		int max, min;
	};

	struct node_t
	{
		pair ask(int, int);
		pair data;
		int l, r;
		int son[2];
	};

	int max(int, int);
	int min(int, int);
	/*
	int MAX(int, int, int);
	int MIN(int, int, int);
	*/
	int build(int, int);
	int ask(int, int);
	pair better(pair, pair);

	const int N(50010);
	int n, num[N], cnt;
	node_t node[2 * N];
}

blob::pair blob::better(blob::pair a, blob::pair b)
{
	pair ret;
	ret.max = max(a.max, b.max);
	ret.min = min(a.min, b.min);
	return ret;
}

blob::pair blob::node_t::ask(int L, int R)
{
	if (L == l && R == r)
		return data;
	int mid((l + r) / 2);
	if (R <= mid)
		return node[son[0]].ask(L, R);
	else if (L >= mid)
		return node[son[1]].ask(L, R);
	else
		return better(node[son[0]].ask(L, mid), node[son[1]].ask(mid, R));
}

int blob::max(int a, int b)
{
	return (a > b) ? a : b;
}

int blob::min(int a, int b)
{
	return (a < b) ? a : b;
}

/*
int blob::MAX(int a, int b, int c)
{
	if (b > a)
		a = b;
	if (c > a)
		a = c;
	return a;
}

int blob::MIN(int a, int b, int c)
{
	if (b < a)
		a = b;
	if (c < a)
		a = c;
	return a;
}
*/

void blob::pair::init()
{
	max = 0;
	min = 1000000;
}

int blob::build(int l, int r)
{
	if (l == r)
		assert(0);
	node_t & x = node[++cnt];
	int ret = cnt, mid = (l + r) / 2;
	x.l = l;
	x.r = r;
	if (l + 1 == r)
	{
		x.son[0] = x.son[1] = 0;
		x.data.max = x.data.min = num[l];
	}
	else
	{
		x.son[0] = build(l, mid);
		x.son[1] = build(mid, r);
		x.data = better(node[x.son[0]].data, node[x.son[1]].data);
	}
	return ret;
}

int blob::ask(int l, int r)
{
	pair ret = node[1].ask(l, r);
	return ret.max - ret.min;
}

int main()
{
#ifdef LOCAL
	freopen("in", "r", stdin);
#endif
	int q;
	scanf("%d%d", &blob::n, &q);
	for (int i = 0; i < blob::n; ++i)
		scanf("%d", &blob::num[i]);
	blob::node[0].data.init();
	blob::build(0, blob::n);
	while (q--)
	{
		static int a, b;
		scanf("%d%d", &a, &b);
		printf("%d\n", blob::ask(a - 1, b));
	}
	return 0;
}
