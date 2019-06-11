#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#define MAXP 5000
#define INF 0x7fffffff/2
using namespace std;
int T,MaxP,w;
int ap[MAXP] , bp[MAXP] , as[MAXP] , bs[MAXP] ;
int f[MAXP][MAXP] , g[MAXP] , q[MAXP]; 
int main()
{
	int ans = 0 ;
	scanf("%d%d%d",&T,&MaxP,&w);
	for (int i = 1 ; i <= T ; i++)
		scanf("%d%d%d%d",&ap[i],&bp[i],&as[i],&bs[i]);
	for (int i = 0 ; i <= T ; i++){ 
		for (int j = 0 ; j <= MaxP ; j++)
			f[i][j] = -INF ;
	}
	f[0][0] = 0 ;
	for (int i = 1 ; i <= T + w + 1; i++)
	{
		for (int j = 0 ; j <= MaxP ; j++)
			f[i][j] = max(f[i-1][j],f[i][j]);
		int k = i - w - 1 ;
		if (k >= 1) 
		{
			int l = 1 , r = 0 ;
			for (int j = 1 ; j <= MaxP ; j++)
			{
				g[j - 1] = f[k][j - 1] + ( j - 1 ) * ap[k] ; 
				while ( r >= l && g[j - 1] >= g[q[r]]) r--;
				q[++r] = j - 1 ;
				if ( j - q[l] > as[k]) ++l;
				f[i][j] = max(f[i][j] , g[q[l]] - j * ap[k]);
			}
			l = 1 ; r = 0 ; 
			for (int j = MaxP - 1 ; j >= 0 ; j--)
			{
				g[j + 1] = f[k][j + 1] + ( j + 1 ) * bp[k] ; 
				while ( r >= l && g[j + 1] >= g[q[r]]) r--;
				q[++r] = j + 1 ;
				if ( q[l] - j > bs[k]) ++l;
				f[i][j] = max(f[i][j] , g[q[l]] - j * bp[k]);
			}
		}
	}
	cout << f[T+w+1][0] << endl;
	return 0 ;
}
