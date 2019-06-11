/*
PROB:butter
LANG:C++
*/
#include <iostream>
#pragma warning(disable:4996)
//#define Debug

using namespace std;

int n, c, p, cow[510], graph[810][810];
struct{
	int to, next, cost;
} edge[3000];
int num, start[810];

void add(int a, int b, int c){
	edge[++num].cost = c;
	edge[num].to = b;
	edge[num].next = start[a];
	start[a] = num;
	edge[++num].cost = c;
	edge[num].to = a;
	edge[num].next = start[b];
	start[b] = num;
}

int q[810], front, back;
bool in[810];
void spfa(int s){
	graph[s][s] = 0;
	q[front = 0] = s;
	back = 1;
	in[s] = true;
	while (front != back){
		int e = q[front++];
		in[e] = false;
		front %= p;
		for (int t=start[e]; t; t=edge[t].next)
			if (!graph[s][edge[t].to] || graph[s][e]+edge[t].cost < graph[s][edge[t].to]){
				graph[s][edge[t].to] = graph[s][e] + edge[t].cost;
				if (!in[edge[t].to]){
					in[edge[t].to] = true;
					q[back++] = edge[t].to;
					back %= p;
				}
			}
	}
	graph[s][s] = 0;
}

int main(){
	freopen("butter.in", "r", stdin);
	freopen("butter.out", "w", stdout);
	scanf("%d%d%d", &n, &p, &c);
	for (int i=1; i<=n; ++i)
		scanf("%d", cow+i);
	for (int i=0; i<c; ++i){
		int a, b, c;
		scanf("%d%d%d", &a, &b, &c);
		add(a, b, c);
	}
	/////////
#ifdef Debug
	spfa(4);
	for (int i=1; i<=p; ++i){
		for (int j=1; j<=p; ++j)
			printf("%d ", graph[i][j]);
		printf("\n");
	}
	return 0;
#else
	for (int i=1; i<=p; ++i)
		spfa(i);
#endif
	/////////
	int ans = 1<<30;
	for (int s=1; s<=p; ++s){
		int path = 0;
		for (int i=1; i<=n; ++i)
			if ((path += graph[cow[i]][s]) >= ans)
				goto next;
		ans = path;
next:;
	}
	printf("%d\n", ans);
#ifdef Debug
	for (int i=1; i<=p; ++i){
		for (int j=1; j<=p; ++j)
			printf("%d ", graph[i][j]);
		printf("\n");
	}
#endif
	return 0;
}
