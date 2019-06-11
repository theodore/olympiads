#include <cstdio>
#include <algorithm>
#include <vector>

#define pb push_back

typedef std::vector<int> List_t;
typedef List_t::iterator Viter;

const int max_n = 1000007;
int n;
List_t list[max_n];

int main()
{
    scanf("%d", &n);
    for (int i = 1, x; i <= n; i++) {
        scanf("%d", &x);
        list[x].pb(i);
    }
    int q;
    for (scanf("%d", &q); q--; ) {
        int l;
        static int num[max_n];
        scanf("%d", &l);
        for (int i = 0; i < l; i++)
            scanf("%d", &num[i]);
        for (int i = 0, p = 0; i < l; i++) {
            Viter t = std::upper_bound(list[num[i]].begin(),
                    list[num[i]].end(), p);
            if (t == list[num[i]].end()) {
                puts("NIE");
                goto next;
            }
            p = *t;
        }
        puts("TAK");
next:;
    }
}
