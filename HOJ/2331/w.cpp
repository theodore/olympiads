#include <cstdio>
#include <iostream>
#include <algorithm>
#include <climits>
#include <cstring>
#define foreach(e,x) for(__typeof(x.begin()) e=x.begin();e!=x.end();++e)
using namespace std;

const int MAX_N = 10 + 2, MAX_L = 100 + 10;
const int MAX_N_STATES = int(2e5);

int dp[2][MAX_N_STATES];
int n, m;
char map[MAX_L][MAX_L];

void swapRC() {
    static char tmp[MAX_L][MAX_L];
    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < m; ++c) {
            tmp[c][r] = map[r][c];
        }
    }
    memcpy(map, tmp, sizeof map);
    swap(n, m);
}

void readInput() {
    cin >> n >> m;
    for (int r = 0; r < n; ++r) {
        scanf(" ");
        scanf("%s", map[r]);
    }
}

const int NONE = 0, NEED = 1, EXTEND = 2;
const int MOD = 20110520;
int pow3[MAX_N];

inline int get(int state, int at) {
    return (state / pow3[at]) % 3;
}

inline void addIt(int&x, int c) {
    x += c;
    if (x >= MOD)
        x -= MOD;
}

void work() {
    pow3[0] = 1;
    for (int i = 1; i < MAX_N; ++i) {
        pow3[i] = pow3[i - 1] * 3;
    }
    int nStates = pow3[m + 1];
    int*am = dp[0], *nam = dp[1];
    memset(am, 0, sizeof(int) * nStates);
    am[0] = 1;
    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < m; ++c) {
            memset(nam, 0, sizeof(int) * nStates);
            for (int s = 0; s < nStates; ++s) {
                int it = am[s];
                if (!it)
                    continue;
                int a = get(s, c), b = get(s, c + 1);
                int pa = pow3[c], pb = pow3[c + 1];
                int ns = s - a * pa - b * pb;
                if (map[r][c] == '*') {
                    if (a != NONE || b != NONE)
                        continue;
                    addIt(nam[ns], it);
                    continue;
                }

                if (a == NONE && b == NONE) {
                    addIt(nam[ns + EXTEND * (pa + pb)], it);
                    addIt(nam[ns + NEED * pa], it);
                    addIt(nam[ns + NEED * pb], it);
                } else if (a == NONE) {
                    addIt(nam[ns + b * pa], it);
                    if (b == NEED)
                        addIt(nam[ns + EXTEND * pb], it);
                    else
                        addIt(nam[ns], it);
                } else if (b == NONE) {
                    addIt(nam[ns + a * pb], it);
                    if (a == NEED)
                        addIt(nam[ns + EXTEND * pa], it);
                    else
                        addIt(nam[ns], it);
                } else {
                    if (a == NEED && b == NEED)
                        addIt(nam[ns], it);
                }
            }
            swap(am, nam);
        }
        if (r == n - 1)
            break;
        memset(nam, 0, sizeof(int) * nStates);
        for (int s = 0; s < nStates; ++s) {
            if (get(s, m) == NONE)
                addIt(nam[s * 3], am[s]);
        }
        swap(am, nam);
    }
    printf("%d\n", am[0]);
}

void solve() {
    readInput();
    if (n < m)
        swapRC();
    work();
}

int main() {
    solve();
}
