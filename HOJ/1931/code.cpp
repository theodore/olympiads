#include <cstring>
#include <cassert>
#include <iostream>
#include <algorithm>

class Int
{
public:
    Int();
    Int(int);
    void operator=(const Int&);
    const Int operator*(const Int&) const;
    void operator+=(const Int&);
private:
    friend std::ostream& operator<<(std::ostream&, const Int&);
    static const int N = 10000;
    static const int maxn = 33;
    int n;
    int a[maxn];
};

Int::Int(): n(1)
{
    memset(a, 0, sizeof a);
    a[0] = 0;
}

Int::Int(int x)
{
    memset(a, 0, sizeof a);
    n = 0;
    do
    {
	a[n++] = x % N;
	x /= N;
    } while (x);
}

void Int::operator=(const Int& x)
{
    memcpy(a, x.a, sizeof a[0] * size_t(std::max(n, n = x.n)));
}

const Int Int::operator*(const Int& x) const
{
    Int r;
    for (int i = 0, c = 0; i < n; ++i)
	for (int j = 0; c || j < x.n; ++j)
	{
	    r.n = std::max(r.n, i + j + 1);
	    r.a[i + j] += a[i] * x.a[j] + c;
	    if ((c = r.a[i + j] / N))
		r.a[i + j] %= N;
	}
    return r;
}

void Int::operator+=(const Int& x)
{
    n = std::max(n, x.n);
    int i, c;
    for (i = c = 0; c || i < n; ++i)
    {
	a[i] += x.a[i] + c;
	if ((c = a[i] >= N))
	    a[i] -= N;
    }
    n = i;
}

std::ostream& operator<<(std::ostream& s, const Int& x)
{
    s << x.a[x.n - 1];
    for (int i = x.n - 2; i >= 0; --i)
	for (int j = Int::N / 10; j; j /= 10)
	    s << x.a[i] / j % 10;
    return s;
}

using std::cin;
using std::cout;
using std::endl;
using std::min;
using std::max;

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
