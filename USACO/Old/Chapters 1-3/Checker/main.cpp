/*
ID:theodor8
PROB:checker
LANG:C++
*/
#include <iostream>
using namespace std;
#pragma warning(disable:4996)

int n;
bool col[13], plus_alright[25], minus_alright[25];//minus_alright = horizontal - vertical + n-1
inline bool poss(const int& x, const int& y){
	return !col[y] && !plus_alright[x+y] && !minus_alright[y-x+n-1];
}
int even(const int& dep = 0){
	int ans = 0;
	for (int i=0; i<(!dep?n>>1:n); ++i){
		if (poss(dep, i)){
			col[i] = plus_alright[i+dep] = minus_alright[i-dep+n-1] = true;
			if (dep == n-1)
				++ans;
			else
				ans += even(dep+1);
			col[i] = plus_alright[i+dep] = minus_alright[i-dep+n-1] = false;
		}
	}
	if (!dep)
		ans <<= 1;
	return ans;
}
int line;
//consider special cases
int odd(const int& dep = -1){
	int ans(0);
	if (dep == -1){
		for (int i=0; i<(n>>1); ++i)	//vertical
			for (int j=0; j<i; ++j){		//horizontal
				col[n>>1] = plus_alright[(n>>1)+i] = minus_alright[(n>>1)-i+n-1] = true;
				col[j] = plus_alright[j+(n>>1)] = minus_alright[j-(n>>1)+n-1] = true;
				line = i;
				ans += odd(0);
				col[n>>1] = plus_alright[(n>>1)+i] = minus_alright[(n>>1)-i+n-1] = false;
				col[j] = plus_alright[j+(n>>1)] = minus_alright[j-(n>>1)+n-1] = false;
			}
		ans <<= 3;
		//put it at the center
		col[n>>1] = plus_alright[n-1] = minus_alright[n-1] = true;
		line = n>>1;
		ans += odd(0);
		col[n>>1] = plus_alright[n-1] = minus_alright[n-1] = false;
	}
	else{
		if (dep == line || dep == (n>>1))
			ans += odd(dep+1);
		else{
			//the same as even but... i<n!
			for (int i=0; i<n; ++i){
				if (poss(dep, i)){
					col[i] = plus_alright[i+dep] = minus_alright[i-dep+n-1] = true;
					if (dep == n-1)
						++ans;
					else
						ans += odd(dep+1);
					col[i] = plus_alright[i+dep] = minus_alright[i-dep+n-1] = false;
				}
			}
		}
	}
	return ans;
}
int num(0), Ans[13];
bool done(false);
void inline search(const int& dep = 0){
	for (int i=0; i<n; ++i){
		if (poss(dep, i)){
			col[i] = plus_alright[i+dep] = minus_alright[i-dep+n-1] = true;
			Ans[dep] = i+1;
			if (dep == n-1){
				//output
				printf("%d", Ans[0]);
				for (int x=1; x<n; ++x)
					printf(" %d", Ans[x]);
				printf("\n");
				if (++num == 3)
					done = true;
			}
			else
				search(dep+1);
			col[i] = plus_alright[i+dep] = minus_alright[i-dep+n-1] = false;
		}
		if (done)
			break;
	}
}
int main(){
	freopen("checker.in", "r", stdin);
	freopen("checker.out", "w", stdout);
	scanf("%d", &n);
	search();
	int ans;
	if (n&1)
		ans = odd();
	else
		ans = even();
	printf("%d\n", ans);
	return 0;
}
	