/*
ID:theodor8
PROB:dualpal
LANG:C++
*/
#include <iostream>
#include <string>
using namespace std;

char dict[] = {'0','1','2','3','4','5','6','7','8','9'};
int n, ans_num;
void solve(const int& s)
{
	int num = 0;
	for (int base=2; base<=10; ++base){
		int tmp = s;
		string ans = "";
		while (tmp){
			ans += dict[tmp % base];
			tmp /= base;
		}
		string sth = "";
		for (int i=ans.length()-1; i>=0; --i)
			sth += ans[i];
		if (sth == ans)
			++num;
		if (num == 2)
			break;
	}
	if(num == 2){
		++ans_num;
		printf("%d\n", s);
	}
}
int main()
{
	freopen("dualpal.in", "r", stdin);
	freopen("dualpal.out", "w", stdout);
	int s;
	scanf("%d%d", &n, &s);
	while (ans_num < n)
		solve(++s);
	return 0;
}
