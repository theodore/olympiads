/*
PROB:shopping
LANG:C++
*/
#include <iostream>
#include <algorithm>
#define Test
//#define TEST

using namespace std;
#ifndef TEST
struct nothing{
	int a, b;
};

struct foo {
	static int num;
	int n, code[5], count[5];
} offer[105];

struct bar {
	static int num;
	int code, count, price;
} item[5];

int foo::num = 0;
int bar::num = 0;

bool nthcmp(const nothing& a, const nothing& b){
	return a.a > b.a;
}
bool barcmp(const bar& a, const bar& b){
	return a.code > b.code;
}

#ifndef Test
int pay[6][6][6][6][6];

void solve(){
	for (int a=0; a<=item[0].num; ++a)
		for (int b=0; b<=item[1].num; ++b)
			for (int c=0; c<=item[2].num; ++c)
				for (int d=0; d<=item[3].num; ++d)
					for (int e=0; e<=item[4].num; ++e){
						int& ans = pay[a][b][c][d][e] = a*item[0].price + b*item[1].price + c*item[2].price + d*item[3].price + e*item[4].price;
						for (int i=0; i<foo::num; ++i){
							int good = true;
							/*good = offer[i] is possible*/
							if (good){
								ans = min(ans, pay[a-offer[i]
							}
						}
					}
}
#endif

void input(){
	scanf("%d", &foo::num);
 #ifdef Test
	printf("Foo: %d\n", foo::num);
 #endif
	for (int i=0; i<foo::num; ++i){
		scanf("%d", &offer[i].n);
		nothing a[5];
		for (int j=0; j<offer[i].n; ++j)
			scanf("%d%d", &a[i].a, &a[i].b);
		sort(a, a+offer[i].n, nthcmp);
		for (int j=0; j<offer[i].n; ++j){
			offer[j].code[j] = a[j].a;
			offer[j].count[j] = a[j].b;
		}
	}
	scanf("%d", &bar::num);
 #ifdef Test
	printf("Bar: %d\n", bar::num);
 #endif
	for (int i=0; i<bar::num; ++i)
		scanf("%d%d%d", &item[i].code, &item[i].count, &item[i].price);
	sort(item, item+bar::num, barcmp);
}

#ifdef Test
void test(){
	printf("%d\n", foo::num);
	for (int i=0; i<foo::num; ++i){
		printf("%d ", offer[i].n);
		for (int j=0; j<offer[i].n; ++j)
			printf("%d %d ", offer[i].code[j], offer[i].count[j]);
		printf("\n");
	}
	printf("**************\n");
	printf("%d\n", bar::num);
	for (int i=0; i<bar::num; ++i){
		printf("%d %d %d\n", item[i].code, item[i].count, item[i].price);
	}
}
#endif

int main(){
//	freopen("shopping.in", "r", stdin);
//	freopen("shopping.out", "w", stdout);
	input();
 #ifdef Test
	test();
 #else
	solve();
	printf("%d\n", pay[item[0].num][item[1].num][item[2].num][item[3].num][item[4].num]);
 #endif
	return 0;
}
#else
struct X{
	static int s;
	int n;
	 X(int);
	int value();
} a(5), b(7);

X::X(int a){
	n = a;
}
int X::value(){
	return n;
}
//int X::s = 0;

int main(){
	a.s = 4;
	b.s = 40;
	cout << a.s << endl;
	cout << b.s << endl;
	scanf("%d", &X::s);
	cout << a.s << endl;
	return 0;
}
#endif
