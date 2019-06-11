#include <iostream>

using namespace std;

struct Point{
	double x, y;
	 Point();
	 Point(double, double);
	void output();
	bool operator==(Point);
	Point operator-(Point);
};

struct FuckingEdge{
	Point a, b;
	void output(){
		a.output();
		putchar(' ');
		b.output();
		putchar('\n');
	}
};

bool cross(Point, Point, FuckingEdge);

int test(){
	Point a, b;
	FuckingEdge c;
	cin >> a.x >> a.y >> b.x >> b.y >> c.a.x >> c.a.y >> c.b.x >> c.b.y;
	cout << cross(a, b, c);
	return 0;
}
