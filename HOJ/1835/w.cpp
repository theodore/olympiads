#include <cstdio>
#include <iostream>
#include <algorithm>
#include <climits>
#include <cstring>
#include <vector>
#define foreach(e,x) for(__typeof(x.begin()) e=x.begin();e!=x.end();++e)
using namespace std;
 
const int MAX_N = 20000 + 10;
const int MAX_K = 100 + 10;
const int INF = INT_MAX / 2;
typedef long long int64;
int N, K;
int where[MAX_N], costToBuild[MAX_N], range[MAX_N], costNotCovered[MAX_N];
 
void input(int arr[], int n) {
    for (int i = 0; i < n; ++i) {
        scanf("%d", arr + i);
    }
}
 
void inputData() {
    scanf("%d%d", &N, &K);
    where[1] = 0;
    input(where + 2, N - 1);
    input(costToBuild + 1, N);
    input(range + 1, N);
    input(costNotCovered + 1, N);
    where[0] = -INF;
    range[0] = 0;
    costToBuild[0] = 0;
    costNotCovered[0] = 0;
 
    where[N + 1] = INF;
    range[N + 1] = 0;
    costToBuild[N + 1] = 0;
    costNotCovered[N + 1] = 0;
 
    N += 2;
    K += 2;
}
 
int toLeft[MAX_N], toRight[MAX_N];
 
vector<int> idByToRight[MAX_N];
 
void prepare() {
    for (int i = 0; i < N; ++i) {
        toLeft[i] = lower_bound(where, where + N, where[i] - range[i]) - where;
        toRight[i] = upper_bound(where, where + N, where[i] + range[i]) - where
                - 1;
    }
 
    for (int i = 0; i < N; ++i) {
        idByToRight[toRight[i]].push_back(i);
    }
}
 
struct SegTree {
    static const int MAX_N_NODES = MAX_N * 4;
 
    int add[MAX_N_NODES], min[MAX_N_NODES];
    int n;
 
    inline int getMin(int a, int b) {
        return a < b ? a : b;
    }
 
    void update(int t) {
        min[t] = getMin(min[t + t], min[t + t + 1]);
    }
 
    int*arr;
    void build(int t, int l, int r) {
        if (l + 1 == r) {
            add[t] = 0;
            min[t] = arr[l];
            return;
        }
        build(t + t, l, l + r >> 1);
        build(t + t + 1, l + r >> 1, r);
        add[t] = 0;
        update(t);
    }
 
    void apply(int t, int a) {
        add[t] += a;
        min[t] += a;
    }
 
    void relax(int t) {
        if (add[t]) {
            apply(t + t, add[t]);
            apply(t + t + 1, add[t]);
            add[t] = 0;
        }
    }
 
    int ask(int t, int l, int r, int tl, int tr) {
        if (tr <= l || r <= tl)
            return INF;
        if (tl <= l && tr >= r)
            return min[t];
        relax(t);
        return getMin(ask(t + t, l, l + r >> 1, tl, tr), ask(t + t + 1, l + r
                >> 1, r, tl, tr));
    }
 
    void changeAdd(int t, int l, int r, int tl, int tr, int a) {
        if (tr <= l || r <= tl)
            return;
        if (tl <= l && r <= tr) {
            apply(t, a);
            return;
        }
        relax(t);
        changeAdd(t + t, l, l + r >> 1, tl, tr, a);
        changeAdd(t + t + 1, l + r >> 1, r, tl, tr, a);
        update(t);
    }
 
    void changeAdd(int tl, int tr, int a) {
        changeAdd(1, 0, n, tl, tr, a);
    }
 
    int ask(int tl, int tr) {
        return ask(1, 0, n, tl, tr);
    }
 
    void init(int _n, int *_arr) {
        n = _n;
        arr = _arr;
        build(1, 0, n);
    }
};
 
SegTree segTree;
 
int dp[MAX_K][MAX_N];
 
void work() {
    prepare();
 
    for (int i = 0; i < N; ++i) {
        dp[1][i] = INF;
    }
    dp[1][0] = 0;
    for (int k = 2; k <= K; k++) {
        segTree.init(N, dp[k - 1]);
        dp[k][0] = 0;
        for (int i = 1; i < N; ++i) {
            foreach(e,idByToRight[i-1]) {
                int cur = *e;
                segTree.changeAdd(0, toLeft[cur], costNotCovered[cur]);
            }
            dp[k][i] = segTree.ask(0, i) + costToBuild[i];
        }
    }
 
    //  for (int k = 1; k <= K; k++) {
    //      cout << "K:" << k << endl;
    //      for (int i = 0; i < N; i++)
    //          cout << dp[k][i] << " ";
    //      cout << endl;
    //  }
 
    cout << dp[K][N - 1] << endl;
}
 
int main() {
    inputData();
    work();
}
