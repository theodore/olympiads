/*
ID:theodor8
TASK:crypt1
LANG:C++
*/
#include <iostream>
#include <cmath>
#define DEBUG
#pragma warning(disable:4996)
using namespace std;

bool num[10];
int num_ans;
void solve()
{
	for (int x1=1; x1<10; ++x1)
		if (num[x1])
			for (int x2=0; x2<10; ++x2)
				if (num[x2])
					for (int x3=0; x3<10; ++x3)
						if (num[x3])
							for (int y1=1; y1<10; ++y1)
								if (num[y1])
									for (int y2=0; y2<10; ++y2)
										if (num[y2]){
											int x=x1*100+x2*10+x3, y=y1*10+y2;
											int ans1 = x * y2,
												ans2 = x * y1,
												ans = x * y;
											if (abs(floor(log10(double(ans1))+1e-9) - 2) < 1e-9 &&
												abs(floor(log10(double(ans2))+1e-9) - 2) < 1e-9 &&
												abs(floor(log10(double(ans))+1e-9) - 3) < 1e-9 &&
												num[ans1/100] &&
												num[ans1%100/10] &&
												num[ans1%10] &&
												num[ans2/100] &&
												num[ans2%100/10] &&
												num[ans2%10] &&
												num[ans/1000] &&
												num[ans%1000/100] &&
												num[ans%1000%100/10] &&
												num[ans%10])
												++num_ans;
										}
}
int main()
{
	freopen("crypt1.in", "r", stdin);
	freopen("crypt1.out", "w", stdout);
	int n;
	scanf("%d", &n);
	for (int i=0; i<n; ++i){
		int x;
		scanf("%d", &x);
		num[x] = true;
	}
	solve();
	printf("%d\n", num_ans);
	return 0;
}

