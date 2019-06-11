#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>

#define MAXN 100003
#define MAXM 10003
#define BUFSIZE 100000

using namespace std;

struct Node {
	
	int num,size,rank,index;
	Node *left,*right;
};

int V[MAXN],N,M;
int fir[MAXN],next[MAXN << 1],end[MAXN << 1],ECnt;
int Qfir[MAXN],Qnext[MAXM],Qk[MAXM],Qans[MAXM],QCnt;
bool vis[MAXN];

Node Tree[MAXN],*base;

#define UPDATE(p) {\
	p -> size = 1; \
	if (p -> left) p -> size += p -> left -> size; \
	if (p -> right) p -> size += p -> right -> size; \
}

char Buff[BUFSIZE],*ptr = Buff + BUFSIZE,*tail = Buff + BUFSIZE;

#define READ \
if (ptr >= tail)\
{\
	ptr = Buff;\
	fread(Buff,1,BUFSIZE,stdin);\
}\

#define SCAN(x) {\
	x = 0; \
	READ \
	bool neg = 0; \
	while (!(('0' <= (*ptr) && (*ptr) <= '9') || (*ptr == '-'))) {ptr++; READ} \
	if ((*ptr) == '-') {neg = 1; ptr++; READ} \
	while ('0' <= (*ptr) && (*ptr) <= '9'){x =  x * 10 + (*(ptr++)) - '0'; READ} \
	if (neg) x = -x; \
}


void Zig(Node * &pos) {

	Node *t = pos -> left;
	pos -> left = t -> right;
	t -> right = pos;
	UPDATE(pos);
	pos = t;
	UPDATE(pos);
}

void Zag(Node * &pos) {

	Node *t = pos -> right;
	pos -> right = t -> left;
	t -> left = pos;
	UPDATE(pos);
	pos = t;
	UPDATE(pos);
}

void Insert(Node * &pos,Node *Loc) {

	if (!pos)
	{
		pos = Loc;
		pos -> size = 1;
		pos -> rank = rand() & 0x7fffffff;
		pos -> left = pos -> right = NULL; //IMP
		return;
	}
	pos -> size++;
	if (Loc -> num < pos -> num) Insert(pos -> left,Loc);
	else Insert(pos -> right,Loc);

	if (pos -> left && pos -> left -> rank < pos -> rank) Zig(pos);
	else if (pos -> right && pos -> right -> rank < pos -> rank) Zag(pos);
}

int kth(Node *pos,int k) {

	Node *l = pos -> left;
	int ls = l ? l -> size : 0;
	if (k <= ls) return kth(l,k);
	else if (k > ls + 1) return kth(pos -> right,k - ls - 1);
	else return pos -> index;
}


Node *dfs(int u,Node *from,Node * &Root) {

	vis[u] = 1;
	Node *to = from + 1,*Sub,*Ori;
	Root = NULL;
   	from -> num = V[u];
	from -> index = u;
	Insert(Root,from);
	for (int now = fir[u],v; now; now = next[now])
	if (!vis[v = end[now]]) 
	{
		Ori = to;
		to = dfs(v,to,Sub);
		if (Sub -> size < Root -> size)
			for (Node *t = Ori; t != to; t++) Insert(Root,t);
		else
		{
			Root = Sub;
			for (Node *t = from; t != Ori; t++) Insert(Root,t);
		}
	}
	for (int now = Qfir[u]; now; now = Qnext[now])
		Qans[now] = kth(Root,Qk[now]);
	return to;
}


int main() {

	SCAN(N)
	for (int i = 1; i <= N; i++) SCAN(V[i])
	int st,ed;
	for (int i = 1; i < N; i++)
	{
		SCAN(st) SCAN(ed)
		next[++ECnt] = fir[st];
		fir[st] = ECnt;
		end[ECnt] = ed;

		next[++ECnt] = fir[ed];
		fir[ed] = ECnt;
		end[ECnt] = st;
	}
	SCAN(M)
	for (int i = 1; i <= M; i++)
	{
		SCAN(st) SCAN(ed)
		Qnext[++QCnt] =Qfir[st];
		Qfir[st] = QCnt;
		Qk[QCnt] = ed;
	}
	dfs(1,Tree,base = Tree);
	for (int i = 1; i <= M; i++) printf("%d\n",Qans[i]);

	return 0;
}
