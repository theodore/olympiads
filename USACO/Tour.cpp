/*
PROB: tour
LANG: C++
*/
#pragma warning(disable: 4996)
#include <iostream>
#include <string>
#include <queue>
//#define Debug

using namespace std;

// Declaration
struct E{
	static int num;
	int to;
	int next;
} edge[10010];
struct C{
	string str;
	int start;
	 C();
	inline void add(int);
};
struct P{
	int start, end;
	 P(int, int);
};

// Implementation
int E::num = 0;
C::C()
	: start(0){}
void C::add(int t){
	edge[++E::num].next = start;
	edge[start=E::num].to = t;
}
P::P(int s, int e)
	: start(s), end(e){}

// Global Variables
int n, m;
C city[103];
int dist[101][101];
queue<P> q;

int find(string x){
	for (int i=0; i<n; ++i)
		if (city[i].str == x)
			return i;
	return -1;
}

inline void input(){
	cin >> n >> m;
	for (int i=0; i<n; ++i)
		cin >> city[i].str;
	string t, s;
	int x, y;
	for (int i=0; i<m; ++i){
		cin >> t >> s;
		if ((x=find(t)) < (y=find(s)))
			city[x].add(y);
		else
			city[y].add(x);
	}
}

inline void output(){
	cout << (dist[n-1][n-1] ? dist[n-1][n-1] : 1) << endl;
}

int main(){
	freopen("tour.in", "r", stdin);
	freopen("tour.out", "w", stdout);
	input();
	dist[0][0] = 1;
	q.push(P(0, 0));
	while (!q.empty()){
		P now = q.front();
		q.pop();
#define U edge[u].to
#define V edge[v].to
		if (now.start != now.end || (now.start == 0 && now.end == 0)){
			for (int u=city[now.start].start; u; u=edge[u].next)
				if (U >= now.end && dist[U][now.end] < dist[now.start][now.end] + (U==now.end ? 0 :1)){
					dist[U][now.end] = dist[now.start][now.end] + (U==now.end ? 0 :1);
					q.push(P(U, now.end));
				}
			for (int v=city[now.end].start; v; v=edge[v].next)
				if (V >= now.start && dist[now.start][V] < dist[now.start][now.end] + (now.start==V ? 0 : 1)){
					dist[now.start][V] = dist[now.start][now.end] + (now.start==V ? 0 : 1);
					q.push(P(now.start, V));
				}
			//for (int u=city[now.start].start; u; u=edge[u].next)
			//	for (int v=city[now.end].start; v; v=edge[v].next)
			//		if (U != now.end && V != now.start && !dist[U][V]){
			//			dist[U][V] = dist[now.start][now.end] + (U==V ? 1 : 2);
			//			q.push(P(U, V));
			//		}
		}
#undef U
#undef V
	}
	output();
	return 0;
}
