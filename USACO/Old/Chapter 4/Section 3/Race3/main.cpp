/*
PROB:race3
LANG:C++
*/
#include <iostream>
#include <cstring>
#include <queue>
//#define MAKE
//#define Debug

using namespace std;

struct E{
	static int num;
	int to, next;
} edge[217];
int start[53];
int startr[53];

int E::num = 0;

bool tos[53];

void add(int from, int to){
	edge[++E::num].to = to;
	edge[E::num].next = start[from];
	start[from] = E::num;
	edge[++E::num].to = from;
	edge[E::num].next = startr[to];
	startr[to] = E::num;
	if (from == to)
		tos[to] = true;
}

int n;

int unavoidable[53], num_una;
int splitting[53], num_spl;

int avoid[53];

queue<int> q;
int c;

bool bfs(int s, int v, bool & sp){
	if (avoid[s])
		return false;
	avoid[s] = v;
	++c;
	q.push(s);
	while (!q.empty()){
		int now = q.front();
		q.pop();
#define Ed edge[e]
		for (int e= v==1 ? start[now] : startr[now]; e; e=Ed.next)
			if (avoid[Ed.to] == 3 - v)
				return false;
			else if (!avoid[Ed.to]){
				++c;
				avoid[Ed.to] = v;
				q.push(Ed.to);
			}
		for (int e= v==1 ? startr[now] : start[now]; e; e=Ed.next)
			if (avoid[Ed.to] == 3 - v)
				sp = false;
	}
	return true;
}

//bool mybfs(int s){
//}

bool unavoid(int x, bool & sp){
	memset(avoid, 0, sizeof(avoid));
	//0 - not visited, 1 - left, 2 - right, 3 - x
	avoid[x] = 3;
	c = 0;
//	if (tos[x])
//		sp = false;
#ifdef Debug
	if (x==5 && sp)
		cout << "still\n";
	bool good = bfs(0, 1, sp);
//	if (x == 5)
//		sp = true;
	good &= bfs(n-1, 2, sp) && c==n-1;
	if (good){
#else
	if (bfs(0, 1, sp) && bfs(n-1, 2, sp) && c==n-1){
#endif
		if (sp){
			for (int e=start[x]; e; e=Ed.next)
				if (avoid[Ed.to] == 1){
					sp = false;
					break;
				}
		}
		return true;
	}
	return false;
#ifndef MAKE
#undef Ed
#endif
}
//bool split(int x){
//	if (tos[x])
//		return false;
//	//mybfs
//	memset(avoid, 0, sizeof(avoid));
//	avoid[x] = 3;
//	c = 0;
//	return mybfs(0) && mybfs(n-1);
//}

int main()
{
	freopen("race3.in", "r", stdin);
	freopen("race3.out", "w", stdout);
	for (int i=0; ; ++i){
		int _;
		for (scanf("%d", &_); _>=0; scanf("%d", &_))
			add(i, _);
		n = i;
		if (_ == -1)
			break;
	}
	//input
#ifdef MAKE
	for (int i=0; i<n-1; ++i){
		for (int e=start[i]; e; e=Ed.next)
			printf("%d -> %d\n", i, Ed.to);
	}
#undef Ed
#else
	for (int i=1; i<n-1; ++i){
		bool split = true;
		if (unavoid(i, split))
{
			unavoidable[num_una++] = i;
		if (split)
			splitting[num_spl++] = i;
}
	}

	printf("%d", num_una);
	for (int i=0; i<num_una; ++i)
		printf(" %d", unavoidable[i]);
	printf("\n%d", num_spl);
	for (int i=0; i<num_spl; ++i)
		printf(" %d", splitting[i]);
	printf("\n");
#endif
	return 0;
}
