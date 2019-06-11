#include <cstdio>
#include <cstring>
#include <algorithm>

struct p_t
{
	int x, y;
	bool operator<(const p_t& o) const
	{
		return x < o.x || (x == o.x && y < o.y);
	}
};

const int maxn = 2003;
int n;
p_t p[maxn];
int t[2][maxn];

void add(int row, int col, int val)
{
	if (row > 1)
	{
#ifdef DB
		fprintf(stderr, "%d, not added\n", val);
#endif
		return;
	}
	col = std::min(col, t[row][0] + 1);
	/*
	if (t[row][col] == 0)
	{
#ifdef DB
		fprintf(stderr, "%d, row %d, col %d\n", val, row, col);
#endif
		++t[row][0];
		t[row][col] = val;
	}
	else
	*/
	{
		while (t[row][col] > val && col >= 1)
			--col;
		++col;
		std::swap(val, t[row][col]);
		if (val)
			add(row + 1, col, val);
		else
			++t[row][0];
	}
}

int main()
{
	scanf("%d", &n);
	for (int i = 0; i < n; ++i)
		scanf("%d%d", &p[i].x, &p[i].y);
	std::sort(p, p + n);
	//memset(t, 0x70, sizeof t);
	//t[0][0] = t[1][0] - 0;
	for (int i = 0; i < n; ++i)
		add(0, t[0][0] + 1, p[i].y);
	printf("%d\n", t[0][0] + t[1][0]);
}
