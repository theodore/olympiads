/*
 * [Coci 2009]PATULJCI.cpp
 *
 *  Created on: 2011-4-5
 *      Author: user
 */
 
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <climits>
#include <cstring>
#include <vector>
#define foreach(e,x) for(__typeof(x.begin()) e=x.begin();e!=x.end();++e)
using namespace std;
 
struct Info {
    int what, num;
    void set(int me) {
        what = me;
        num = 1;
    }
    void clear() {
        what = -1;
        num = 0;
    }
    Info() {
        clear();
    }
};
 
Info operator+(Info l, Info r) {
    Info me;
    if (l.num < r.num)
        swap(l, r);
    me = l;
    if (r.what == me.what)
        me.num += r.num;
    else
        me.num -= r.num;
    return me;
}
 
const int MAX_N_NODES = 300000 + 10;
 
struct SegTree {
    static const int MAX_T = MAX_N_NODES * 4;
    Info info[MAX_T];
    int offSet;
 
    void setLeave(int where, int toWhat) {
        info[where + offSet].set(toWhat);
    }
 
    void init(int cap) {
        offSet = 1;
        while (offSet <= cap + 3)
            offSet <<= 1;
        for (int i = 0; i < offSet * 2; ++i) {
            info[i].clear();
        }
    }
 
    void start() {
        for (int i = offSet - 1; i >= 1; --i) {
            info[i] = info[i + i] + info[i + i + 1];
        }
    }
 
    Info ask(int l, int r) {
        l += offSet - 1;
        r += offSet + 1;
        Info ret;
        for (; l ^ r ^ 1; l >>= 1, r >>= 1) {
            if (~l & 1)
                ret = ret + info[l ^ 1];
            if (r & 1)
                ret = ret + info[r ^ 1];
        }
        return ret;
    }
};
 
SegTree segTree;
int nums[MAX_N_NODES], nNums;
 
vector<int> where[MAX_N_NODES];
int seq[MAX_N_NODES];
 
bool check(int l, int r, int what) {
    if (what == -1)
        return false;
    vector<int>&cur = where[lower_bound(nums, nums + nNums, what) - nums];
    return upper_bound(cur.begin(), cur.end(), r) - lower_bound(cur.begin(),
            cur.end(), l) > (r - l + 1) / 2;
}
 
inline void scanInt(int&x) {
    char ch;
    while (ch = getchar(), ch < '0' || ch > '9')
        ;
    x = ch - '0';
    while (ch = getchar(), ch >= '0' && ch <= '9')
        x = x * 10 + ch - '0';
}
 
int main() {
    //  freopen("in", "r", stdin);
    int n, nC;
    scanInt(n);
    scanInt(nC);
    segTree.init(n);
 
    nNums = 0;
    for (int i = 1; i <= n; ++i) {
        int what;
        scanInt(what);
        segTree.setLeave(i, what);
        nums[nNums++] = what;
        seq[i] = what;
    }
    segTree.start();
 
    sort(nums, nums + nNums);
    nNums = unique(nums, nums + nNums) - nums;
 
    for (int i = 1; i <= n; ++i) {
        int what = seq[i];
        int id = lower_bound(nums, nums + nNums, what) - nums;
        where[id].push_back(i);
    }
 
    int nQ;
    scanInt(nQ);
    while (nQ--) {
        int l, r;
        scanInt(l);
        scanInt(r);
        Info me = segTree.ask(l, r);
        int what = me.what;
        if (check(l, r, what))
            printf("yes %d\n", what);
        else
            printf("no\n");
    }
}
