/*
PROB:fc
LANG:C++
*/
#include <iostream>
#include <cmath>
#include <algorithm>
//#define Data

using namespace std;

struct P{
	double x, y;
	void swap(P&);
} point[10007];

void P::swap(P& r){
	::swap(x, r.x);
	::swap(y, r.y);
}

int n;

bool cmp(const P& a, const P& b){
	double da, db;
	if (abs((da = atan2(a.y-point[0].y, a.x-point[0].x)) - (db = atan2(b.y-point[0].y, b.x-point[0].x))) < 1e-6)
		return hypot(a.x-point[0].x, a.y-point[0].y) < hypot(b.x-point[0].x, b.y-point[0].y);
	return da < db;
}

class stack{
 public:
	int ele[10007];
	int num;
 public:
	 stack();
	int top();
	int top2();
	void pop();
	void push(int);
} s;
stack::stack()
	: num(0){
}
int stack::top(){
	return ele[num-1];
}
int stack::top2(){
	return ele[num-2];
}
void stack::pop(){
	--num;
}
void stack::push(int x){
	ele[num++] = x;
}

double det(P a, P b, P c){
	P A, B;
	A.x = b.x - a.x;
	A.y = b.y - a.y;
	B.x = c.x - a.x;
	B.y = c.y - a.y;
	return A.x*B.y - A.y*B.x;
}
void special(){
	if (n == 1){
		printf("0.00\n");
		exit(0);
	}
	double ans = hypot(point[1].x-point[0].x, point[1].y-point[0].y);
	printf("%.2f\n", 2*ans);
	exit(0);
}

#ifndef Data
int main()
{
	freopen("fc.in", "r", stdin);
	freopen("fc.out", "w", stdout);
	scanf("%d", &n);
	for (int i=0; i<n; ++i)
		scanf("%lf%lf", &point[i].x, &point[i].y);
	if (n < 3)
		special();
	int mini = 0;
	for (int i=1; i<n; ++i)
		if (point[i].y < point[mini].y || (abs(point[i].y - point[mini].y) < 1e-6 && point[i].x < point[mini].x))
			mini = i;
	point[0].swap(point[mini]);
	sort(point+1, point+n, cmp);
//	for (int i=0; i<n; ++i)
//		printf("%f %f\n", point[i].x, point[i].y);
	s.push(0);
	s.push(1);
	for (int next=2; next<n; ++next){
		int a = s.top2(), b = s.top();
		while (det(point[a], point[next], point[b]) > 0){
			s.pop();
			a = s.top2();
			b = s.top();
		}
		s.push(next);
	}
//	for (int i=0; i<s.num; ++i)
//		printf("%d ", s.ele[i]);
	double ans = 0;
#define next point[s.ele[(i+1) % s.num]]
#define now point[s.ele[i]]
	for (int i=0; i<s.num; ++i)
		ans += hypot(next.x-now.x, next.y-now.y);
#undef next
#undef now
	printf("%.2f\n", ans);
	return 0;
}
#else
int main(){
	freopen("fc.in", "w", stdout);
	srand(19940813);
	int n;
	while (n < 100 || n > 5000)
		n = rand();
	cout << n << endl;
	for (int i=0; i<n; ++i)
		cout << rand()/double(rand()%10) << ' ' << rand()/double(rand()%10) << endl;
	return 0;
}
#endif
