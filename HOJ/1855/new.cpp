#include <cstdio>
#include <cstring>
#include <algorithm>
#include <deque>

#ifdef DB
# include <iostream>
#endif

const int maxn(2003);
const int maxm(2003);
int n, m, w;
int f[maxn][maxn];

struct T
{
	T(): val(0), pos(0){}
	T(const int v, const int p): val(v), pos(p){}
	int val, pos;
};
std::deque<T> q;

int main()
{
	scanf("%d%d%d", &n, &m, &w);
	memset(f[0], 0xc0, sizeof f[0]);
	f[0][0] = 0;
	for (int i = 1, pb, ps, lb, ls; i <= n; ++i)
	{
		scanf("%d%d%d%d", &pb, &ps, &lb, &ls);
		while (!q.empty())
			q.pop_front();
		for (int j = 0; j <= m; ++j)
		{
#ifdef DB
			fprintf(stderr, "%d %d\n", i, j);
#endif
			f[i][j] = f[i - 1][j];
			const int nval = f[std::max(0, i - w - 1)][j] + j * pb;
			while (!q.empty() && q.back().val <= nval)
				q.pop_back();
			q.push_back(T(nval, j));
			if (q.front().pos < j - lb)
				q.pop_front();
#ifdef DB
			fprintf(stderr, "\t");
			for (std::deque<T>::iterator k = q.begin(); k != q.end(); ++k)
				fprintf(stderr, "<%d, %d> ", k->pos, k->val);
			fprintf(stderr, "\n");
#endif
			int t;
			if ((t = q.front().val - j * pb) > f[i][j])
				f[i][j] = t;
		}
		while (!q.empty())
			q.pop_front();
		for (int j = m; j >= 0; --j)
		{
#ifdef DB
			fprintf(stderr, "%d %d\n", i, j);
#endif
			const int nval = f[std::max(0, i - w - 1)][j] - (m - j) * ps;
			while (!q.empty() && q.back().val <= nval)
				q.pop_back();
			q.push_back(T(nval, j));
			if (q.front().pos > j + ls)
				q.pop_front();
#ifdef DB
			fprintf(stderr, "\t");
			for (std::deque<T>::iterator k = q.begin(); k != q.end(); ++k)
				fprintf(stderr, "<%d, %d> ", k->pos, k->val);
			fprintf(stderr, "\n");
#endif
			int t;
			if ((t = q.front().val + (m - j) * ps) > f[i][j])
				f[i][j] = t;
		}
	}
	printf("%d\n", f[n][0]);
#ifdef DB
	for (int i = 0; i <= n; ++i)
	{
		for (int j = 0; j <= m; ++j)
			fprintf(stderr, "%d ", f[i][j]);
		fprintf(stderr, "\n");
	}
#endif
	return 0;
}
