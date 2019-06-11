#include <cstdio>

int a[100010], n, b[100010];

void sort(int l, int r)
{
	if (l + 1 == r)
		return;
	int mid = (l + r) / 2;
	sort(l, mid);
	sort(mid, r);
	int i(l), j(mid), k(l);
	for (; i < mid && j < r; ++k)
		if (a[i] < a[j])
			b[k] = a[i++];
		else
			b[k] = a[j++];
	if (j < r)
	{
		i = j;
		mid = r;
	}
	for (; i < mid; ++i)
		b[k++] = a[i];
	for (i = l; i < r; ++i)
		a[i] = b[i];
}

int main()
{
#ifdef LOCAL
	freopen("input", "r", stdin);
#endif
	while (scanf("%d", &a[n]) == 1)
		++n;
	sort(0, n);
	for (int i = 0; i < n - 1; ++i)
		printf("%d ", a[i]);
	printf("%d\n", a[n - 1]);
	return 0;
}
