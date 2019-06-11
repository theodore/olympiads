/*
PROB:fence4
LANG:C++
*/
#include <iostream>
#include <cmath>
//#define Debug
//#define Test

using namespace std;

struct Point{
	double x, y;
	 Point();
	 Point(double, double);
	void output();
	bool operator==(Point);
	Point operator-(Point);
} eye, point[210];

Point::Point(){}
Point::Point(double a, double b)
	:x(a), y(b){}
void Point::output(){
#ifdef Debug
	printf("%f %f", x, y);
#else
	printf("%.0f %.0f", x, y);
#endif
}
bool Point::operator==(Point oper){
	return hypot(x-oper.x, y-oper.y) < 1e-3;
}
Point Point::operator-(Point oper){
	return Point(x-oper.x, y-oper.y);
}

struct Edge{
	Point a, b;
	 Edge();
	 Edge(Point, Point);
	void output();
} edge[210];

Edge::Edge(){}
Edge::Edge(Point x, Point y){
	a = x;
	b = y;
}
void Edge::output(){
	a.output();
	putchar(' ');
	b.output();
	putchar('\n');
}

int n;
void init(){
	freopen("fence4.in", "r", stdin);
	freopen("fence4.out", "w", stdout);
	scanf("%d%lf%lf", &n, &eye.x, &eye.y);
	for (int i=0; i<n; ++i)
		scanf("%lf%lf", &point[i].x, &point[i].y);
	for (int i=0; i<n-2; ++i){
		edge[i].a = point[i];
		edge[i].b = point[i+1];
	}
	edge[n-2].a = point[0];
	edge[n-2].b = point[n-1];
	edge[n-1].a = point[n-2];
	edge[n-1].b = point[n-1];
}

int dlecmp(double x){
	if (abs(x) < 1e-6)
		return 0;
	else if (x > 0)
		return 1;
	else
		return -1;
}

double det(Point a, Point b){
	return a.x*b.y - a.y*b.x;
}

bool cross(Point start, Point end, Edge x){
	return dlecmp(det(end-start, x.a-start)) * dlecmp(det(end-start, x.b-start)) < 0 &&
			dlecmp(det(x.b-x.a, start-x.a)) * dlecmp(det(x.b-x.a, end-x.a)) < 0;
}

//is point[i] on ray eye->x?
bool on(int i, Point x){
	return !dlecmp(det(x-eye, point[i]-eye));
}

bool see(Point p, Point q){
//	cout << "see?" << endl;
//	p.output();
//	putchar(' ');
//	q.output();
//	putchar('\n\n');
	if (p == q)
		return false;

//	if (good(p) && good(q))
//		return true;

	bool badp, badq, all = false;
	for (int i=0; i<n; ++i){
		badp = cross(eye, p, edge[i]);
		badq = cross(eye, q, edge[i]);
		//add
		if (!badp && !(point[i] == p) && on(i, p))// && cross(eye, p, Edge(point[(i+1)%n], point[i?i-1:n-1])))
			badp = true;
		if (!badq && !(point[i] == q) && on(i, q))// && cross(eye, q, Edge(point[(i+1)%n], point[i?i-1:n-1])))
			badq = true;
		//end add
		if (badp && badq)
			return false;
		all |= badp || badq;
	}
	if (!all)
		return true;
	//add
//	for (int i=0; i<n; ++i)
//		if ()
//			return false;
//	return true;



	Point mid((p.x+q.x)/2, (p.y+q.y)/2);
	return see(p, mid) || see(mid, q);
}

bool can_see(int i){
//	cout << "can see " << i << '?' << endl;
//	edge[i].output();
	return see(edge[i].a, edge[i].b);
}

bool visible[210];
int num;
void getit(){
	for (int i=0; i<n; ++i){
//		cout << "Testing " << i << endl;
		if (can_see(i)){
			++num;
			visible[i] = true;
//			cout << "good " << i << endl;
		}
	}
	////////// output ///////////////
	printf("%d\n", num);
	for (int i=0; i<n; ++i)
		if (visible[i])
			edge[i].output();
}

#ifdef Test
int test();
#endif
int main(){
#ifdef Test
	test();
#else
	init();
//	cout << "init finished" << endl;
	getit();
#endif
	return 0;
}
