#include <iostream>
#pragma warning(disable:4996)

using namespace std;

const int infinity = 1<<30;
int n, net[100][100], ans;
bool in[100];
inline void expand(int pos){
	in[pos] = true;
	int ret(pos==0?0:infinity);
	if (ret)
		for (int i=0; i<n; ++i)
			if (i!=pos && in[i] && net[i][pos] && net[i][pos]<ret)
				ret = net[i][pos];
	ans += ret;
	for (int i=0; i<n; ++i)
		if (i!=pos && net[pos][i] && !in[i])
			expand(i);
}
int main(){
	freopen("agrinet.in", "r", stdin);
	//freopen("agrinet.out", "w", stdout);
	scanf("%d", &n);
	for (int i=0; i<n; ++i)
		for (int j=0; j<n; ++j)
			scanf("%d", &net[i][j]);
	expand(0);
	printf("%d\n", ans);
	return 0;
}
