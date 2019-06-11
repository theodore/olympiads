/*
ID:theodor8
PROB:runround
LANG:C++
*/
#include <iostream>
using namespace std;
#pragma warning(disable:4996)
//#define Debug

inline bool is_round(unsigned x){
	int bit[10];
	bit[0] = 0;
	while (x){
		bit[++bit[0]] = x %10;
		x /= 10;
	}
	if (bit[0] == 1)
		return false;
	bool brandnew[10] = {false};
#ifdef Debug
	for (int i=0; i<10; ++i)
		printf("%d", int(brandnew[i]));
	printf("\n");
#endif
	for (int i=1; i<=bit[0]; ++i)
		brandnew[bit[i]] = true;
#ifdef Debug
	for (int i=0; i<10; ++i)
		printf("%d", int(brandnew[i]));
	printf("\n");
#endif
	//go for it
	int now(bit[0]);
	int step(bit[now]);
	for (int i=0; i<bit[0]; ++i){
		now = ((now-step)%bit[0]+bit[0])%bit[0];
		if (!now)
			now = bit[0];
		step = bit[now];
		if (i != bit[0]-1 && now == bit[0])
			return false;
#ifdef Debug
		printf("Now:\t%d,\tStep:\t%d\n", now, step);
#endif
		if (brandnew[step])
			brandnew[step] = false;
		else
			return false;
	}
	return true;
}
int main(){
	freopen("runround.in", "r", stdin);
	freopen("runround.out", "w", stdout);
	unsigned n;
	scanf("%u", &n);
	for (unsigned i=n+1; ; ++i)
#ifdef Debug
		if (is_round(i))
			cout<<"Shit\n";
		return 0;
#else
		if (is_round(i)){
			printf("%u\n", i);
			return 0;
		}
#endif
	return 0;
}
