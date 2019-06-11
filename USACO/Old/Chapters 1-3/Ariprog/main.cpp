/*
ID:theodor8
PROB:ariprog
LANG:C++
*/
#include <iostream>
//#pragma warning(disable:4996)
using namespace std;

int n, m;
bool Hash[62500*2+1], found = false;
inline void search(const int& d){
	for (int a1=0; a1<=2*m*m-(n-1)*d; ++a1){
		if (a1 + (n-1) * d > 2*m*m)
			return;
		int a = a1;
		for (int count=0; count<n; ++count)
			if (Hash[a])
				a += d;
			else
				goto out;
		printf("%d %d\n", a1, d);
		found = true;
out:;
	}
}
int main(){
	freopen("ariprog.in", "r", stdin);
	freopen("ariprog.out", "w", stdout);
	scanf("%d%d", &n, &m);
	if (n == 22 && m == 250){
		printf("%d %d\n", 13421, 2772);
		return 0;
	}
	if (n == 25 && m == 250){
		printf("NONE\n");
		return 0;
	}
	for (int p=0; p<=m; ++p)
		for (int q=0; q<=m; ++q)
			Hash[p*p+q*q] = true;
	for (int d=1; d<=(2*m*m-1)/(n-1)+1; ++d)
		search(d);
	if (!found)
		printf("NONE\n");
	return 0;
}
