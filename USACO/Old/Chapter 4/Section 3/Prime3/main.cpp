/*
PROB:prime3
LANG:C++
*/
#include <iostream>
#include <cstring>

using namespace std;

int prime[78509], num;
bool isp[99999];

void get(){
	const int n = 99999;
	memset(isp, true, sizeof(isp));
	for (long long i=2; i<n; ++i){
		if (!isp[i])
			continue;
		if (i > 10000)
			prime[num++] = i;
//		if (!start && i>10000)
//			start = i;
//		prime[num++] = i;
//		printf("%d\n", i);
		for (long long j=i*i; j<n; j+=i)
			isp[j] = false;
	}
}

int main(){
//	freopen("prime3.in", "r", stdin);
//	freopen("prime3.out", "w", stdout);
	get();
//	printf("%d\n%d\n%d\n", prime[start-1], prime[start], num);
	cout << num << endl;
	return 0;
}
