#include <iostream>
#pragma warning(disable:4996)
#define Case_1
#define Case_2
using namespace std;

int a, b, c;
int ans[20], num = 0;

void output(){
	for (int i=0; i<num; ++i)
		cout<<ans[i]<<' ';
	cout<<endl;
}
int test()
{
	freopen("milk3.in", "r", stdin);
	freopen("milk3.out", "w", stdout);
	cin>>a>>b>>c;
	int ao = a, bo = b, co = c;
#ifdef Case_1
	while (c > b && a > 0){
		c -= b;
		a -= b;
		ans[num++] = c;
		if (a < 0){
			c += -a;
			ans[num++] = c;
		}
	}
	output();
#endif
	num = 0;
	a = ao; b = bo; c = co;
#ifdef Case_2
	while (c >= b && a > 0){
		c -= b;
		if (c > 0)
			ans[num++] = c;
		c += ao;
		ans[num++] = c;
		a -= b-a;
		if (a < 0)
			ans[num++] = co + a;
		if (c < b)
			ans[num++] = ao;
	}
	output();
#endif
	return 0;
}
