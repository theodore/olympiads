#include <cstdio>

#define max(a, b) ((a) > (b) ? (a) : (b))

const int maxn(150003);
int n;
int p[maxn];
int ans[maxn][2];

int main()
{
	scanf("%d", &n);
	for (int i = 0; i < n; ++i)
		scanf("%d", &p[i]);
	int best0(-9999999), best1;
	best1 = ans[0][1] = p[0];
	/*
	if (p[0] > out)
		out = p[0];
	*/
	for (int i = 1; i < n; ++i)
	{
		ans[i][0] = best1 - p[i];
		ans[i][1] = max(best0, 0) + p[i];
		if (ans[i][0] > best0)
			best0 = ans[i][0];
		if (ans[i][1] > best1)
			best1 = ans[i][1];
	}
	printf("%d\n", max(best1, best0));
	return 0;
}
