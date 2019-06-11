/*
PROB:nuggets
LANG:C++
*/
#include <iostream>

using namespace std;

void zero(){
	printf("0\n");
	exit(0);
}

int gcd(int a, int b){
	if (a % b == 0)
		return b;
	else
		return gcd(b, a%b);
}

int n, pack[15];
bool fit[300];

int main(){
	freopen("nuggets.in", "r", stdin);
	freopen("nuggets.out", "w", stdout);
	scanf("%d", &n);
	for (int i=0; i<n; ++i){
		scanf("%d", pack+i);
		if (pack[i] == 1)
			zero();
	}
	int ans = 1;
	fit[0] = true;
	for (int i=2; i<=256*256; ++i){
		fit[i%257] = false;
		for (int j=0; j<n; ++j)
			if (i>=pack[j] && fit[(i-pack[j]) % 257]){
				fit[i%257] = true;
				break;
			}
		if (fit[i%257] == false)
			ans = i;
	}
	for (int i=256*256+1; i<=2*256*256; ++i){
		fit[i%257] = false;
		for (int j=0; j<n; ++j)
			if (fit[(i-pack[j]) % 257]){
				fit[i%257] = true;
				break;
			}
		if (!fit[i%257])
			zero();
	}
	printf("%d\n", ans);
	return 0;
}
