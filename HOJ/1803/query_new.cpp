/** @file query_new.cpp
 *  @version 2.0
 *  @date Wed Aug 25 2010, 8:49:20 PM +0800
 *  @author Theodore You
 *  Just using BFS and change the problem to "k-th value in a sequence".
 */
#include <cstdio>
#include <cassert>

#define maxn 100010
#define maxm 10010
#define maxN (1 << 18)

int n, m, N;
int label[maxn];
int start[maxn], to[maxn<<1], next[maxn<<1], edge;
int maxv(-1), minv(1<<30);
int left[maxn], right[maxn];
int (*seq[maxN])[2]; ///< 0 -- index, 1 -- label.
int sc;
int size[maxN];
bool vis[maxn];
char buf[3000010];
char* p(buf);

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

#define input(x) \
{ \
	while (*p < '0' || *p > '9') ++p; \
	for (x = 0; *p >= '0' && *p <= '9'; ++p) x = x * 10 + *p - '0'; \
}

#define add(a, b)\
{\
	to[++edge] = b;\
	next[edge] = start[a];\
	start[a] = edge;\
}

void dfs(int x)
{
	++sc;
	vis[x] = true;
	left[x] = sc + N;
	seq[sc+N] = new int[1][2];
	seq[sc+N][0][0] = x;
	seq[sc+N][0][1] = label[x];
	size[sc+N] = 1;
	for (int e = start[x]; e; e = next[e])
		if (!vis[to[e]])
			dfs(to[e]);
	right[x] = sc + N;
}

int ans;

int smaller_than(int n, int x)
{
	if (size[n] == 0)
		return 0;
	int min, mid, max;
	for (min = 0, max = size[n] - 1, mid = max >> 1;
			min <= max; mid = (min + max) >> 1)
	{
#define s seq[n][mid][1]
		if (s == x)
		{
			ans = seq[n][mid][0];
			return mid;
		}
		else if (s < x)
			min = mid + 1;
		else
			max = mid - 1;
#undef s
	}
	return MAX(min, max);
}

int answer(int x, int k)
{
	for (int min = minv, max = maxv, mid = (minv + maxv) >> 1;
			min <= max; mid = (min + max) >> 1)
	{
#ifdef DB
		printf("%d, %d, %d\n", min, max, mid);
#endif
		int c = 0;
		ans = 0;
		for (int l = left[x] - 1, r = right[x] + 1; l ^ r ^ 1; l >>= 1, r >>= 1)
		{
			if (~l & 1)
				c += smaller_than(l ^ 1, mid);
			if (r & 1)
				c += smaller_than(r ^ 1, mid);
#ifdef DB
			printf("%d, %d, c = %d\n", l, r, c);
#endif
		}
#ifdef DB
		putchar(10);
#endif
		if (c == k - 1 && ans)
			return ans;
		else if (c < k)
		{
			//assert(min != mid);
			min = mid + 1;
		}
		else
			max = mid - 1;
	}
	assert(0);
}

int main()
{
#ifdef GDB
	freopen("in", "r", stdin);
#endif
	fread(buf, 1, 3000000, stdin);
	input(n);
	for (N = 4; N - 2 < n; N <<= 1);
	for (register int i = 1; i <= n; ++i)
	{
		input(label[i]);
		minv = MIN(minv, label[i]);
		maxv = MAX(maxv, label[i]);
	}
	for (register int i = 0; i < n - 1; ++i)
	{
		static int a, b;
		input(a);
		input(b);
		add(a, b);
		add(b, a);
	}
	dfs(1);
	for (int f = N - 1; f; --f)
	{
#define l (f<<1)
#define r ((f<<1)+1)
		size[f] = size[l] + size[r];
		seq[f] = new int [size[f]][2];
		register int i(0), j(0), p(0);
		for (; i < size[l] && j < size[r]; ++p)
		{
			if (seq[l][i][1] < seq[r][j][1])
			{
				seq[f][p][0] = seq[l][i][0];
				seq[f][p][1] = seq[l][i][1];
				++i;
			}
			else
			{
				seq[f][p][0] = seq[r][j][0];
				seq[f][p][1] = seq[r][j][1];
				++j;
			}
		}
		if (i < size[l])
		{
			for (; i < size[l]; ++i, ++p)
			{
				seq[f][p][0] = seq[l][i][0];
				seq[f][p][1] = seq[l][i][1];
			}
		}
		if (j < size[r])
		{
			for (; j < size[r]; ++j, ++p)
			{
				seq[f][p][0] = seq[r][j][0];
				seq[f][p][1] = seq[r][j][1];
			}
		}
		assert(p == size[f]);
#undef l
#undef r
	}
	input(m);
	while (m--)
	{
		static int a, b;
		input(a);
		input(b);
		printf("%d\n", answer(a, b));
	}
	return 0;
}
