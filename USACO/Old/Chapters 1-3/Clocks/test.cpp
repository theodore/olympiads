#include <iostream>
using namespace std;

void test(){
	freopen("output.txt", "w", stdout);
	printf("inline void search(){\n");
	for (int i=0; i<9; ++i){
		for (int j=0; j<=i; ++j)
			printf("\t");
		printf("for (n[%d]=0; n[%d]<4; ++n[%d])\n", i, i, i);
	}
}