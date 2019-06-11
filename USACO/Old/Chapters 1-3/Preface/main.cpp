/*
ID:theodor8
PROB:preface
LANG:C++
*/
#include <iostream>
using namespace std;
#pragma warning(disable:4996)

int n, R[10];
void inline change(int x){
	for (int i=0; x; i+=2){
		int n(x%10);
		x /= 10;
		if (n <= 3)
			R[i] += n;
		else if (n == 4)
			++R[i], ++R[i+1];
		else if (n <= 8)
			++R[i+1], R[i] += n-5;
		else if (n == 9)
			++R[i+2], ++R[i];
		else
			++R[i+2];
	}
}
int main(){
	freopen("preface.in", "r", stdin);
	freopen("preface.out", "w", stdout);
	scanf("%d", &n);
	for (int i=1; i<=n; ++i)
		change(i);
	if (R[0])
		printf("I %d\n", R[0]);
	if (R[1])
		printf("V %d\n", R[1]);
	if (R[2])
		printf("X %d\n", R[2]);
	if (R[3])
		printf("L %d\n", R[3]);
	if (R[4])
		printf("C %d\n", R[4]);
	if (R[5])
		printf("D %d\n", R[5]);
	if (R[6])
		printf("M %d\n", R[6]);
	return 0;
}
