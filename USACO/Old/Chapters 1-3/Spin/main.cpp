/*
PROB:spin
LANG:C++
*/
#include <iostream>
#pragma warning(disable:4996)
#define Debug

using namespace std;

struct X{
	int v, n, start[5], end[5];
} w[5];

int main(){
	freopen("spin.in", "r",  stdin);
	freopen("spin.out", "w", stdout);
	for (int i=0; i<5; ++i){
		scanf("%d%d", &w[i].v, &w[i].n);
		for (int j=0; j<w[i].n; ++j){
			scanf("%d%d", &w[i].start[j], &w[i].end[j]);
			w[i].start[j] = (w[i].start[j] - w[i].v) % 360;
			w[i].end[j] = (w[i].start[j] + w[i].end[j]) % 360;
		}
	}
	///////////////input above//////////////////////////

	for (int time=0; time<=360; ++time){
		for (int i=0; i<5; ++i){
			for (int j=0; j<w[i].n; ++j){
				w[i].start[j] = (w[i].start[j] + w[i].v) % 360;
				w[i].end[j] = (w[i].end[j] + w[i].v) % 360;
			}
		}
		for (int in=0; in<360; ++in){
			for (int i=0; i<5; ++i){
				int good = false;
				for (int j=0; j<w[i].n; ++j){
					int s = w[i].start[j], e = w[i].end[j];
					if (in >= s && in <= e ||(e < s && (in <= e || in >= s)))
						good = true;
				}
				if (!good)
					goto next;
			}
		////////output
		printf("%d\n", time);
		return 0;
next:;
		}
	}
	printf("none\n");
	return 0;
}
