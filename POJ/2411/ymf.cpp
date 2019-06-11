#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>

#define MAXB 2049
#define MAXN 12

using namespace std;

long long f[MAXN][MAXB],res[MAXN][MAXN];
bool can[MAXB][MAXB];
int h,w,Max;

inline bool check(int tmp) {
	bool flag = 1;
	int inc = 0;
	while (tmp)
	{
		if (!(tmp & 1)) 
		{
			if (inc & 1) {flag = 0; break;}
			inc = 0;
		}
		else inc++;
		tmp >>= 1;
	}
	if (inc & 1) flag = 0;
	return flag;
}

void pre() {

	for (int now = 0; now < MAXB - 1; now++)
		for (int last = 0; last < MAXB - 1; last++)
			can[now][last] = check(now & last);
}


int main() {

	pre();
	for (int j = 0; j < MAXB - 1; j++) if (check(j)) f[1][j] = 1;
	while (scanf("%d %d",&h,&w)) 
	{
		if (!h && !w) break;
		if ((h * w) & 1) {printf("0\n"); continue;}
		if (h > w) {int tmp = h; h = w; w = tmp;}
		if (res[h][w]) {printf("%I64d\n",res[h][w]); continue;}
		Max = (1 << w) - 1;

		for (int i = 2; i <= h; i++)
			for (int now = 0; now <= Max; now++)
			{
				bool flag;
				f[i][now] = 0;
				for (int last = 0; last <= Max; last++)
				{
					flag = can[now][last];
					if ((last | now) != ((1 << w) - 1)) flag = 0;
					if (flag) f[i][now] += f[i - 1][last];
				}
			}
		res[h][w] = f[h][Max];
		printf("%I64d\n",res[h][w]);
	}

	return 0;
}


