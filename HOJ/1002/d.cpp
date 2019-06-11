#include <cstdio>
#include <cstring>
#include <algorithm>

class Int
{
public:
    Int();
    Int(int);
    const Int operator+(const Int&) const;
    void output() const;
private:
    static const int N;
    int n;
    int a[7];
};

const int Int::N = 1000000000;

Int::Int(): n(1)
{
    memset(a, 0, sizeof a);
}

Int::Int(int x): n(1)
{
    memset(a, 0, sizeof a);
    a[0] = x;
}

const Int Int::operator+(const Int& x) const
{
    Int r;
    int& d = r.n = std::max(n, x.n);
    for (int i = 0; i < d; ++i)
    {
	r.a[i] += a[i] + x.a[i];
	if (r.a[i] >= N)
	{
	    r.a[i] -= N;
	    ++r.a[i + 1];
	}
    }
    if (r.a[d])
	++d;
    return r;
}

void Int::output() const
{
    printf("%d", a[n - 1]);
    for (int i = n - 2; i >= 0; --i)
	for (int j = N / 10; j; j /= 10)
	    putchar('0' + a[i] / j % 10);
    putchar('\n');
}

const int maxn = 103;
int n;
Int f[maxn][2];
Int ans;

int main()
{
    scanf("%d", &n);
    f[1][1] = 1;
    for (int i = 2; i <= n; ++i)
	f[i][0] = f[i - 1][0] + f[i - 1][1], f[i][1] = f[i][0] + f[i - 1][1];
    ans = f[n][0] + f[n][1];
    for (int i = 1; i < n; ++i)
	ans = ans + f[i][0] + f[i][1] + f[i][0] + f[i][1];
    ans.output();
}
