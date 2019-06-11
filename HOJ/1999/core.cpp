#include <cstdio>
#include <cstring>

#define max(a, b) ((a) > (b) ? (a) : (b))
#define MAX(a, b, c) max(a, max(b, c))

const int maxn(500003);
const int maxm(1000003);
int n, s;
int start[maxn], to[maxm], next[maxm], len[maxm], edge;

void add(const int& a, const int& b, const int& c)
{
	to[++edge] = b;
	len[edge] = c;
	next[edge] = start[a];
	start[a] = edge;
}

void input()
{
	scanf("%d%d", &n, &s);
	for (int i = 1, a, b, c; i < n; ++i)
	{
		scanf("%d%d%d", &a, &b, &c);
		add(a, b, c);
		add(b, a, c);
	}
}

int q[maxn], h, t;
int dist[maxn];
int l[maxn][2], lc;
int pre[maxn];
int plen[maxn];

void get_longest_chain()
{
	int s, d = 0, x;
	q[0] = 1;
	t = 1;
	dist[1] = 1; // This is to make the search easier.
	while (h != t)
	{
		x = q[h++];
		if (h == maxn)
			h = 0;
		if (dist[x] > d)
		{
			d = dist[x];
			s = x;
		}
		for (int e = start[x]; e; e = next[e])
			if (dist[to[e]] == 0)
			{
				dist[to[e]] = dist[x] + len[e];
				q[t++] = to[e];
				if (t == maxn)
					t = 0;
			}
	}
	memset(dist, 0, sizeof dist);
	q[h = 0] = s;
	t = 1;
	dist[s] = 1;
	d = 0;
	while (h != t)
	{
		x = q[h++];
		if (h == maxn)
			h = 0;
		if (dist[x] > d)
		{
			d = dist[x];
			s = x;
		}
		for (int e = start[x]; e; e = next[e])
			if (dist[to[e]] == 0)
			{
				dist[to[e]] = dist[x] + len[e];
				pre[to[e]] = x;
				plen[to[e]] = len[e];
				q[t++] = to[e];
				if (t == maxn)
					t = 0;
			}
	}
	for (; s; s = pre[s])
	{
		l[++lc][0] = s;
		l[lc][1] = plen[s];
	}
}

int dfs(const int x, const int f)
{
	int r = 0, t;
	for (int e = start[x]; e; e = next[e])
		if (to[e] != f)
		{
			t = dfs(to[e], x) + len[e];
			if (t > r)
				r = t;
		}
	return r;
}

int left[maxn], here[maxn], right[maxn];

// Initialize left, right, here.
void init()
{
	int t;
	for (int i = 1; i <= lc; ++i)
	{
		for (int e = start[l[i][0]]; e; e = next[e])
			if (to[e] != l[i - 1][0] && to[e] != l[i + 1][0])
			{
				t = dfs(to[e], l[i][0]) + len[e];
				if (t > here[i])
					here[i] = t;
			}
		left[i] = max(left[i - 1] + l[i - 1][1], here[i - 1]);
	}
	for (int i = lc; i >= 1; --i)
		right[i] = max(right[i + 1] + l[i][1], here[i + 1]);
#if 0
	for (int i = 1; i <= lc; ++i)
		printf("%d %d %d\n", left[i], here[i], right[i]);
#endif
}

/*
// Answer the problem, using a monotonous queue.
int answer()
{
	int r(-1u>>1);
#ifdef DB
	fprintf(stderr, "r = %d\n", r);
#endif
	// Not using a monotonous queue, just to check if everything is right.
	for (int i = 1, len = 0, j; i <= lc; ++i, len = 0)
	{
		int t = max(here[i], left[i]);
		for (j = i; j <= lc && len <= s; len += l[j][1], ++j)
			if (here[j] > t)
				t = here[j];
		if (right[--j] > t)
			t = right[j];
#ifdef DB
		fprintf(stderr, "%d %d\n", i, t);
#endif
		if (t < r)
			r = t;
	}
	return r;
}
*/

// here, dist
int a[maxn], b[maxn];

void insert(int x)
{
	while (h != t && a[t - 1] <= here[x])
		--t;
	a[t] = here[x];
	b[t++] = dist[x];
	while (s < dist[x] - b[h])
		++h;
}

int front()
{
	return a[h];
}

// The real one
int answer()
{
	// Initialize dist, so it'll be easier to code the queue.
	dist[0] = dist[1] = 0;
	for (int i = 1; i <= lc; ++i)
		dist[i + 1] = dist[i] + l[i][1];
	int x, t, r(-1u>>1);
	// I'm using the previous h and t.
	h = t = 0;
	for (int i = 1, j = 1; i <= lc; ++i)
	{
		insert(i);
		x = front();
		while (dist[i] - dist[j] > s)
			++j;
		t = MAX(left[j], x, right[i]);
		if (t < r)
			r = t;
	}
	return r;
}

int main()
{
	input();
	get_longest_chain();
	init();
	printf("%d\n", answer());
	return 0;
}
