/*
ID:theodor8
TASK:concom
LANG:C++
*/
#include <iostream>
using namespace std;
#pragma warning(disable:4996)
#define CASE 2

int com[110][110];
bool done[110][110]
#if CASE==2
[110]
#endif
;
void find(){
	bool again;
#if CASE==1
	for (int i=1; i<=100; ++i){
		again = false;
no:
		for (int j=1; j<=100; ++j)
			if(i!=j && com[i][j]>=50 && !done[i][j]){
				done[i][j] = true;
				for (int k=1; k<=100; ++k)
					if (k!=i && k!=j)
						com[i][k] += com[j][k];
				again = true;
			}
		if (again){
			again = false;
			goto no;
		}
	}
#else if CASE==2
no:
	again = false;
	for (int i=1; i<=100; ++i)
		for (int j=1; j<=100; ++j)
			if (i!=j && com[i][j]>=50)
				for (int k=1; k<=100; ++k){
					if (i!=k && j!=k && !done[i][j][k]){
						done[i][j][k] = true;
						again = true;
						com[i][k] += com[j][k];
					}
				}
	if (again)
		goto no;
#endif
}
int main(){
	freopen("concom.in", "r", stdin);
	freopen("concom.out", "w", stdout);
	int n;
	for (scanf("%d", &n); n; --n){
		int a, b, c;
		scanf("%d%d%d", &a, &b, &c);
		com[a][b] = c;
	}
	find();
	for (int i=1; i<=100; ++i)
		for (int j=1; j<=100; ++j)
			if (i != j && com[i][j] >= 50)
				printf("%d %d\n", i, j);
	return 0;
}
