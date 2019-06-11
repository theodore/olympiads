/*
PROB:fence3
LANG:C++
*//*
#pragma warning(disable: 4996)
#include <iostream>
#include <cmath>
#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b, c) min(min(a, b), c)
#define MAX(a, b, c) max(max(a, b), c)

using namespace std;

struct P{
	int x, y;
};

struct L{
	P a, b;
} line[153];

int n;

double calc(int x, int y){
	double ret(0);
	for (int i=0; i<n; ++i)
		if (line[i].a.x == line[i].b.x)
			if (min(line[i].a.y, line[i].b.y) <= y && max(line[i].a.y, line[i].b.y) >= y)
				ret += abs(x - line[i].a.x);
			else
				ret += min(hypot(x - line[i].a.x, y - line[i].a.y), hypot(x - line[i].b.x, y - line[i].b.y));
		else
			if (min(line[i].a.x, line[i].b.x) <= x && max(line[i].a.x, line[i].b.x) >= x)
				ret += abs(y -  line[i].a.y);
			else
				ret += min(hypot(x - line[i].a.x, y - line[i].a.y), hypot(x - line[i].b.x, y - line[i].b.y));
	return ret;
}

int main(){
	freopen("fence3.in", "r", stdin);
	freopen("fence3.out", "w", stdout);
	scanf("%d", &n);
	int l, r, u, d;
	for (int i=0; i<n; ++i){
		scanf("%d%d%d%d", &line[i].a.x, &line[i].a.y, &line[i].b.x, &line[i].b.y);
		line[i].a.x *= 10;
		line[i].a.y *= 10;
		line[i].b.x *= 10;
		line[i].b.y *= 10;
		if (!i){
			l = min(line[i].a.x, line[i].b.x);
			r = max(line[i].a.x, line[i].b.x);
			d = min(line[i].a.y, line[i].b.y);
			u = max(line[i].a.y, line[i].b.y);
		}
		else{
			l = MIN(line[i].a.x, line[i].b.x, l);
			r = MAX(line[i].a.x, line[i].b.x, r);
			d = MIN(line[i].a.y, line[i].b.y, d);
			u = MAX(line[i].a.y, line[i].b.y, u);
		}
	}
	P ans;
	double cur;
	for (int i=l; i<=r; ++i)
		for (int j=d; j<=u; ++j){
			double now = calc(i, j);
			if ((i == l && j == d) || (cur > now)){
				cur = now;
				ans.x = i;
				ans.y = j;
			}
		}
	printf("%.1f %.1f %.1f\n", ans.x/10., ans.y/10., cur/10);
	return 0;
}
*/
#pragma warning(disable: 4996)
#include <iostream>
#include <cmath>
#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b, c) min(min(a, b), c)
#define MAX(a, b, c) max(max(a, b), c)

using namespace std;

struct P{
	int x, y;
};

struct L{
	P a, b;
} line[153];

int n;

double calc(int x, int y){
	double ret(0);
	for (int i=0; i<n; ++i)
		if (line[i].a.x == line[i].b.x)
			if (min(line[i].a.y, line[i].b.y) <= y && max(line[i].a.y, line[i].b.y) >= y)
				ret += abs(x - line[i].a.x);
			else
				ret += min(hypot(x - line[i].a.x, y - line[i].a.y), hypot(x - line[i].b.x, y - line[i].b.y));
		else
			if (min(line[i].a.x, line[i].b.x) <= x && max(line[i].a.x, line[i].b.x) >= x)
				ret += abs(y -  line[i].a.y);
			else
				ret += min(hypot(x - line[i].a.x, y - line[i].a.y), hypot(x - line[i].b.x, y - line[i].b.y));
	return ret;
}

int main(){
	freopen("fence3.in", "r", stdin);
	freopen("fence3.out", "w", stdout);
	scanf("%d", &n);
	int l, r, u, d;
	for (int i=0; i<n; ++i){
		scanf("%d%d%d%d", &line[i].a.x, &line[i].a.y, &line[i].b.x, &line[i].b.y);
		line[i].a.x *= 10;
		line[i].a.y *= 10;
		line[i].b.x *= 10;
		line[i].b.y *= 10;
		if (!i){
			l = min(line[i].a.x, line[i].b.x);
			r = max(line[i].a.x, line[i].b.x);
			d = min(line[i].a.y, line[i].b.y);
			u = max(line[i].a.y, line[i].b.y);
		}
		else{
			l = MIN(line[i].a.x, line[i].b.x, l);
			r = MAX(line[i].a.x, line[i].b.x, r);
			d = MIN(line[i].a.y, line[i].b.y, d);
			u = MAX(line[i].a.y, line[i].b.y, u);
		}
	}
	P ans;
	ans.x = l;
	ans.y = d;
	double cur = calc(l, d);

	//for (int i=l; i<=r; ++i)
	//	for (int j=d; j<=u; ++j){
	//		double now = calc(i, j);
	//		if (cur > now){
	//			cur = now;
	//			ans.x = i;
	//			ans.y = j;
	//		}
	//	}
	
	for (int i=l; i<=r; i+=100)
		for (int j=d; j<=u; j+=100){
			double now = calc(i, j);
			if (cur > now){
				cur = now;
				ans.x = i;
				ans.y = j;
			}
		}
	int nl, nd;
	//printf("%.1f %.1f %.1f\n", ans.x/10., ans.y/10., cur/10);
	for (int i=max(l, (nl=ans.x)-100); i<=nl+100; i+=10)
		for (int j=max(d, (nd=ans.y)-100); j<=nd+100; j+=10){
			double now = calc(i, j);
			if (cur > now){
				cur = now;
				ans.x = i;
				ans.y = j;
			}
		}

	//printf("%.1f %.1f %.1f\n", ans.x/10., ans.y/10., cur/10);
	for (int i=max(l, (nl=ans.x)-10); i<=nl+10; ++i)
		for (int j=max(d, (nd=ans.y)-10); j<=nd+10; ++j){
			double now = calc(i, j);
			if (cur > now){
				cur = now;
				ans.x = i;
				ans.y = j;
			}
		}

	printf("%.1f %.1f %.1f\n", ans.x/10., ans.y/10., cur/10);
	return 0;
}