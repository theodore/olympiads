#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>

#define MAXN 101

using namespace std;

struct Node {

	int s,t,p;
};

int N,K,T,f[MAXN];
bool can[MAXN];
Node Gang[MAXN];

int cmp(const void *a,const void *b) {

	return ((Node *)a) -> t - ((Node *)b) -> t;
}

int ABS(int x) {

	return (x > 0 ? x : -x);
}

int main() {

	scanf("%d %d %d",&N,&K,&T);
	for (int i = 1; i <= N; i++) scanf("%d",&Gang[i].t);
	for (int i = 1; i <= N; i++) scanf("%d",&Gang[i].p);
	for (int i = 1; i <= N; i++) scanf("%d",&Gang[i].s);
	qsort(Gang + 1,N,sizeof(Node),cmp);

	int Res = 0;
	for (int i = 1; i <= N; i++)
	{
		f[i] = 0;
		for (int j = 1; j < i; j++)
		if (can[j] && Gang[i].t - Gang[j].t >= ABS(Gang[j].s - Gang[i].s) && f[j] + Gang[i].p > f[i])
			f[i] = f[j] + Gang[i].p;
		if (f[i]) can[i] = 1;
		else if (Gang[i].t >= Gang[i].s) //IMP!!
		{
			can[i] = 1;
			f[i] = Gang[i].p;
		}
		if (f[i] > Res) Res = f[i];
	}
	printf("%d\n",Res);
	return 0;
}
