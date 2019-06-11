#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>

#define MAXN 10005
#define MAXQ 30005
#define calc(x) (f[x] + (SumT[i] - SumT[x] + S) * SumF[i])

using namespace std;

int N,S,T[MAXN],F[MAXN];
int SumF[MAXN],SumT[MAXN];
int f[MAXN],que[MAXQ],L,R;

inline double g(int a,int b) {
	return (double)(f[a] - f[b]) / (double)(SumT[a] - SumT[b]);
}

int main() {

//	freopen("batch.in","r",stdin);
//	freopen("batch.out","w",stdout);
	SumF[N + 1] = SumT[N + 1] = 0;

	scanf("%d %d",&N,&S);
	for (int i = 1; i <= N; i++) scanf("%d %d",&T[i],&F[i]);
	for (int i = N; i >= 1; i--)
	{
		SumF[i] = SumF[i + 1] + F[i];
		SumT[i] = SumT[i + 1] + T[i];
	}
	
	L = 1; R = 2;
	que[L] = N + 1;

	for (int i = N; i >= 1; i--)
	{
		while (R - L > 1) 
		{
			double tg = g(que[L],que[L + 1]);
		//	if (tg >= SumF[i]) que[L + 1] = que[L++];
		//		else L++;
			if (tg < SumF[i]) L++;
			 else break;
		}
		int prev = que[L];
		f[i] = f[prev] + (SumT[i] - SumT[prev] + S) * SumF[i];
		que[R++] = i;
		while (R - L >= 3 && g(que[R - 3],que[R - 2]) > g(que[R - 2],que[R - 1]))
		{
			que[R - 2] = que[R - 1];
			R--;
		}
	}

	printf("%d\n",f[1]);
	return 0;
}
