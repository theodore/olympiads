#include <cstdio>

const int N(100);
int n, a[N], pos[N], b[N], posb[N];

void swap(int l, int r)
{
	for (int i = l, j = r - 1; i < r; ++i, --j)
	{
		b[i] = a[j];
		posb[i] = pos[j];
	}
	for (int i = l; i < r; ++i)
	{
		a[i] = b[i];
		pos[i] = posb[i];
	}
}

int main()
{
	freopen("in", "r", stdin);
	freopen("ans", "w", stdout);
	scanf("%d", &n);
	for (int i = 0; i < n; ++i)
	{
		scanf("%d", &a[i]);
		pos[i] = i;
	}
	for (int i = 0; i < n - 1; ++i)
	{
		int min = i;
		for (int j = i + 1; j < n; ++j)
			if (a[j] < a[min] || (a[j] == a[min] && pos[j] < pos[min]))
				min = j;
		printf("%d ", min + 1);
		swap(i, min + 1);
	}
	printf("%d\n", n);
	return 0;
}
