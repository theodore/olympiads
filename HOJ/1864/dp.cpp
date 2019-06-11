#include <cstdio>
#include <cstring>
#include <algorithm>

#define MAX(a, b, c) std::max(a, std::max(b, c))
#define MIN(a, b, c) std::min(a, std::min(b, c))

const int maxn = 10003;
const int list[3][2] = {{1, 2}, {0, 2}, {0, 1}};

struct Data {
    int min[3], max[3];
    int Max() { return MAX(max[0], max[1], max[2]); }
    int Min() { return MIN(min[0], min[1], min[2]); }
};

int n;
char S[maxn];
Data f[maxn];

int Work(int x)
{
    using std::max;
    using std::min;

    if (S[x] == '0') {
        f[x].min[0] = f[x].max[0] = 1;
        f[x].min[1] = f[x].max[1] = 0;
        f[x].min[2] = f[x].max[2] = 0;
        return x + 1;
    } else if (S[x] == '1') {
        const int ret = Work(x + 1), z = x + 1;
        for (int i = 0; i < 3; ++i) {
            f[x].min[i] = min(f[z].min[list[i][0]], f[z].min[list[i][1]]);
            f[x].max[i] = max(f[z].max[list[i][0]], f[z].max[list[i][1]]);
        }
        f[x].min[0]++;
        f[x].max[0]++;
        return ret;
    } else {
        const int l = x + 1, r = Work(l), ret = Work(r);
        for (int i = 0; i < 3; ++i) {
            const int a = list[i][0], b = list[i][1];
            f[x].min[i] = min(f[l].min[a] + f[r].min[b], f[l].min[b] + f[r].min[a]);
            f[x].max[i] = max(f[l].max[a] + f[r].max[b], f[l].max[b] + f[r].max[a]);
        }
        f[x].min[0]++;
        f[x].max[0]++;
        return ret;
    }
}

int main()
{
    scanf("%s", S);
    n = strlen(S);
    Work(0);
    printf("%d %d\n", f[0].Max(), f[0].Min());
}
