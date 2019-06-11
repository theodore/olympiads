/*
 * $File: gss2.cpp
 * $Date: Wed Apr 21 13:59:04 2010 +0800
 */
#define INPUT	"gss2.in"
#define OUTPUT	"gss2.out"
#define STDIO

#include <cstdio>
#include <cstring>

namespace Solve
{
	const int SEQLEN_MAX = 100005, TREE_SIZE = SEQLEN_MAX * 4;

	inline int max(int a, int b)
	{return a > b ? a : b;}

	struct Node
	{
		int low, high,
			max, max_history, relax, relax_history;
		inline void add_relax(int val);
	};
	Node tree[TREE_SIZE];
#define CH_LEFT(_p_) (((_p_) << 1) + 1)
#define CH_RIGHT(_p_) (((_p_) + 1) << 1)
	void apply_relax(int root);
	void add(int root, int low, int high, int val);
	int ask_max_history(int root, int low, int high);
	void make_tree(int root, int low, int high);

	const int NUM_RANGE = 100005, NQUERY_MAX = 100005;
	struct Query
	{
		int left, right, num;
	};
	Query query[NQUERY_MAX];
	int nquery;
	void sort(int left, int right);
	int last_pos[NUM_RANGE * 2], data[SEQLEN_MAX];

	void solve(FILE *fin, FILE *fout);
}

void Solve::solve(FILE *fin, FILE *fout)
{
	const int BUFFER_SIZE = 1024 * 1024 * 5;
	static char buffer[BUFFER_SIZE];
	char *ptr = buffer, *buf_end = buffer +1;
#define PTR_NEXT() \
	{ \
		ptr ++; \
		if (ptr == buf_end) \
		{ \
			ptr = buffer; \
			buf_end = buffer + fread(buffer, 1, BUFFER_SIZE, fin); \
		} \
	}
#define READ_INT(_n_) \
	{ \
		while ((*ptr < '0' || *ptr > '9') && *ptr != '-') \
			PTR_NEXT(); \
		bool _nega_; \
		if (*ptr == '-') \
		{ \
			_nega_ = true; \
			PTR_NEXT(); \
		} else _nega_ = false; \
		int register _x_ = 0; \
		while (*ptr >= '0' && *ptr <= '9') \
		{ \
			_x_ = _x_ * 10 + *ptr - '0'; \
			PTR_NEXT(); \
		} \
		(_n_) = _nega_ ? -_x_ : _x_; \
	}
	PTR_NEXT();

	static int ans[NQUERY_MAX];

	int n;
	READ_INT(n);
	make_tree(0, 0, n - 1);
	for (int i = 0; i < n; i ++)
		READ_INT(data[i]);
	READ_INT(nquery);
	for (int i = 0; i < nquery; i ++)
	{
		READ_INT(query[i].left);
		READ_INT(query[i].right);
		query[i].left --;
		query[i].right --;
		query[i].num = i;
	}
	sort(0, nquery - 1);
	memset(last_pos, -1, sizeof(last_pos));
	for (int i = 0, qpos = 0; i < n && qpos < nquery; i ++)
	{
		add(0, last_pos[data[i] + NUM_RANGE] + 1, i, data[i]);
		last_pos[data[i] + NUM_RANGE] = i;
		while (qpos < nquery && query[qpos].right == i)
		{
			ans[query[qpos].num] = ask_max_history(0, query[qpos].left, i);
			qpos ++;
		}
	}

	for (int i = 0; i < nquery; i ++)
		fprintf(fout, "%d\n", ans[i]);

#undef PTR_NEXT
#undef READ_INT
}

void Solve::sort(int left, int right)
{
	if (left >= right)
		return;
	int register i = left, j = right, mid = query[(i + j) >> 1].right;
	while (i <= j)
	{
		while (query[i].right < mid)
			i ++;
		while (query[j].right > mid)
			j --;
		if (i <= j)
		{
			Query x = query[i];
			query[i] = query[j];
			query[j] = x;
			i ++;
			j --;
		}
	}
	sort(left, j);
	sort(i, right);
}

void Solve::make_tree(int root, int low, int high)
{
	tree[root].low = low;
	tree[root].high = high;
	tree[root].max = tree[root].max_history =
		tree[root].relax = tree[root].relax_history = 0;
	if (low != high)
	{
		int mid = (low + high) >> 1;
		make_tree(CH_LEFT(root), low, mid);
		make_tree(CH_RIGHT(root), mid + 1, high);
	}
}

void Solve::Node::add_relax(int val)
{
	relax += val;
	if (relax > relax_history)
		relax_history = relax;
	max += val;
	if (max > max_history)
		max_history = max;
}

void Solve::apply_relax(int root)
{
	if ((tree[root].relax == 0 && tree[root].relax_history == 0) ||
			tree[root].low == tree[root].high)
		return;
	int r = tree[root].relax, rh = tree[root].relax_history,
		chl = CH_LEFT(root), chr = CH_RIGHT(root);
	tree[root].relax = 0;
	tree[root].relax_history = 0;

	tree[chl].add_relax(rh);
	tree[chr].add_relax(rh);
	tree[chl].add_relax(r - rh);
	tree[chr].add_relax(r - rh);
}

void Solve::add(int root, int low, int high, int val)
{
	if (low == tree[root].low && high == tree[root].high)
	{
		tree[root].add_relax(val);
		return;
	}
	apply_relax(root);
	int chl = CH_LEFT(root), chr = CH_RIGHT(root), mid = (tree[root].low + tree[root].high) >> 1;
	if (high <= mid)
		add(chl, low, high, val);
	else if (low > mid)
		add(chr, low, high, val);
	else
	{
		add(chl, low, mid, val);
		add(chr, mid + 1, high, val);
	}
	tree[root].max = max(tree[chl].max, tree[chr].max);
	tree[root].max_history = max(tree[chl].max_history, tree[chr].max_history);
}

int Solve::ask_max_history(int root, int low, int high)
{
	apply_relax(root);
	if (low == tree[root].low && high == tree[root].high)
		return tree[root].max_history;
	int chl = CH_LEFT(root), chr = CH_RIGHT(root), mid = (tree[root].low + tree[root].high) >> 1;
	if (high <= mid)
		return ask_max_history(chl, low, high);
	if (low > mid)
		return ask_max_history(chr, low, high);
	return max(ask_max_history(chl, low, mid), ask_max_history(chr, mid + 1, high));
}

int main()
{
	Solve::solve(stdin, stdout);
}


