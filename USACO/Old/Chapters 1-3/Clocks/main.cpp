/*
ID:theodo8
LANG:C++
PROB:clocks
*/
#include <iostream>
//#pragma warning(disable:4996)
//#define Debug
using namespace std;

int clocks[9];
int ans[9], ans_num = 999999, n[9];
inline void init(){
	//get original clocks
	for (int i=0; i<9; ++i){
		scanf("%d", &clocks[i]);
		clocks[i] = (12 - clocks[i]) / 3;
	}
}
inline void search(){
	for (n[0]=0; n[0]<4; ++n[0])
		for (n[1]=0; n[1]<4; ++n[1])
			for (n[2]=0; n[2]<4; ++n[2])
				for (n[3]=0; n[3]<4; ++n[3])
					for (n[4]=0; n[4]<4; ++n[4])
						for (n[5]=0; n[5]<4; ++n[5])
							for (n[6]=0; n[6]<4; ++n[6])
								for (n[7]=0; n[7]<4; ++n[7])
									for (n[8]=0; n[8]<4; ++n[8]){
										if (n[0]+n[1]+n[2]+n[3]+n[4]+n[5]+n[6]+n[7]+n[8] < ans_num &&
											(n[0]+n[1]+n[3])%4 == clocks[0] &&
											(n[0]+n[1]+n[2]+n[4])%4 == clocks[1] &&
											(n[1]+n[2]+n[5])%4 == clocks[2] &&
											(n[0]+n[3]+n[4]+n[6])%4 == clocks[3] &&
											(n[0]+n[2]+n[4]+n[6]+n[8])%4 == clocks[4] &&
											(n[2]+n[4]+n[5]+n[8])%4 == clocks[5] &&
											(n[3]+n[6]+n[7])%4 == clocks[6] &&
											(n[4]+n[6]+n[7]+n[8])%4 == clocks[7] &&
											(n[5]+n[7]+n[8])%4 == clocks[8]){
												//record the ans
												for (int i=0; i<9; ++i)
													ans[i] = n[i];
												ans_num = n[0]+n[1]+n[2]+n[3]+n[4]+n[5]+n[6]+n[7]+n[8];
										}
									}
}
inline void output(){
	int i=0;
	for (int j=0; j<9; ++j){
		for (int k=0; k<ans[j]; ++k){
			printf("%d", j+1);
			if (++i < ans_num)
				printf(" ");
		}
	}
	printf("\n");
}
int main(){
	freopen("clocks.in", "r", stdin);
	freopen("clocks.out", "w", stdout);
	init();
	search();
	output();
	return 0;
}
