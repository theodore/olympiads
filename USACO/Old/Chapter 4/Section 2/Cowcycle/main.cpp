/*
PROB:cowcycle
LANG:C++
*/
#include <iostream>
#include <cmath>
#define Sqr(x) (x)*(x)

using namespace std;

int numf, numr, minf, maxf, minr, maxr;
int front[7], rear[13], ansf[7], ansr[13];
bool found = false;
long double var, vart;

bool chosenf[83], chosenr[47];

inline int dblcmp(double x){
	if (abs(x) < 1e-9)
		return 0;
	if (x > 0)
		return 1;
	return -1;
}

void debug(){
	for (int i=0; i<5; ++i)
		printf("%d ", rear[i]);
	printf("\n%f %f\n", var, vart);
}

bool judge(){
	double mean = 0, x[7][13];
	for (int i=0; i<numf; ++i)
		for (int j=0; j<numr; ++j)
			mean += x[i][j] = double(front[i])/rear[j];
	mean /= numf*numr;
	vart = 0;
	for (int i=0; i<numf; ++i)
		for (int j=0; j<numr; ++j)
			vart += Sqr(x[i][j] - mean);
	vart /= numf*numr;
	if (dblcmp(vart) < dblcmp(var) || !found){
		debug();
		return true;
	}
	else
		return false;

//for (int i=0; i<numf; ++i)
//	for (int j=0; j<numr; ++j)
//		printf("%d %d %f\n", front[i], rear[j], double(front[i])/rear[j]);
}

//void debug(){
//	for (int i=0; i<numf; ++i)
//		printf("%d ", front[i]);
//	printf("\n");
//	for (int i=0; i<numr; ++i)
//		printf("%d ", rear[i]);
//	printf("\n");
//
//	for (int i=0; i<numf; ++i)
//		printf("%d ", ansf[i]);
//	printf("\n");
//	for (int i=0; i<numr; ++i)
//		printf("%d ", ansr[i]);
//	printf("\n");
//	printf("%f %f\n", vart, var);
//}

void search(bool front = true, int now = 1){
	if (front){
		if (now == numf-1){
//			printf("Front\n");
			search(false);
			return;
		}
		for (int i=::front[now-1]+1; i<=maxf; ++i)
			if (!chosenf[i]){
				chosenf[i] = true;
				::front[now] = i;
				search(true, now+1);
				chosenf[i] = false;
			}
	}
	else{
//		debug();
		if (now == numr-1){
//			debug();
			if (judge()){
				found = true;
				var = vart;
				memcpy(ansf, ::front, sizeof(::front));
				memcpy(ansr, rear, sizeof(rear));
//	debug();
			}
			return;
		}
		for (int i=rear[now-1]+1; i<rear[numr-1]; ++i)
			if (!chosenr[i]){
				chosenr[i] = true;
				rear[now] = i;
				search(false, now+1);
				chosenr[i] = false;
			}
	}
}

int main(){
	freopen("cowcycle.in", "r", stdin);
	freopen("cowcycle.out", "w", stdout);
	scanf("%d%d%d%d%d%d", &numf, &numr, &minf, &maxf, &minr, &maxr);
	for (front[0]=minf; front[0]<=maxf; ++front[0])
		for (front[numf-1]=front[0]+numf-1; front[numf-1]<=maxf; ++front[numf-1])
			for (rear[0]=minr; rear[0]<=maxr; ++rear[0])
				for (rear[numr-1]=rear[0]+numr-1; rear[numr-1]<=maxr; ++rear[numr-1]){
					if (front[0] == 39 && front[numf-1] == 53 && rear[0] == 12 && rear[numr-1] == 27){
//						cout << "Fuck you\n";
//					printf("%d %d %d %d\n", front[0], front[numf-1], rear[0], rear[numr-1]);

//					if (front[numf-1] * rear[numr-1] >= 3 * front[0] * rear[0]){
//debug();
						chosenf[front[0]] = chosenf[front[numf-1]] =
						 chosenr[rear[0]] = chosenr[rear[numr-1]] = true;
//				printf("Let's go!\n\t%d %d %d %d\n", front[0], front[numf-1], rear[0], rear[numr-1]);
						search();
						chosenf[front[0]] = chosenf[front[numf-1]] =
						 chosenr[rear[0]] = chosenr[rear[numr-1]] = false;
					}
				}
	for (int i=0; i<numf-1; ++i)
		printf("%d ", ansf[i]);
	printf("%d\n", ansf[numf-1]);
	for (int i=0; i<numr-1; ++i)
		printf("%d ", ansr[i]);
	printf("%d\n", ansr[numr-1]);
	return 0;
}
