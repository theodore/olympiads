/*
PROB:rectbarn
LANG:C++
*/
#include <cstdio>
#include <cstdlib>
#include <cstring>

const int N(3003);
const int P(30003);

namespace parole
{
	struct point
	{
		int x, y;
	};

	inline int min(int, int);
	inline int max(int, int);
	void init();
	int answer();
	int cmp(const void*, const void*);

	int n, m, p, now_p(0);
	point bad[P];
	int left[N], right[N], up[N];
	int ans_l[N], ans_r[N];
	bool bad_point[N];
}

int parole::answer()
{
	int ret(0);
	for (int i = 0; i < n; ++i)
	{
		memset(bad_point, false, sizeof(bad_point));
		for (; now_p < p && bad[now_p].x == i; ++now_p)
			bad_point[bad[now_p].y] = true;

		for (int i = 0; i < m; ++i)
			up[i] = bad_point[i] ? 0 : up[i] + 1;
		left[0] = bad_point[0] ? 0 : 1;
		for (int i = 1; i < m; ++i)
			left[i] = bad_point[i] ? 0 : left[i-1] + 1;
		right[m-1] = bad_point[m-1] ? 0 : 1;
		for (int i = m - 2; i >= 0; --i)
			right[i] = bad_point[i] ? 0 : right[i+1] + 1;

		for (int i = 0; i < m; ++i)
		{
			if (up[i] == 1)
			{
				ans_l[i] = left[i];
				ans_r[i] = right[i];
			}
			else
			{
				ans_l[i] = min(ans_l[i], left[i]);
				ans_r[i] = min(ans_r[i], right[i]);
			}
#ifdef DB
			printf("i = %d, up = %d, ans_l = %d, ans_r = %d\n", i, up[i], ans_l[i], ans_r[i]);
#endif
			ret = max(ret, up[i] * (ans_l[i] + ans_r[i] - 1));
		}
#ifdef DB
		printf("line = %d, ret = %d\n", i, ret);
#endif
	}
	return ret;
}

inline int parole::min(int a, int b)
{
	return (a < b) ? a : b;
}

inline int parole::max(int a, int b)
{
	return (a > b) ? a : b;
}

void parole::init()
{
	scanf("%d%d%d", &n, &m, &p);
	for (int i = 0; i < p; ++i)
	{
		scanf("%d%d", &bad[i].x, &bad[i].y);
		--bad[i].x;
		--bad[i].y;
	}
	qsort(bad, p, sizeof(bad[0]), cmp);
}

int parole::cmp(const void * A, const void * B)
{
	point * a = (point*)A, * b = (point*)B;
	if (a->x != b->x)
		return a->x - b->x;
	else
		return a->y - b->y;
}

int main()
{
	freopen("rectbarn.in", "r", stdin);
	freopen("rectbarn.out", "w", stdout);
	parole::init();
	printf("%d\n", parole::answer());
	return 0;
}
