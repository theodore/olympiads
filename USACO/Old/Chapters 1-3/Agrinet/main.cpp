/*
ID:theodor8
PROB:agrinet
LANG:C++
*/
#include <iostream>
using namespace std;
#pragma warning(disable:4996)

int n, net[110][110], ans, dis[110];
bool in[110];
void expand(const int& pos){
	in[pos] = true;
	int next(0);
	for (int i=0; i<n; ++i){
		if (i!=pos && !in[i] && net[pos][i]<dis[i])
			dis[i] = net[pos][i];
		if (!in[i] && (!next || dis[next]>dis[i]))
			next = i;
	}
	if (next){
		ans += dis[next];
		expand(next);
	}
}
int main(){
	freopen("agrinet.in", "r", stdin);
	freopen("agrinet.out", "w", stdout);
	scanf("%d", &n);
	for (int i=0; i<n; ++i)
		for (int j=0; j<n; ++j)
			scanf("%d", &net[i][j]);
	in[0] = true;
	int next(1);
	for (int i=1; i<n; ++i){
		dis[i] = net[0][i];
		if (dis[next] > dis[i])
			next = i;
	}
	ans += dis[next];
	expand(next);
	printf("%d\n", ans);
	return 0;
}
