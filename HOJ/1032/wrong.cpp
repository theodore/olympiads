#include <cstdio>
#include <cassert>
#include <algorithm>

const int maxn = 503;
int n;
int bead[maxn];
int f[maxn][maxn];
int prev[maxn], next[maxn];

void dp()
{
    for (int i = 0, j; i < n; i = next[i])
    {
	for (j = i + 1; j < n && bead[j] == bead[i]; ++j)
	    ;
	next[i] = j;
	for (j = i + 1; j < next[i]; ++j)
	    next[j] = next[i];
    }
    for (int i = n - 1, j; i >= 0; i = prev[i])
    {
	for (j = i - 1; j >= 0 && bead[j] == bead[i]; --j)
	    ;
	prev[i] = j;
	for (j = i - 1; j > prev[i]; --j)
	    prev[j] = prev[i];
    }
#define j (i + l)
    for (int l = 0; l < n; ++l)
	for (int i = 0; j < n; ++i)
	{
	    f[i][j] = -1u >> 1;
	    if (bead[i] != bead[j])
		for (int k = i; k < j; ++k)
		    f[i][j] = std::min(f[i][j], f[i][k] + f[k + 1][j]);
	    else
	    {
		bool same = true;
		for (int k = i + 1; k <= j; ++k)
		    same &= bead[i] == bead[k];
		if (same)
		    f[i][j] = 1 + (l == 0);
		else
		    f[i][j] = f[next[i]][prev[j]] + (next[i] - i + j - prev[j] <= 2);
	    }
	}
#undef j
}

int main()
{
    scanf("%d", &n);
    for (int i = 0; i < n; ++i)
	scanf("%d", bead + i);
    dp();
    printf("%d\n", f[0][n - 1]);
}
