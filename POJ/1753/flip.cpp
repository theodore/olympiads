/** @file flip.cpp
 *  @version 1.0
 *  @date Fri Aug 20, 4:47:15 PM, 2010 +0800
 *  @author Theodore You
 *  This is my implementation for POJ Problem #1753, Flip Game.
 */
#include <cstdio>
#include <cassert>
#include <cstring>
#include <algorithm>

using std::min;

int board[6][6];

void input()
{
	char t[10];
	for (int i = 1; i < 5; ++i)
	{
		scanf("%s", t);
		for (int j = 1; j < 5; ++j)
			board[i][j] = t[j-1] == 'w';
	}
}

int work[6][6];

void turn(int x, int y)
{
	work[x][y]		^= 1;
	work[x-1][y]	^= 1;
	work[x+1][y]	^= 1;
	work[x][y-1]	^= 1;
	work[x][y+1]	^= 1;
}

int answer()
{
	int ans[6][6], r(100);
	for (int i = 0; i <= 0xf; ++i)
	{
#ifdef DB
		printf("i = %d\n", i);
#endif
		memcpy(work, board, sizeof(board));
		memset(ans, 0, sizeof(ans));
		for (int j = 0; j < 4; ++j)
		{
			if ((ans[1][j+1] = (i & (1 << j) ? 1 : 0)))
				turn(1, j+1);
		}
		for (int j = 2; j < 5; ++j)
			for (int k = 1; k < 5; ++k)
				if (work[j-1][k])
				{
#ifdef DB
					printf("j, k = %d, %d\n", j, k);
#endif
					assert(ans[j][k] == 0);
					ans[j][k] = 1;
					turn(j, k);
				}
		int c(0);
		for (int j = 1; j < 5; ++j)
			if (work[4][j])
			{
				c = 100;
				break;
			}
		if (c == 100)
			continue;
		for (int j = 1; j < 5; ++j)
			for (int k = 1; k < 5; ++k)
				c += ans[j][k];
		r = min(r, c);
	}
	return r;
}

int main()
{
	input();
	int ans(100);
	int t = answer();
	ans = min(ans, t);
	for (int i = 1; i < 5; ++i)
		for (int j = 1; j < 5; ++j)
			board[i][j] ^= 1;
	t = answer();
	ans = min(ans, t);
	if (ans == 100)
		printf("Impossible\n");
	else
		printf("%d\n", ans);
	return 0;
}
