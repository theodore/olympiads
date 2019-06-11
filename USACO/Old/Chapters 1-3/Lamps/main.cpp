/*
ID:theodor8
PROB:lamps
LANG:C++
*/
#include <iostream>
using namespace std;
#pragma warning(disable:4996)
//#define Test

int n, c, goal[110], now[110];
bool found;
inline void init(){
	for (int i=1; i<=n; ++i)
		now[i] = 1;
}
inline void operation1(){
	for (int i=1; i<=n; ++i)
		now[i] ^= 1;
}
inline void operation2(){
	for (int i=1; i<=n; i+=2)
		now[i] ^= 1;
}
inline void operation3(){
	for (int i=2; i<=n; i+=2)
		now[i] ^= 1;
}
inline void operation4(){
	for (int i=1; i<=n; i+=3)
		now[i] ^= 1;
}
inline bool judge(){
	for (int i=1; i<=n; ++i)
		if (goal[i] == 1 && now[i] != 1)
			return false;
		else if (goal[i] == -1 && now[i] != 0)
			return false;
	return true;
}
inline void output(){
	for (int i=1; i<=n; ++i)
		printf("%d", now[i]);
	printf("\n");
}
inline void handle(){
	if (judge()){
		output();
		found = true;
	}
}
#ifndef Test
int main(){
	freopen("lamps.in", "r", stdin);
	freopen("lamps.out", "w", stdout);
	scanf("%d%d", &n, &c);
	int qwertyuiop;
	scanf("%d", &qwertyuiop);
	while (qwertyuiop != -1){
		goal[qwertyuiop] = 1;
		scanf("%d", &qwertyuiop);
	}
	scanf("%d", &qwertyuiop);
	while (qwertyuiop != -1){
		goal[qwertyuiop] = -1;
		scanf("%d", &qwertyuiop);
	}

	switch (c){
	case 0:
		init(); handle();
		break;
	case 1:
		//1 2 3 4
		//1
		init(); operation1(); handle();
		//2
		init(); operation2(); handle();
		//4
		init(); operation4(); handle();
		//3
		init(); operation3(); handle();
		break;
	case 2:
		//1
		init(); operation1(); handle();
		//34
		init(); operation3(); operation4(); handle();
		//2
		init(); operation2(); handle();
		//14
		init(); operation1(); operation4(); handle();
		//3
		init(); operation3(); handle();
		//24
		init(); operation2(); operation4(); handle();
		//0
		init(); handle();
		break;
	default:
		//1
		init(); operation1(); handle();
		//34
		init(); operation3(); operation4(); handle();
		//2
		init(); operation2(); handle();
		//4
		init(); operation4(); handle();
		//14
		init(); operation1(); operation4(); handle();
		//3
		init(); operation3(); handle();
		//24
		init(); operation2(); operation4(); handle();
		//0
		init(); handle();
	}
	if (!found)
		printf("IMPOSSIBLE\n");
	return 0;
}
#else
int main(){
	freopen("test.txt", "w", stdout);
	n = 10;
	init(); printf("1\n"); operation1(); output();
	init(); printf("34\n"); operation3(); operation4(); output();
	init(); printf("2\n"); operation2(); output();
	init(); printf("4\n"); operation4(); output();
	init(); printf("3\n"); operation3(); output();
	init(); printf("14\n"); operation1(); operation4(); output();
	init(); printf("24\n"); operation2(); operation4(); output();
	init(); printf("0\n"); output();
	return 0;
}
#endif
