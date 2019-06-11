#include <cstdio>
#include <cstdlib>

#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))

const int maxn(103);
const int maxk(103);
const int maxt(30003);

int n, k, t;
// time, value, stoutness
int gang[maxn][3];
int ans[maxk];

int cmp(const void* a, const void* b)
{
	if (*(int*)a != *(int*)b)
		return *(int*)a - *(int*)b;
	else if (((int*)a)[2] != ((int*)b)[2])
		return ((int*)b)[2] - ((int*)a)[2];
	else
		return ((int*)b)[1] - ((int*)a)[1];
}

int main()
{
	scanf("%d%d%d", &n, &k, &t);
	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < n; ++j)
			scanf("%d", &gang[j][i]);
	qsort(gang, n, sizeof gang[0], cmp);
	int p = 0;
	while (gang[p][0] == 0)
		++p;
#ifdef DB
	printf("%d\n", p);
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < 3; ++j)
			printf("%d ",gang[i][j]);
		putchar('\n');
	}
#endif
	for (int i = 1, pre = 0; i <= t; ++i, pre = 0)
	{
		while (gang[p][0] == i && gang[p][2] > min(i, k))
			++p;
		for (int j = min(k, i), tmp; j >= 0; --j, pre = tmp)
		{
			tmp = ans[j];
			if (j > 0 && ans[j-1] > ans[j])
				ans[j] = ans[j-1];
			if (pre > ans[j])
				ans[j] = pre;
			while (gang[p][0] == i && gang[p][2] == j)
				ans[j] += gang[p++][1];
#ifdef DB
			printf("%d, %d, %d\n", i, j, ans[j]);
#endif
		}
	}
	int out(0);
	for (int i = 0; i <= k; ++i)
		if (ans[i] > out)
			out = ans[i];
	printf("%d\n", out);
	return 0;
}
