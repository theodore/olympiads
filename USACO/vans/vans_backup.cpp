/*
PROB:vans
LANG:C++
*/
#include <cstdio>
#include <cassert>

/*
int ans[1000][4];

int main()
{
	freopen("vans.in", "r", stdin);
	freopen("vans.out", "w", stdout);
	int n;
	scanf("%d", &n);
	if (n == 1)
	{
		printf("0\n");
		return 0;
	}
	ans[0][0] = ans[0][2] = 1;
	for (int i = 1; i < n - 1; ++i)
	{
		ans[i][1] = ans[i-1][0] + ans[i-1][1];
		ans[i][0] = ans[i-1][1] + ans[i][1];
		ans[i][2] = ans[i][0] + ans[i-1][3];
		ans[i][3] = ans[i-1][2];
	}
	printf("%d\n", 2 * (ans[n-2][2] + ans[n-2][1]));
#ifdef DB
	for (int i = 0; i < n - 1; ++i)
		for (int j = 0; j < 4; ++j)
			printf("ans[%d][%d] = %d\n", i, j, ans[i][j]);
#endif
	return 0;
}
*/

long long int ans[1000][7];
char trans[][3] = {"4u", "4d", "4s", "2u", "2d", "2s", "2m"};

int main()
{
	freopen("vans.in", "r", stdin);
	freopen("vans.out", "w", stdout);
	int n;
	scanf("%d", &n);
	if (n == 1)
	{
		printf("0\n");
		return 0;
	}
#define fu 0
#define fd 1
#define fs 2
#define tu 3
#define td 4
#define ts 5
#define tm 6
	ans[0][tu] = 1;
	//ans[1][fu] = ans[1][fd] = ans[1][ts] = 1;
	for (int i = 1; i < n; ++i)
	{
		ans[i][fu] = ans[i-1][fu] + ans[i-1][tu];
		ans[i][fd] = ans[i-1][fd] + ans[i-1][td];
		ans[i][fs] = ans[i-1][fs] + ans[i-1][ts];
		ans[i][tu] = ans[i-1][fs] + ans[i-1][ts];
		ans[i][td] = ans[i-1][fs] + ans[i-1][ts];
		ans[i][ts] = ans[i-1][fu] + ans[i-1][fd] + ans[i-1][tu] + ans[i-1][td] + ans[i-1][tm];
		ans[i][tm] = ans[i-1][ts];
#undef fu
#undef fd
#undef fs
#undef tu
#undef td
#undef ts
#undef tm
	}
	printf("%lld\n", 2 * (ans[n-1][2] + ans[n-1][5]));
#ifdef DB
	for (int i = 1; i < n; ++i)
	{
		for (int j = 0; j < 7; ++j)
			printf("ans[%d][%s] = %d\n", i, trans[j], ans[i][j]);
		putchar('\n');
	}
#endif 
	return 0;
}
