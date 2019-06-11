#include <cstdio>
#include <cstring>
#include <cstdlib>

#define MAXN 100001
#define MAXM (MAXN << 1)

typedef long long LL;

int N,S[MAXN],V[MAXN],d[MAXN];
int fir[MAXN],next[MAXM],end[MAXM],cost[MAXM],ECnt;
LL f[MAXN];

void AddEdge(int st,int ed,int c) {

	next[++ECnt] = fir[st];
	fir[st] = ECnt;
	end[ECnt] = ed;
	cost[ECnt] = c;
}


double g(LL a,LL b) {

	return (f[a] - f[b]) / (double)(d[a] - d[b]);
}

int Stack[MAXN],Top = 0,STop = 1;
int Rec[MAXN][2] = {{0},{0}}; // Rec[0] for value recovery

void PrePush(int v) {

	int prev,L,R,Mid;
	if (Top > 1)
	{
		if (V[v] <= g(Stack[1],Stack[2])) prev = Stack[1];
		else if (V[v] >= g(Stack[Top - 1],Stack[Top])) prev = Stack[Top];
		else
		{
			for (L = 1,R = Top; R - L > 1;)
			{
				Mid = (L + R) >> 1;
				if (g(Stack[Mid],Stack[Mid + 1]) > V[v]) R = Mid;
				else L = Mid;
			}
			prev = Stack[L + 1];
		}
	}
	else prev = Stack[1];

	f[v] = f[prev] + (d[v] - d[prev]) * (LL)V[v] + S[v];

	Rec[v][1] = Top; // Record old Top pos
	while (Top > 1 && g(Stack[Top - 1],Stack[Top]) >= g(Stack[Top],v)) Top--; //maintain the Stack
	Rec[v][0] = Stack[Top + 1]; // Record Top value that will be replaced
	Stack[++Top] = v; //cover the position with v

}

void dfs() {

	// Rec[1] for jump pos recovery
	struct SNode {

		int now,u,par;
	};
	static SNode stack[MAXN]; // 

	stack[1].u = 1;
	stack[1].now = fir[1];
	stack[1].par = -1;
	PrePush(1);

	while (STop)
	{
		int &u = stack[STop].u;
		int &now = stack[STop].now;
		int &par = stack[STop].par;


		int v;

		while ((v = end[now]) == par) now = next[now];
		if (now)
		{
			stack[++STop].u = v;
			stack[STop].now = fir[v];
			stack[STop].par = u;
			d[v] = d[u] + cost[now];
			PrePush(v);
			now = next[now];
		} //push
		else
		{
			STop--;
			Stack[Top] = Rec[u][0]; // Recovery the value
			Top = Rec[u][1]; // Recovery Top
		}
	}
}

int main() {

	scanf("%d",&N);
	int st,ed,c;
	for (int i = 1; i < N; i++)
	{
		scanf("%d %d %d",&st,&ed,&c);
		AddEdge(st,ed,c);
		AddEdge(ed,st,c);
	} // build tree

	for (int i = 2; i <= N; i++)
		scanf("%d %d",&S[i],&V[i]);
	memset(f,127,sizeof(f));
	f[0] = 0;
	dfs();
	for (int i = 2; i < N; i++) printf("%I64d ",f[i]); printf("%I64d\n",f[N]);

	return 0;
}
