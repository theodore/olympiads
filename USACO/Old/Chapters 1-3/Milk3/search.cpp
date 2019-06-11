/*
ID:theodor8
PROB:milk3
LANG:C++
*/
#include <iostream>
#pragma warning(disable:4996)
using namespace std;
int a, b, c;
struct Situation{
	int a, b, c;
}	init;
/*
Functions:
0:A->B
1:A->C
2:B->A
3:B->C
4:C->A
5:C->B
*/
bool ans[21];
inline void search(const Situation& basic = init, const int dep = 0){
	if (dep >= 14)
		return;
	if (!basic.a)
		ans[basic.c] = true;
	Situation now;
	for (int fn=0; fn<6; ++fn){
		switch(fn){
case 0:
	if (basic.a && basic.b != b){
		now = basic;
		if (basic.a >= b-basic.b){
			now.a -= b - now.b;
			now.b = b;
		}
		else{
			now.a = 0;
			now.b = basic.a + basic.b;
		}
		search(now, dep+1);
	}
	break;
case 1:
	if (basic.a && basic.c != c){
		now = basic;
		if (basic.a >= c-basic.c){
			now.a -= c - now.c;
			now.c = c;
		}
		else{
			now.a = 0;
			now.c = basic.a + basic.c;
		}
		search(now, dep+1);
	}
	break;
case 2:
	if (basic.b && basic.a != a){
		now = basic;
		if (basic.b >= a-basic.a){
			now.b -= a - now.a;
			now.a = a;
		}
		else{
			now.b = 0;
			now.a = basic.b + basic.a;
		}
		search(now, dep+1);
	}
	break;
case 3:
	if (basic.b && basic.c != c){
		now = basic;
		if (basic.b >= c-basic.c){
			now.b -= c - now.c;
			now.c = c;
		}
		else{
			now.b = 0;
			now.c = basic.b + basic.c;
		}
		search(now, dep+1);
	}
	break;
case 4:
	if (basic.c && basic.a != a){
		now = basic;
		if (basic.c >= a-basic.a){
			now.c -= a - now.a;
			now.a = a;
		}
		else{
			now.c = 0;
			now.a = basic.c + basic.a;
		}
		search(now, dep+1);
	}
	break;
case 5:
	if (basic.c && basic.b != b){
		now = basic;
		if (basic.c >= b-basic.b){
			now.c -= b - now.b;
			now.b = b;
		}
		else{
			now.c = 0;
			now.b = basic.c + basic.b;
		}
		search(now, dep+1);
	}
	break;
		}
	}
}
inline void output(){
	bool first = true;
	for (int i=0; i<=20; ++i)
		if (ans[i])
			if (first)
				printf("%d", i), first = false;
			else
				printf(" %d", i);
	printf("\n");
}
int main(){
	freopen("milk3.in", "r", stdin);
	freopen("milk3.out", "w", stdout);
	scanf("%d%d%d", &a, &b, &c);
	init.a = 0;
	init.b = 0;
	init.c = c;
	search();
	output();
	return 0;
}
