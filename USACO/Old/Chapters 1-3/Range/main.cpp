/*
PROB:range
LANG:C++
*/
#include <iostream>

using namespace std;

int n;
int range[250][250];
char str[255];
int ans[255];

void debug(){
	for (int i=0; i<6; ++i){
		for (int j=0; j<6; ++j)
			printf("%d", range[i][j]);
		printf("\n");
	}
}

int main(){
	freopen("range.in", "r", stdin);
	freopen("range.out", "w", stdout);
	scanf("%d", &n);
	for (int i=0; i<n; ++i){
		scanf("%s", str);
		for (int j=0; j<n; ++j)
			range[i][j] = str[j]=='1' ? 1 : 0;
	}

//	for (int i=0; i<n; ++i)
//		for (int j=0; j<n; ++j)
//			for (int k=2; k<=min(i, j)+1; ++k)
//				range[i][j][k] = range[i][j][1] && range[i-1][j-1][k-1] && range[i-1][j][k-1] && range[i][j-1][k-1];

	for (int i=1; i<n; ++i)
		for (int j=1; j<n; ++j){
			if (range[i][j]){
				range[i][j] = min(range[i-1][j], range[i-1][j-1]);
				range[i][j] = min(range[i][j], range[i][j-1]);
				++range[i][j];

			}
			for (int k=1; k<=range[i][j]; ++k)
				++ans[k];
		}
//	debug();
	for (int i=2; ans[i]; ++i)
		printf("%d %d\n", i, ans[i]);
//	for (int len=2; len<=4; ++len){
//		for (int i=0; i<n; ++i){
//			for (int j=0; j<n; ++j)
//				cout << range[i][j][len];
//			cout << endl;
//		}
//		cout << endl;
//	}

    return 0;
}
