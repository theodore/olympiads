/*
USER:theodor8
LANG:C++
TASK:zerosum
*/
#include <iostream>
using namespace std;
#pragma warning(disable:4996)
//#define Debug

int n;
int ans[8];	//1 for plus, -1 for minus, 0 for blank
inline void judge(){
	int t(1), s(0);
	for (int i=2; i<=n; ++i){
		if (ans[i-2]){
			s += t, t = ans[i-2] * i;
#ifdef Debug
			printf("S=%d\tT=%d\n", s, t);
#endif
		}
		else{
#ifdef Debug
			printf("S=%d\tT=%d\n", s, t);
#endif
			t *= 10;
			if (t >= 0)
				t += i;
			else
				t -= i;
		}
	}
	s += t;
	if (!s){
		for (int i=1; i<n; ++i){
			printf("%d", i);
			switch (ans[i-1]){
			case 1:
				printf("+");
				break;
			case 0:
				printf(" ");
				break;
			case -1:
				printf("-");
			}
		}
		printf("%d\n", n);
	}
}
void search(const int& dep=0){
#ifdef Debug
	for (int i=0; i<n-1; ++i)
		scanf("%d", &ans[i]);
	judge();
#else
	int i(0);
		ans[dep] = i;
		if (dep == n-2)
			judge();
		else
			search(dep+1);
	i = 1;
		ans[dep] = i;
		if (dep == n-2)
			judge();
		else
			search(dep+1);
	i = -1;
		ans[dep] = i;
		if (dep == n-2)
			judge();
		else
			search(dep+1);
	//for (int i=0; i<=5; ++i)
	//	scanf("%d", &ans[i]);
	//judge();
#endif
}
int main(){
	freopen("zerosum.in", "r", stdin);
	freopen("zerosum.out", "w", stdout);
	scanf("%d", &n);
	search();
	return 0;
}
