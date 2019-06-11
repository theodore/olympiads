/** @file LIS2.cpp
 *  @brief SPOJ LIS2, Another Longest Increasing Subsequence.
 *  A traditional problem in 2D. Still bisection, but then we use a set to
 *  maintain all points having the same length.
 *  @author Theodore You <theodoreyou@gmail.com>
 *  @date Mon, 11 Apr 2011 21:33:46 +0800
 */

#include <cstdio>
#include <set>
#include <algorithm>

struct Point
{
    int x, y;
    bool operator<(const Point& z) const
    {
	return x < z.x || (x == z.x && y < z.y);
    }
};

typedef std::set<Point> S;
const int maxn = 100007;
int n;
S leng[maxn];

bool cmp(const S& s, const S& z)
{
    const Point& x = *z.begin();
    S::const_iterator t = s.lower_bound(x);
    return t != s.begin() && (--t)->y < x.y && (t->x < x.x || (t != s.begin() && (--t)->y < x.y));
    //if (t == s.end())
    //--t;
    //while (t != s.begin() && x.x <= t->x)
    //--t;
    //return t->x < x.x && t->y < x.y;
}

int main()
{
    scanf("%d", &n);
    int ans = 0;
    Point p;
    p.x = -1e9 - 1;
    p.y = -1e9 - 1;
    leng[0].insert(p);
    while (n--)
    {
	scanf("%d%d", &p.x, &p.y);
	const int z = std::lower_bound(leng, leng + ans + 1, S(&p, &p + 1), cmp)
	    - leng;
	ans = std::max(ans, z);
	S& s = leng[z];
	S::iterator t = s.lower_bound(p);
	if (t == s.begin() || p.y < (--t)->y)
	{
	    S::iterator i = s.insert(p).first;
	    for (++i; i != s.end() && p.y <= i->y; s.erase(i++))
		;
	}
    }
    printf("%d\n", ans);
}
