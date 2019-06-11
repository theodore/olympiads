/*
ID:theodor8
LANG:C++
PROB:comehome
*/
#include <iostream>
#include <queue>
using namespace std;
#pragma warning(disable:4996)
//#define Debug

int n;
bool used[70];
int dis[70][70];
int main(){
	freopen("comehome.in", "r", stdin);
	freopen("comehome.out" ,"w", stdout);
	scanf("%d\n", &n);
	for (int i=0; i<n; ++i){
		char a, b;
		int c;
		scanf("%c %c %d\n", &a, &b, &c);
		a -= 60;
		b -= 60;
		used[a] = used[b] = true;
		if (!dis[a][b] || dis[a][b]>c)
			dis[a][b] = dis[b][a] = c;
	}
	//floyd
	for (int k=5; k<=62; ++k)
		if (used[k])
			for (int i=5; i<=62; ++i)
				if (used[i] && dis[i][k])
					for (int j=5; j<=62; ++j)
						if (used[j] && i!=j && dis[j][k] && (!dis[i][j] || dis[i][k]+dis[k][j]<dis[i][j]))
							dis[i][j] = dis[i][k]+dis[k][j];
#ifdef Debug
	for (char i='A'; i<='z'; ++i)
		for (char j='A'; j<='z'; ++j)
			if (used[i-60] && used[j-60] && i!=j)
				printf("%c, %c\t%d\n", i, j, dis[i-60][j-60]);
#else
	int ans(0);
	for (int i=5; i<30; ++i)
		if (used[i] && (!ans || dis['Z'-60][i]<dis['Z'-60][ans]))
			ans = i;
	printf("%c %d\n", ans+60, dis['Z'-60][ans]);
#endif
	return 0;
}
