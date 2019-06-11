/*
ID:theodor8
PROB:checker
LANG:C++
*/
#include <iostream>
#include <ctime>
using namespace std;
#pragma warning(disable:4996)

int n, Ans[13];
bool col[13], plus[25], minus[25];
inline bool poss(const int& x, const int& y){
	return !col[y] && !plus[x+y] && !minus[y-x+n-1];
}
inline void found(){
	//++ans;
	//for (int i=0; i<n; ++i)
	//	cout<<Ans[i];
	//cout<<endl;
}
int search(const int& dep = 0){
	int ans = 0;
	for (int i=0; i<(!dep?n>>1:n); ++i){
		if (poss(dep, i)){
			col[i] = plus[i+dep] = minus[i-dep+n-1] = true;
			Ans[dep] = i;
			if (dep == n-1)
				found(), ++ans;
			else
				ans += search(dep+1);
			col[i] = plus[i+dep] = minus[i-dep+n-1] = false;
		}
	}
	if (!dep){
		ans <<= 1;
		if (n & 1){
			int i = n>>1;
			col[i] = plus[i+dep] = minus[i-dep+n-1] = true;
			Ans[dep] = i;
			ans += search(dep+1);
			col[i] = plus[i+dep] = minus[i-dep+n-1] = false;
		}
	}
	return ans;
}
int main(){
	//freopen("checker.in", "r", stdin);
	//freopen("checker.out", "w", stdout);
	scanf("%d", &n);
	int start = clock();
	int ans = search();
	printf("%d\n", ans);
	printf("Time:\t%lf\n", double(clock()-start)/CLOCKS_PER_SEC);
	return 0;
}
