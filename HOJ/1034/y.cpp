#include <cstdio>
#include <cstring>
#include <cstdlib>
 
const int MAXN = 100010;
 
int N, a[MAXN + 1], b[MAXN + 1];
 
int cmp(const void *a, const void *b) {
 
    return *(int *)a - *(int *)b;
}
 
void pre_work() {
 
    scanf("%d", &N);
    for (int i = 1; i <= N; i++)
        scanf("%d", a + i);
    for (int i = 1; i <= N; i++)
        scanf("%d", b + i);
    qsort(a + 1, N, 4, cmp);
    qsort(b + 1, N, 4, cmp);
}
 
int mark[MAXN + 1];
 
int g(int x, int y) {
     
    if (x == y) return 1;
    return y > x ? 2 : 0;
}
 
int get_ngt(int x, int x0, int *arr) {
 
    static int l, r, mid;
    if (g(arr[1], x0) < x) return 0;
    for (l = 1, r = N + 1; mid = (l + r) >> 1, r - l > 1;
        ((g(arr[mid], x0) >= x ? l : r) = mid));
    return l;
}
 
void add(int l, int r, int x) {
 
    if (l > r) return;
    if (l <= 0 && r <= 0) return;
    if (l <= 0) l = 1; else if (r <= 0) r = 1;
//  printf("%d %d\n", l, r);
    mark[l] += x, mark[r + 1] -= x;
}
 
int doit(int *a, int *b) {
 
    memset(mark, 0, sizeof(mark));
    for (int i = 1; i <= N; i++)
    {
        int l = get_ngt(2, a[i], b);
        int r = get_ngt(1, a[i], b);
//      printf("[%d, %d], [%d, %d]\n", i - l + 1, i, i - r + 1, i - l);
        add(i - l + 1, i, 2);
        add(i - r + 1, i - l, 1);
    }
    int res = 0, t = 0;
    for (int i = 1; i <= N; i++)
    {
        t += mark[i];
        if (t > res) res = t;
    }
    return res;
//  printf("%d\n", res);
}
 
void work() {
 
//  doit(a, b);
    printf("%d %d\n", doit(a, b), N * 2 - doit(b, a));
}
 
int main() {
 
    pre_work();
    work();
 
    return 0;
}
