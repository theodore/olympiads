#include <cstdio>
#include <algorithm>

#define UPN(a, b) a = std::min(a, b)

const int Max_n = 100007;
const int Max_log = 19;
int n;
int tree[Max_log][Max_n], toleft[Max_log][Max_n], sorted[Max_n];
int leftof[Max_n * 2], midof[Max_n * 2];

void MkTree(int d, int l, int r, int idx)
{
    if (r - l <= 1)
        return;
    const int mid = (l + r) / 2; // [l, r) -> [l, mid) + [mid, r)
    leftof[idx] = l;
    midof[idx] = mid;
    const int pivot = sorted[mid]; // nums < pivot goes left
    const int oldval = toleft[d][l - 1];
    toleft[d][l - 1] = 0;
    for (int i = l, ll = l, rr = mid; i < r; i++) {
        toleft[d][i] = toleft[d][i - 1];
        if (tree[d][i] < pivot)
            tree[d + 1][ll++] = tree[d][i], toleft[d][i]++;
        else
            tree[d + 1][rr++] = tree[d][i];
    }
    toleft[d][l - 1] = oldval;
    MkTree(d + 1, l, mid, idx * 2);
    MkTree(d + 1, mid, r, idx * 2 + 1);
}

void Init()
{
    for (int i = 1; i <= n; i++)
        scanf("%d", &tree[0][i]), sorted[i] = tree[0][i];
    std::sort(sorted + 1, sorted + n + 1);
    MkTree(0, 1, n + 1, 1);
}

int Query(int l, int r, int k)
{
    int d, i;
    for (d = 0, i = 1, r++; r - l > 1; d++) {
        int a = (l == leftof[i] ? 0 : toleft[d][l - 1]);
        int b = toleft[d][r - 1];
#if DB & 1
        fprintf(stderr, "%d: (%d %d) %d, %d, k = %d\n", d, l, r, a, b, k);
#endif
        if (k <= b - a) {
            l = leftof[i] + a;
            r = leftof[i] + b;
            i *= 2;
        } else {
            k -= b - a;
            a = l - leftof[i] - a;
            b = r - leftof[i] - b;
#if DB & 1
            fprintf(stderr, "now, a = %d, b = %d\n", a, b);
#endif
            l = midof[i] + a;
            r = midof[i] + b;
            i *= 2;
            i++;
        }
    }
    return tree[d][l];
}

#if DB & 1
void PTree()
{
    int depth = 1;
    for (int t = n; t != 1; t = (t + 1) / 2)
        depth++;
    for (int d = 0; d < depth; d++, fprintf(stderr, "\n")) {
        fprintf(stderr, "%d:", d);
        for (int i = 1; i <= n; i++)
            fprintf(stderr, " %d", tree[d][i]);
    }
    for (int d = 0; d < depth; d++, fprintf(stderr, "\n")) {
        fprintf(stderr, "%d:", d);
        for (int i = 1; i <= n; i++)
            fprintf(stderr, " %d", toleft[d][i]);
    }
    for (int i = 1; i < (1 << depth); i++) {
        fprintf(stderr, "%d ", leftof[i]);
        i++;
        if ((i ^ (i & -i)) == 0)
            fprintf(stderr, "\n");
        i--;
    }
    for (int i = 1; i < (1 << depth); i++) {
        fprintf(stderr, "%d ", midof[i]);
        i++;
        if ((i ^ (i & -i)) == 0)
            fprintf(stderr, "\n");
        i--;
    }
    fprintf(stderr, "\n\n");
}
#endif

int main()
{
    int q;
    scanf("%d%d", &n, &q);
    Init();
#if DB & 1
    PTree();
#endif
    while (q--) {
        int l, r, k;
        scanf("%d%d%d", &l, &r, &k);
        printf("%d\n", Query(l, r, k));
    }
}
