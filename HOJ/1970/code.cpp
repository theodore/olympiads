#include <cstdio>
#include <cstring>
#include <iomanip>
#include <iostream>

typedef std::ostream OS;

class Int {
public:
    Int();
    Int(int);
    void operator+=(const Int&);
    friend Int pow2(int);
    friend OS& operator<<(OS&, const Int&);
private:
    static const int N = 100000000;
    int num[4];
};

Int::Int()
{
    memset(num, 0, sizeof num);
}

Int::Int(int x)
{
    memset(num, 0, sizeof num);
    for (int i = 0; x; i++)
        num[i] = x % N, x /= N;
}

void Int::operator+=(const Int& x)
{
    for (int i = 0, c = 0; i < 4; i++) {
        num[i] += x.num[i] + c;
        c = num[i] / N;
        num[i] %= N;
    }
}

Int pow2(int x)
{
    Int ret = 1;
    for (int i = 0; i < x; i++)
        ret += ret;
    return ret;
}

OS& operator<<(OS& o, const Int& x)
{
    bool out = false;
    for (int i = 3; i >= 0; i--)
        if (out) {
            o << std::setw(8) << std::setfill('0') << x.num[i];
        } else if (x.num[i]) {
            o << x.num[i];
            out = true;
        }
    if (!out)
        o << 0;
    return o;
}

const int max_n = 203;
char str[max_n];
Int ans;

int Work(int p, int k)
{
#if DB & 1
    fprintf(stderr, "Work %d %d\n", p, k);
#endif
    int ret = p + 1;
    if (str[p] == '0')
        ans += pow2(2 * k);
    else if (str[p] == '2')
        for (int i = 0; i < 4; i++)
            ret = Work(ret, k - 1);
    return ret;
}

int main()
{
    int n;
    scanf("%d", &n);
    scanf("%s", str);
    Work(0, n);
    std::cout << ans << std::endl;
}
