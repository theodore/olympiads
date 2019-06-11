#include <cstdio>
#include <cstring>
#include <iostream>

typedef long long ll;

int n;
char str[13];
ll ans;
bool vis[13];
int l;

void search(int d, ll v)
{
    if (d == l)
    {
	ans += (v % n == 0);
	return;
    }
    v *= 10;
    bool used[13];
    memset(used, 0, sizeof used);
    for (int i = 0; i < l; ++i)
	if (!vis[i] && !used[str[i] - '0'])
	{
	    vis[i] = true;
	    used[str[i] - '0'] = true;
	    search(d + 1, v + str[i] - '0');
	    vis[i] = false;
	}
}

int main()
{
    int _;
    for (scanf("%d", &_); _--; )
    {
	scanf("%s%d", str, &n);
	l = strlen(str);
	ans = 0;
	search(0, 0);
	std::cout << ans << std::endl;
    }
}
