/*
PROB:shopping
LANG:C++
*/
#include <iostream>
//#define Test
#define Solve
//#define Debug
//#define Well
//#define Pae printf("pay[%d][%d][%d][%d][%d] = %d\n", a, b, c, d, e, pay[a][b][c][d][e]);

using namespace std;

struct special{
	static int num;
	int code[5], count[5], price;
} offer[100];
int special::num = 0;

struct deal{
	static int num;
	int code, count, price;
} item[5];
int deal::num = 0;

void init(){
	freopen("shopping.in", "r", stdin);
	freopen("shopping.out", "w", stdout);
	scanf("%d", &special::num);
	for (int i=0; i<special::num; ++i){
		int _;
		scanf("%d", &_);
		for (int j=0; j<_; ++j)
			scanf("%d%d", &offer[i].code[j], &offer[i].count[j]);
		scanf("%d", &offer[i].price);
	}
	scanf("%d", &deal::num);
	for (int i=0; i<deal::num; ++i)
		scanf("%d%d%d", &item[i].code, &item[i].count, &item[i].price);
	//////////////input above
	int map[5];
	for (int i=0; i<5; ++i)
		map[i] = item[i].code;
	special foo;
	for (int i=0; i<special::num; ++i){
		//code, count
		for (int j=0; j<5; ++j){
			int seek = -1;
			if (map[j])
				for (int k=0; k<5; ++k)
					if (map[j] == offer[i].code[k]){
						seek = k;
						break;
					}
			if (seek == -1)
				foo.code[j] = foo.count[j] = 0;
			else{
				foo.code[j] = offer[i].code[seek];
				foo.count[j] = offer[i].count[seek];
			}
		}
		foo.price = offer[i].price;
		offer[i] = foo;
	}
}

#ifdef Test
void test(){
	printf("%d\n", offer[0].num);
	for (int i=0; i<offer[0].num; ++i){
		for (int j=0; j<5; ++j)
			printf("%d %d ", offer[i].code[j], offer[i].count[j]);
		printf("%d\n", offer[i].price);
	}
	printf("************************\n");
	printf("%d\n", deal::num);
	for (int i=0; i<deal::num; ++i)
		printf("%d %d %d\n", item[i].code, item[i].count, item[i].price);
}
#endif

int pay[6][6][6][6][6];
void solve(){
	for (int a=0; a<=item[0].count; ++a)
		for (int b=0; b<=item[1].count; ++b)
			for (int c=0; c<=item[2].count; ++c)
				for (int d=0; d<=item[3].count; ++d)
					for (int e=0; e<=item[4].count; ++e)/*
					{
						bool changed = false;
						int & ans = pay[a][b][c][d][e] = a*item[0].price + b*item[1].price + c*item[2].price + d*item[3].price + e*item[4].price;
						#ifdef Well
						Pae
						#endif
						ans = min(ans,
								pay[a][b][c][d][e?e-1:e] + e ? changed=true, item[4].price : 0);
						#ifdef Well
						Pae
						#endif
						ans = min(ans,
								pay[a][b][c][d?d-1:d][e] + d ? changed=true, item[3].price : 0);
						#ifdef Well
						Pae
						#endif
						ans = min(ans,
								pay[a][b][c?c-1:c][d][e] + c ? changed=true, item[2].price : 0);
						#ifdef Well
						Pae
						#endif
						ans = min(ans,
								pay[a][b?b-1:b][c][d][e] + b ? changed=true, item[1].price : 0);
						#ifdef Well
						Pae
						#endif
						ans = min(ans,
								pay[a?a-1:a][b][c][d][e] + a ? changed=true, item[0].price : 0);
						#ifdef Well
						Pae
						#endif
//						if (!changed)
//							ans = a*item[0].price + b*item[1].price + c*item[2].price + d*item[3].price + e*item[4].price;
						for (int i=0; i<special::num; ++i){
							bool good = true; // = offer[i] fits
							if (a < offer[i].count[0])
								good = false;
							if (b < offer[i].count[1])
								good = false;
							if (c < offer[i].count[2])
								good = false;
							if (e < offer[i].count[3])
								good = false;
							if (e < offer[i].count[4])
								good = false;
#ifdef Well
good = false;
#endif

							if (good){
//							#ifdef Debug
//								int ans1 = ans,
//									ans2 = pay[a-offer[i].count[0]][b-offer[i].count[1]][c-offer[i].count[2]][d-offer[i].count[3]][e-offer[i].count[4]] + offer[i].price;
//								printf("%d %d %d %d %d\n\tAns1: %d\tAns2: %d\n", a, b, c, d, e, ans1, ans2);
//								ans = min(ans1, ans2);
//							#else
								ans = min(ans,
										pay[a-offer[i].count[0]][b-offer[i].count[1]][c-offer[i].count[2]][d-offer[i].count[3]][e-offer[i].count[4]] + offer[i].price);
//							#endif
							}
						}
					}
*/
					{
						int & ans = pay[a][b][c][d][e];
						ans = a*item[0].price + b*item[1].price + c*item[2].price + d*item[3].price + e*item[4].price;
						//Pae
						//calc the best without using a special
//						if (a)
//							ans = min(ans,
//								pay[a-1][b][c][d][e] + item[0].price);
//						//Pae
//						if (b)
//							ans = min(ans,
//								pay[a][b-1][c][d][e] + item[1].price);
//						//Pae
//						if (c)
//							ans = min(ans,
//								pay[a][b][c-1][d][e] + item[2].price);
//						//Pae
//						if (d)
//							ans = min(ans,
//								pay[a][b][c][d-1][e] + item[3].price);
//						//Pae
//						if (e)
//							ans = min(ans,
//								pay[a][b][c][d][e-1] + item[4].price);
						//Pae

						//determine whether to use a special
						for (int i=0; i<special::num; ++i){
							bool good = true;
							if (a < offer[i].count[0]){
//								printf("%d false, a ", i);
								good = false;
							}
							if (b < offer[i].count[1]){
//								printf("%d false, b ", i);
								good = false;
							}
							if (c < offer[i].count[2]){
//								printf("%d false, c ", i);
								good = false;
							}
							if (d < offer[i].count[3]){
//								printf("%d false, d ", i);
								good = false;
							}
							if (e < offer[i].count[4]){
//								printf("%d false, e ", i);
								good = false;
							}
//							printf("\n");
							if (good){
//								printf("%d is good\n", i);
								ans = min(ans, pay[a-offer[i].count[0]][b-offer[i].count[1]][c-offer[i].count[2]][d-offer[i].count[3]][e-offer[i].count[4]] + offer[i].price);
							}
						}
						//Pae
//						printf("\n");

					}
}

int main(){
	init();
 #ifdef Test
	test();
 #endif
 #ifdef Solve
	solve();
	printf("%d\n", pay[item[0].count][item[1].count][item[2].count][item[3].count][item[4].count]);
 #endif
 #ifdef Well
	printf("****************\n");
	for (int a=0; a<=item[0].count; ++a)
		for (int b=0; b<=item[1].count; ++b)
			for (int c=0; c<=item[2].count; ++c)
				for (int d=0; d<=item[3].count; ++d)
					for (int e=0; e<=item[4].count; ++e)
						printf("pay[%d][%d][%d][%d][%d] = %d\n", a, b, c, d, e, pay[a][b][c][d][e]);
 #endif
	return 0;
}
