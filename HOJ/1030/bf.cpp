#include <cstdio>
#include <string>
#include <iostream>

using std::string;

const int maxn = 63;
const int maxm = 103;
const int mod = 10007;
int n, m;
char word[maxn][maxm];
int ans;
string st;

void search(const int d)
{
    if (d == m)
    {
	for (int i = 0; i < n; ++i)
	    if (st.find(word[i]) != string::npos)
	    {
		if (++ans == mod)
		    ans = 0;
		return;
	    }
	return;
    }
    for (char c = 'A'; c <= 'Z'; ++c)
    {
	st.push_back(c);
	search(d + 1);
	st.resize(d);
    }
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; ++i)
	scanf("%s", word[i]);
    search(0);
    printf("%d\n", ans);
}
