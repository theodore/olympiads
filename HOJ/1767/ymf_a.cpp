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
//	while (Top > 1 && g(Stack[Top - 1],Stack[Top]) >= g(Stack[Top],v)) Top--; //maintain the Stack
	
	if (Top > 1)
	{
		for (L = 1,R = Top + 1; R - L > 1;)
		{
			Mid = (L + R) >> 1;
			if (g(Stack[Mid - 1],Stack[Mid]) < g(Stack[Mid],v)) L = Mid;
			else R = Mid;
		}
		Top = L;
	}
	Rec[v][0] = Stack[Top + 1]; // Record Top value that will be replaced
	Stack[++Top] = v; //cover the position with v

}

void PrePop(int u) {

	Stack[Top] = Rec[u][0]; // Recovery the value
	Top = Rec[u][1]; // Recovery Top
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
	
	int v;
	while (STop)
	{
		int &u = stack[STop].u;
		int &now = stack[STop].now;
		int &par = stack[STop].par;

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
			PrePop(u);
			STop--;
		}
	}
}

#define BUFSIZE 1000000
char buf[BUFSIZE], *pt = buf + BUFSIZE, *pend = buf + BUFSIZE;
#define read() \
	do{ \
		if (pt >= pend) \
		{ \
			pt = buf; \
			fread(buf, 1, BUFSIZE, stdin); \
		} \
	} while(0) 

#define scan(t) \
{ \
	t = 0; \
	read(); \
	bool nega = false; \
	while (!(((*pt) >= '0' && (*pt) <= '9') || (*pt == '-'))) {pt ++; read();} \
	if ((*pt) == '-') {nega = true, pt ++; read();} \
	while (((*pt) >= '0' && (*pt) <= '9')) {t = t * 10 + (*(pt ++)) - '0'; read();}\
	if (nega) t = -t; \
}

char str[3000000];
int pos = 0;
void Add(long long v)
{
	int cnt = 0;
	static char buf[100];
	while (v)
		buf[cnt ++] = v % 10 + '0', v /= 10;
	if (!cnt)
		buf[cnt ++] = '0';
	while (cnt)
		str[pos ++] = buf[-- cnt];
	str[pos ++] = ' ';
}

int main() {

	scan(N);
	int st,ed,c;
	for (int i = 1; i < N; i++)
	{
		scan(st);scan(ed);scan(c);
		AddEdge(st,ed,c);
		AddEdge(ed,st,c);
	} // build tree

	for (int i = 2; i <= N; i++)
	{
		scan(S[i]);scan(V[i]);
	}
	memset(f,127,sizeof(f));
	f[0] = 0;
	dfs();
	/*
	for (int i = 2; i < N; i++)
		printf("%I64d ",f[i]);
	printf("%I64d\n",f[N]);
	*/
	for (int i = 2; i <=N; ++i)
		Add(f[i]);
	puts(str);
	return 0;
}
