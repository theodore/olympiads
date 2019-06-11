/*
ID:theodor8
TASK:namenum
LANG:C++
*/
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

char touch_tone[10][3] ={
	{0, 0, 0},
	{0, 0, 0},
	{'A', 'B', 'C'},
	{'D', 'E', 'F'},
	{'G', 'H', 'I'},
	{'J', 'K', 'L'},
	{'M', 'N', 'O'},
	{'P', 'R', 'S'},
	{'T', 'U', 'V'},
	{'W', 'X', 'Y'},
};

string n, dict[1000], ans;
int voc = -1;
bool not_found = true;


void get_dict(const char& h, const int& len){
	string tmp;
	while (cin>>tmp)
		if ((tmp[0] == h || tmp[0] == h+1 || tmp[0] == h+2) && tmp.length() == len)
			dict[++voc] = tmp;
		else
			if (tmp[0] > h+2)
				break;
}
void find_it()
{
	for (int i = 0; i <= voc; ++i)
		if (ans == dict[i]){
			cout<<ans<<'\n';
			not_found = false;
			break;
		}
}
void search(const int& pos)
{
	if (pos == n.length())
		find_it();
	else
		for (int i = 0; i < 3; ++i){
			if (pos == 0)
				ans = touch_tone[n[pos]-'0'][i];
			else
				ans += touch_tone[n[pos]-'0'][i];
			search(pos+1);
			ans = ans.substr(0, ans.length()-1);
		}
}
int main()
{
	ifstream fin("namenum.in");
	fin>>n;
	freopen("dict.txt", "r", stdin);
	freopen("namenum.out", "w", stdout);
	get_dict(touch_tone[n[0]-'0'][0], n.length());
	search(0);
	if (not_found)
		cout<<"NONE\n";
	return 0;
}
