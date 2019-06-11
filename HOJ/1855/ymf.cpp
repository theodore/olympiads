#include <cstdio>
#include <cstring>
#include <cstdlib>

#define MAXT 4002
#define MAXP 2001
#define INF (1 << 30)

int T,P,W;
int AP[MAXT],BP[MAXT],AS[MAXT],BS[MAXT];
int f[MAXT][MAXP],Ans;
int que[MAXP];

#define g(i,id,c,k) (f[i][id] + (c) * ((id) - (k)))

#define MAINTAIN_B(x) while (l < r && g(prev,que[r],+BP[i],x) >= g(prev,que[r - 1],+BP[i],x)) {que[r - 1] = que[r]; r--;}
#define MAINTAIN_A(x) while (l < r && g(prev,que[r],AP[i],x) >= g(prev,que[r - 1],AP[i],x)) {que[r - 1] = que[r]; r--;}

void update(int &des,int src) {

	if (src > des) des = src;
}

int main() {

	scanf("%d %d %d",&T,&P,&W);
	for (int i = 1; i <= T; i++) scanf("%d %d %d %d",&AP[i],&BP[i],&AS[i],&BS[i]);

	for (int i = 0; i <= T; i++)
		for (int j = 0; j <= P; j++)
			f[i][j] = -INF;

	f[0][0] = 0;
	Ans = 0;
	for (int i = 1; i <= T; i++)
	{
		for (int j = 0; j <= P; j++) f[i][j] = f[i - 1][j];

		int l = 0,r = -1,prev = i - W - 1;
		if (prev < 0) prev = 0; ///IMP


		for (int j = 1; j <= BS[i]; j++) 
		{
			que[++r] = j;
			MAINTAIN_B(0);
		}
		for (int j = 1; j <= P; j++)
		{
			update(f[i][j - 1],g(prev,que[l],+BP[i],j - 1));
			if (que[l] <= j) l++;
			if (j + BS[i] <= P) que[++r] = BS[i] + j;
			MAINTAIN_B(j);
		}

		//B
		l = 0,r = -1;
		for (int j = 1; j <= AS[i]; j++)
		{
			que[++r] = P - j;
			MAINTAIN_A(0);
		}
		for (int j = P; j >= 1; j--)
		{
			update(f[i][j],g(prev,que[l],AP[i],j));
			if (que[l] >= j - 1) l++;
			if ((j - 1) - AS[i] >= 0) que[++r] = (j - 1) - AS[i];
			MAINTAIN_A(j - 1);
		}
	}
	for (int i = 0; i <= P; i++) if (f[T][i] > Ans) Ans = f[T][i];
	printf("%d\n",Ans);
	return 0;
}
