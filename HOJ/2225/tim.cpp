#include <cstdio>
#include <set>
 
using std::set;
 
const int N_MAX = 100000;
class Point
{
    public:
        int x, y;
        bool operator < (const Point &p) const
        {
            if (x != p.x)
                return x < p.x;
            return y > p.y;
        }
};
 
typedef set<Point> List_t;
List_t list[N_MAX + 1];
int main()
{
    List_t::iterator p;
    int n;
    scanf("%d", &n);
    int len = 0;
    for (int i = 0; i < n; i ++)
    {
        Point cur;
        scanf("%d%d", &cur.x, &cur.y);
        int l, r;
        for (l = 1, r = len; l <= r;)
        {
            int mid = (l + r) >> 1;
            p = list[mid].lower_bound(cur);
            if (p == list[mid].begin())
                r = mid - 1;
            else
            {
                p --;
                if (p->x < cur.x && p->y < cur.y)
                    l = mid + 1;
                else r = mid - 1;
            }
        }
        if (l > len)
            len = l;
        p = list[l].lower_bound(cur);
        for (;p != list[l].end(); list[l].erase(p ++))
            if (cur.y > p->y)
                break;
        list[l].insert(cur);
    }
    printf("%d\n", len);
    return 0;
}
