#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long int64;
struct Point
{
	int64 x, y;
} p[100011];
int n;
int main()
{
	scanf("%d", &n);
	for(int i = 0; i < n; i ++)
		scanf("%lld%lld", &p[i].x, &p[i].y);
	p[n] = p[0];
	int64 area = 0, sub_ver = 0, sub_hor = 0;
	for(int i = 0; i < n; i ++)
		area += p[i + 1].x * p[i].y - p[i + 1].y * p[i].x;
	area = abs(area);
	for(int i = 0; i < n; i ++)
		if(p[i].x == p[i + 1].x)
			sub_ver += abs(p[i].y - p[i + 1].y);
		else if(p[i].y == p[i + 1].y)
			sub_hor += abs(p[i].x - p[i + 1].x);
	printf("%.3Lf\n", (long double)area - (long double)(sub_ver + sub_hor) / 2);
}
