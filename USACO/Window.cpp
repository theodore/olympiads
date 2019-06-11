/*
PROB: window
LANG: C++
*/
#pragma warning(disable: 4996)
#include <iostream>
#include <cstring>
#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))
//#define Debug
//#define NO_CALC
//#define NO_OUT

using namespace std;

char str[30];

struct P{
	int x, y;
#ifdef NO_CALC
	void output(){
		printf("%d %d", x, y);
	}
#endif
};

struct R{
	static int top, bottom;
	P a, b;
	int next;

	 R();
	 R(int, int, int, int);
	inline bool used();
	inline int area();
#ifdef NO_CALC
	void output(){
		a.output();
		putchar(' ');
		b.output();
		putchar('\n');
	}
#endif
} rect[70];

R::R(){}

R::R(int x1, int y1, int x2, int y2){
	a.x = x1;
	a.y = y1;
	b.x = x2;
	b.y = y2;
}

bool R::used(){
	return next!=0;
}

int R::area(){
	return (b.x - a.x) * (b.y - a.y);
}

int R::top = -1, R::bottom = -1;

int h(char x){
	if (x >= 'a' && x <= 'z')
		return x - 'a' + 1;
	else if (x >= 'A' && x <= 'Z')
		return x - 'A' + 27;
	else
		return x - '0' + 53;
}

void destroy(char p){
	const int id = h(p);
	if (R::bottom == id){
		if ((R::bottom = rect[id].next) == -1)
			R::top = -1;
	}
	else
		for (int now = R::bottom; ; now=rect[now].next)
			if (rect[now].next == id){
				if ((rect[now].next = rect[id].next) == -1)
					R::top = now;
				break;
			}
	rect[id].next = 0;
}

void create(char p0, int p1, int p2, int p3, int p4){
	R now(min(p1, p3), min(p2, p4), max(p1, p3), max(p2, p4));
	const int id = h(p0);
	if (rect[id].used())
		destroy(p0);
	if (R::top == -1){
		rect[R::top = R::bottom = id] = now;
		rect[id].next = -1;
	}
	else{
		rect[R::top].next = id;
		rect[id] = now;
		rect[R::top = id].next = -1;
	}
}

void top(char p){
	const int id = h(p);
#define p1 rect[id].a.x
#define p2 rect[id].a.y
#define p3 rect[id].b.x
#define p4 rect[id].b.y
	destroy(p);
	create(p, p1, p2, p3, p4);
#undef p1
#undef p2
#undef p3
#undef p4
}

void bottom(char p){
	const int id = h(p);
#ifdef Debug
	rect[id].output();
#endif
	destroy(p);
#ifdef Debug
	rect[id].output();
	printf("\n");
#endif
	rect[id].next = R::bottom;
	R::bottom = id;
}

int area(R now, int n){
#define rn rect[n]
	if (n == -1)
		return now.area();
	if (rn.a.x >= now.b.x || rn.a.y >= now.b.y || rn.b.x <= now.a.x || rn.b.y <= now.a.y)
		return area(now, rn.next);
	int ret(0);
	if (rn.a.x > now.a.x)
		ret += area(R(now.a.x, now.a.y, rn.a.x, now.b.y), rn.next);
	if (rn.b.x < now.b.x)
		ret += area(R(rn.b.x, now.a.y, now.b.x, now.b.y), rn.next);
	if (rn.a.y > now.a.y)
		ret += area(R(max(now.a.x, rn.a.x), now.a.y, min(now.b.x, rn.b.x), rn.a.y), rn.next);
	if (rn.b.y < now.b.y)
		ret += area(R(max(now.a.x, rn.a.x), rn.b.y, min(now.b.x, rn.b.x), now.b.y), rn.next);
#undef rn
	return ret;
}

inline void output(char p){
#ifndef NO_CALC
	const int id = h(p);
	printf("%.3f\n", 100.*area(rect[id], rect[id].next)/rect[id].area());
#else
	for (int i=R::bottom; i!=-1; i=rect[i].next)
		rect[i].output();
	putchar('\n');
#endif
}

int main(){
	freopen("window.in", "r", stdin);
#ifndef NO_OUT
	freopen("window.out", "w", stdout);
#endif
	while (scanf("%s", str) != EOF)
		switch(str[0]){
		case 'w':
			char a;
			int b, c, d, e;
			sscanf(str, "w(%c,%d,%d,%d,%d)", &a, &b, &c, &d, &e);
			create(a, b, c, d, e);
			break;
		case 't':
			top(str[2]);
			break;
		case 'b':
			bottom(str[2]);
			break;
		case 'd':
			destroy(str[2]);
			break;
		case 's':
			output(str[2]);
			break;
		}
	return 0;
}
