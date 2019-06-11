/*
PROB:fence9
LANG:C++
*/
#include <iostream>
#include <cmath>

using namespace std;

struct point{
	double x, y;
	 point();
	 point(double, double);
	point operator-(point);
};

point::point()
	: x(0), y(0){
}
point::point(double a, double b)
	: x(a), y(b){
}
point point::operator-(point oper){
	return point(x-oper.x, y-oper.y);
}

int det(point a, point b){
	double d = a.x*b.y - a.y*b.x;
	if (abs(d) < 1e-6)
		return 0;
	else if (d > 0)
		return 1;
	else
		return -1;
}

int ans;
point top, Right;
int main(){
	freopen("fence9.in", "r", stdin);
	freopen("fence9.out", "w", stdout);
	scanf("%lf%lf%lf", &top.x, &top.y, &Right.x);
	int l = 0, r = Right.x-1;
	for (int h=1; h<top.y; ++h){
		//find new l
		while (det(top, point(l, h)) >= 0)
			++l;
		if (Right.x > top.x)
			while (det(top-Right, point(r, h)-Right) <= 0)
				--r;
		if (Right.x < top.x){
			bool changed = false;
			while (det(top-Right, point(r, h)-Right) > 0){
				++r;
				changed = true;
			}
			if (changed)
				--r;
		}
		//find new r
//		if (r<l)
//			printf("%d\n", h);
//			break;
		ans += r-l+1;
	}
	printf("%d\n", ans);
	return 0;
}
