#pragma warning(disable: 4996)
#include <cstdio>
#include <cstring>
#define ARR [10][10]

int map ARR;

void input()
{
	for (int i=1; i<=5; ++i)
		for (int j=1; j<=6; ++j)
			scanf("%d", &map[i][j]);
}

int work ARR, ans  ARR;

inline void turn(int x, int y)
{
	work[x][y] ^= 1;
	work[x-1][y] ^= 1;
	work[x+1][y] ^= 1;
	work[x][y-1] ^= 1;
	work[x][y+1] ^= 1;
}

void go()
{
	for (int i=0; i<0x40; ++i) {
		memcpy(work, map, sizeof map);
		memset(ans, 0, sizeof ans);
		for (int j=1, t=i; j<=6; ++j, t>>=1)
			if (ans[1][j] = t & 1)
				turn(1, j);
		for (int j=1; j<=4; ++j)
			for (int k=1; k<=6; ++k)
				if (work[j][k]) {
					ans[j+1][k] = 1;
					turn(j+1, k);
				}
		for (int j=1; j<=6; ++j)
			if (work[5][j])
				goto no;
		break;
no:;
	}
}

void output(int x)
{
	printf("PUZZLE #%d\n", x);
	for (int i=1; i<=5; ++i) {
		for (int j=1; j<=5; ++j)
			printf("%d ", ans[i][j]);
		printf("%d\n", ans[i][6]);
	}
}

int main()
{
	int m;
	scanf("%d", &m);
	for (int _=1; _<=m; ++_) {
		input();
		go();
		output(_);
	}
	return 0;
}
