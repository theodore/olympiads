#include <cstring>
#include <cassert>
#include <iostream>
#include <algorithm>
#include <cln/cln.h>

using std::cin;
using std::cout;
using std::endl;
using std::min;
using std::max;

typedef cln::cl_I Int;

const int maxn = 67;
int n, m;
int p[maxn];
Int f[maxn][maxn][maxn];

int calc()
{
    int r = 0;
    for (int i = 0; i < n; ++i)
	r += i == p[i];
    return r;
}

void dp()
{
    f[0][0][0] = 1;
    for (int i = 1; i <= n; ++i)
    {
	f[i][0][0] = f[i - 1][0][0] * i;
	for (int j = 1; j <= i; ++j)
	    for (int k = 0; k <= min(j, m); ++k)
	    {
		f[i][j][k] += f[i - 1][j - 1][k] * (i - j);
		if (k)
		    f[i][j][k] += f[i - 1][j - 1][k - 1];
		if (j >= 2)
		    f[i][j][k] += f[i - 1][j - 2][k] * (j - 1);
#ifdef DB
		std::cerr << i << ' ' << j << ' ' << k << ' ' << f[i][j][k] << endl;
#endif
	    }
    }
}

Int answer()
{
    Int ret = 0;
    int left = n;
    int mm = m;
    static bool vis[maxn];
    for (int i = 0; i + max(1, mm) <= n; ++i)
    {
	assert(left >= 0);
	assert(mm >= 0);
	for (int j = 0, t, s; j < p[i]; ++j)
	    if (!vis[j] && (t = left - !vis[i] - (j > i)) >= 0 && (s = mm - (j == i)) >= 0)
		ret += f[n - i - 1][t][s];
	left -= !vis[i] + (p[i] > i);
	vis[p[i]] = true;
	mm -= p[i] == i;
    }
    return ret;
}


int main()
{
    cin >> n;
    for (int i = 0; i < n; ++i)
	cin >> p[i];
    m = calc();
    dp();
    cout << m << ' ' << answer() << endl;
}
