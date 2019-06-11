/*
PROB:fence
LANG:C++
*/
#include <iostream>
#include <stack>

using namespace std;

stack<int> circuit;
int graph[510][510];
int degree[510];

void find(int s){
	for (int i=1; i<=500; ++i)
		if (graph[s][i]){
			--graph[s][i];
			--graph[i][s];
			find(i);
		}
	circuit.push(s);
}

void judge(int& s){
	for (int i=1; i<=500; ++i)
		if (degree[i] & 1){
			s = i;
			return;
		}
}

int main(){
	freopen("fence.in", "r", stdin);
	freopen("fence.out", "w", stdout);
	int _, mini = 500;
	for (scanf("%d", &_); _; --_){
		int a, b;
		scanf("%d%d", &a, &b);
		++graph[a][b];
		++graph[b][a];
		++degree[a];
		++degree[b];
		if (a < mini)
			mini = a;
		if (b < mini)
			mini = b;
	}
//	judge(mini);
	find(mini);
	while (!circuit.empty()){
		printf("%d\n", circuit.top());
		circuit.pop();
	}
	return 0;
}
