/*
PROB:butter
LANG:C++
*/
#include <iostream>
//#include <ctime>
#pragma warning(disable:4996)
//#define Debug
//#define Cow

using namespace std;

int n, c, p, cow[510], graph[810][810];
int main(){
	freopen("butter.in", "r", stdin);
	freopen("butter.out", "w", stdout);
	scanf("%d%d%d", &n, &p, &c);
	for (int i=1; i<=n; ++i)
		scanf("%d", cow+i);
	for (int i=0; i<c; ++i){
		int a, b, c;
		scanf("%d%d%d", &a, &b, &c);
		graph[a][b] = graph[b][a] = c;
	}
	for (int k=1; k<=p; ++k)
		for (int i=1; i<=p; ++i)
			if (graph[i][k] && i!=k)
				for (int j=1; j<i; ++j)
					if (graph[k][j] && (!graph[i][j] || graph[i][j]>graph[i][k]+graph[k][j]))
#ifdef Debug
					{
						printf("graph[%d][%d], %d -> %d + %d\n", i, j, graph[i][j], graph[i][k], graph[k][j]);
#endif
						graph[i][j] = graph[j][i] = graph[i][k] + graph[k][j];
#ifdef Debug
					}
#endif
	int ans = 1<<30;
#ifdef Cow
	for (int s=1; s<=n; ++s){
		int path = 0;
		for (int i=1; i<=n; ++i)
			if ((path += graph[cow[i]][cow[s]]) >= ans)
				goto next;
		ans = path;
next:;
	}
#else
	for (int s=1; s<=p; ++s){
		int path = 0;
		for (int i=1; i<=n; ++i)
			if ((path += graph[cow[i]][s]) >= ans)
				goto next;
		if (path < ans)
			ans = path;
next:;
	}
#endif
	printf("%d\n", ans);
#ifdef Debug
	for (int i=1; i<=p; ++i){
		for (int j=1; j<=p; ++j)
			printf("%d ", graph[i][j]);
		printf("\n");
	}
#endif
	//printf("%f\n", clock()/double(CLOCKS_PER_SEC));
	return 0;
}
