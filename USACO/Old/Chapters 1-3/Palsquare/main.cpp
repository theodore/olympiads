/*
ID:theodor8
PROB:palsquare
LANG:C++
*/
#include <iostream>
#include <string>
using namespace std;

char dict[] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F','G','H','I','J'};
int base;
bool good(const string&);
void solve(const int& what)
{
	string ans="";
	int tmp = what;
	while (tmp){
		ans += dict[tmp % base];
		tmp /= base;
	}
	string ans1 = "";
	for (int i=ans.length()-1; i>=0; --i)
		ans1 += ans[i];
	string sqr="";
	tmp = what * what;
	while (tmp){
		sqr += dict[tmp % base];
		tmp /= base;
	}
	if (good(sqr))
		cout<<ans1<<' '<<sqr<<endl;
}
int main()
{
	freopen("palsquare.in", "r", stdin);
	freopen("palsquare.out", "w", stdout);
	scanf("%d", &base);
	for (int i=1; i<=300; ++i)
		solve(i);
	return 0;
}
bool good(const string& sth)
{
	string tmp = "";
	for (int i=sth.length()-1; i>=0; --i)
		tmp += sth[i];
	return tmp==sth;
}
