/*
ID:theodor8
TASK:sprime
LANG:C++
*/
#include <iostream>
using namespace std;
#pragma warning(disable:4996)
//#define Debug

int n, ans[8];
inline bool is_prime(const int& x){
	if (x == 1)
		return false;
	if (x == 2)
		return true;
	if (!(x&1))
		return false;
	for (int i=3; i*i<=x; i+=2)
		if (x % i == 0)
			return false;
	return true;
}
inline bool fit(const int& dep){
	int t=0;
	for (int i=0; i<=dep; ++i)
		t = t*10 + ans[i];
	return is_prime(t);
}
inline void output(){
	for (int i=0; i<n; ++i)
		printf("%d", ans[i]);
	printf("\n");
}
void search(const int& dep = 0){
	for (int i=1; i<=9; ++i){
		ans[dep] = i;
		if (fit(dep)){
			if (dep == n-1)
				output();
			else
				search(dep+1);
		}
	}
}
#ifndef Debug
int main(){
	freopen("sprime.in", "r", stdin);
	freopen("sprime.out", "w", stdout);
	scanf("%d", &n);
	search();
	return 0;
}
#else
int main(){
	for (int i=1;i<10;++i)
		cout<<i<<'\t'<<is_prime(i)<<endl;
}
#endif