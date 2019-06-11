#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>

#define MAXM 420001

using namespace std;

bool f[MAXM];
int mark[MAXM][2],A[7],M,Cnt;

int main() {

	while (1)
	{
		M = mark[0][0] = mark[0][1] = 0;
		memset(f,0,sizeof(f));
		f[0] = 1;
		for (int i = 1; i <= 6; i++) {scanf("%d",&A[i]); M += A[i] * i;}
		if (!M) break;
		printf("Collection #%d:\n",++Cnt);
		if (M & 1) printf("Can't be divided.");
		else
		{
			M >>= 1;
			for (int i = 1; i <= 6; i++)
				if (A[i])
				{
				for (int j = i; j <= M; j++)
				{
					int *now = mark[j];
					int *prev = mark[j - i];
					if (!f[j] && f[j - i] && (prev[0] != i || prev[1] < A[i]))
					{
						f[j] = 1;
						now[0] = i;
						now[1] = prev[0] == i ? prev[1] + 1 : 1;
					}
				}
				}
			if (f[M]) printf("Can be divided."); else printf("Can't be divided.");
		}
		printf("\n\n");
	}

	return 0;
}
