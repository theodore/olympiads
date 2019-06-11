/*
ID:theodor8
PROB:fracdec
LANG:C++
*/
#include <iostream>
#include <string.h>
using namespace std;
#pragma warning(disable:4996)

int num, den, count2, count5;
char output[100000];
inline int gcd(int a, int b){
	while (a%b){
		int r=a;
		a = b;
		b = r%b;
	}
	return b;
}
inline bool finite(){
	int g(gcd(num, den));
	if (g!=1){
		num /= g;
		den /= g;
	}
	int t(den);
	while (!(t%2))
		t /= 2, ++count2;
	while (!(t%5))
		t /= 5, ++count5;
	return (t==1);
}
int seek(){
	int i(0);
	while (output[i] != '\0')
		++i;
	return i;
}
void divide(bool good){
	sprintf(output, "%d.", num/den);
	int pos = seek();
	num %= den;
	if (num){
		if (good){
			while (num){
				num *= 10;
				int t(num/den);
				output[pos++] = t+'0';
				num %= den;
			}
			output[pos] = '\0';
		}
		else{
			int count(max(count2, count5));
			for (int i=0; i<count; ++i){
				num *= 10;
				int t(num/den);
				output[pos++] = t+'0';
				num %= den;
			}
			int remainder(num);
			output[pos++] = '(';
			do{
				num *= 10;
				int t(num/den);
				output[pos++] = t+'0';
				num %= den;
			} while (num != remainder);
			output[pos++] = ')';
			output[pos++] = '\0';
		}
	}
	else{
		output[pos] = '0';
		output[++pos] = '\0';
	}
}
int main(){
	freopen("fracdec.in", "r", stdin);
	freopen("fracdec.out", "w", stdout);
	scanf("%d%d", &num, &den);
	divide(finite());

	//output
	for (int i=0; output[i]!='\0'; ++i){
		printf("%c", output[i]);
		if (i%76 == 75)
			printf("\n");
	}
	if (strlen(output)%76)
		printf("\n");
	return 0;
}
