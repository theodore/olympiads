#include <string.h>
#include <iostream>

#define LS(x) ((x) << 1)
#define RS(x) (LS(x) + 1)
#define L (l ^ 1)
#define R (r ^ 1)

using std::cin;
using std::cout;

typedef long long ll;

const int Max_N = 1 << 18;
int n, N;
ll sum[Max_N], label[Max_N];
ll size[Max_N];

inline void Update(int x)
{
    sum[x] = sum[LS(x)] + sum[RS(x)] + label[x] * size[x];
}

void Add(int l, int r, int z)
{
    bool ll = false, rr = false;
    for (l += N - 1, r += N + 1; l ^ r ^ 1; l >>= 1, r >>= 1) {
        if (ll)
            Update(l);
        if (rr)
            Update(r);
        if (~l & 1)
            sum[L] += z * size[L], label[L] += z, ll = true;
        if (r & 1)
            sum[R] += z * size[R], label[R] += z, rr = true;
    }
    Update(r);
    while (l)
        Update(l), l >>= 1;
}

ll Query(int l, int r)
{
    ll ansl = 0, ansr = 0, ls = 0, rs = 0;
    for (l += N - 1, r += N + 1; l ^ r ^ 1; l >>= 1, r >>= 1) {
        ansl += label[l] * ls;
        ansr += label[r] * rs;
        if (~l & 1)
            ansl += sum[L], ls += size[L];
        if (r & 1)
            ansr += sum[R], rs += size[R];
    }
    ansl += label[l] * ls;
    ansr += label[r] * rs;
    ansl += ansr;
    ls += rs;
    for (l >>= 1; l; l >>= 1)
        ansl += label[l] * ls;
    return ansl;
}

int main()
{
    cin.sync_with_stdio(false);
    int q;
    cin >> n >> q;
    for (N = 4; N < n + 2; N <<= 1)
        ;
    for (int i = 1; i <= n; i++)
        cin >> sum[N + i], size[N + i] = 1;
    for (int i = N - 1; i; i--)
        sum[i] = sum[LS(i)] + sum[RS(i)], size[i] = size[LS(i)] + size[RS(i)];
    while (q--) {
        char a;
        int l, r, z;
        cin >> a >> l >> r;
        if (a == 'C') {
            cin >> z;
            Add(l, r, z);
        } else {
            cout << Query(l, r) << '\n';
        }
    }
}
