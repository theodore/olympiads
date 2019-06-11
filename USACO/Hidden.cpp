/*
PROB:hidden
LANG:C++
*/
#pragma warning(disable: 4996)
#include <cstdio>
#include <cstring>

int n;
char str[100001] = "";

bool better(int now, int best)
{
	int i(now), j(best), c(0);
#define inc(x) (x==n-1 ? 0 : x+1)
	for (; str[i]==str[j] && c<n; i=inc(i), j=inc(j), ++c)
		;
#undef inc
	return c != n && str[i] < str[j];
}

int main()
{
	freopen("hidden.in", "r", stdin);
	freopen("hidden.out", "w", stdout);
	scanf("%d", &n);
	for (int i=0; i<=(n-1)/72; ++i)
		scanf("%s", str + strlen(str));
	int ans(0);
	for (unsigned i=1; i<strlen(str); ++i)
		if (better(i, ans))
			ans = i;
	printf("%d\n", ans);
	return 0;
}
