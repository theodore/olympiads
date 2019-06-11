/*
PROB: milk4
LANG: C++
*/
#pragma warning(disable: 4996)
#include <iostream>
#include <cstring>
//#define Debug
//#define Fix

using namespace std;

int n, m, pail[103];

int cmp(const void* a, const void* b){
	return *(int*)a - *(int*)b;
}

struct A{
	int num;
	bool get, used[103];
	bool operator<(const A&);
} ans[20010];

bool A::operator<(const A& r){
	for (int i=0; i<m; ++i)
		if (used[i] && !r.used[i])
			return true;
		else if (r.used[i] && !used[i])
			return false;
	return false;
}

int main(){
	freopen("milk4.in", "r", stdin);
	freopen("milk4.out", "w", stdout);
	scanf("%d%d", &n, &m);
	for (int i=0; i<m; ++i)
		scanf("%d", pail+i);
	qsort(pail, m, 4, cmp);
	for (int i=0; i<=n; ++i)
		for (int j=0; j<m && pail[j]<=i; ++j){
			if (!ans[i-pail[j]].get && pail[j]!=i)
				continue;
			//ans[i].get = true;
#ifndef Fix
			A s = ans[i-pail[j]];
			s.get = true;
#else
			A s;
			for (int k=1; k*pail[j]<=i; ++k){
				if (!ans[i-pail[j]*k].get && pail[j]*k!=i)
					break;
				s = ans[i-pail[j]*k];
				s.get = true;
#endif
				if (!s.used[j]){
					++s.num;
					s.used[j] = true;
				}
				if (!ans[i].get || s.num<ans[i].num || (s.num==ans[i].num && s<ans[i]))
					ans[i] = s;
#ifdef Fix
			}
#endif
		}
#ifndef Debug
	printf("%d", ans[n].num);
	for (int i=0; i<m; ++i)
		if (ans[n].used[i])
			printf(" %d", pail[i]);
	printf("\n");
#else
	for (int i=1; i<=n; ++i){
		printf("%d", ans[i].num);
		for (int j=0; j<m; ++j)
			if (ans[i].used[j])
				printf(" %d", pail[j]);
		printf("\n");
	}
#endif
	return 0;
}
