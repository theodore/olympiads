/*
PROB:rect1
LANG:C++
*/
#include <iostream>
#pragma warning(disable:4996)
//#define Debug

using namespace std;

int count_x(1), count_y(1), to_x[2012], to_y[2012];
short rect[2012][2012];

#ifdef Debug
void output(){
	for (int i=count_y-1; i>=0; --i){
		for (int j=0; j<count_x; ++j)
			printf("%d ", rect[j][i]);
		printf("\n");
	}
	printf("\n");
	for (int i=0; i<count_x; ++i)
		printf("%d ", to_x[i]);
	printf("\n");
	for (int i=0; i<count_y; ++i)
		printf("%d ", to_y[i]);
	printf("\n\n");
}
#endif
void lcut(int pos){
	if (!pos)
		return;
	int x = -1;
	for (int i=0; i<count_x; ++i)
		if (to_x[i] >= pos){
			x = i;
			break;
		}
	if (x == -1)
		x = count_x - 1;
	if (x && to_x[x-1] == pos-1)
		return;
	for (int i=count_x++; i>x; --i){
		to_x[i] = to_x[i-1];
		for (int j=0; j<count_y; ++j)
			rect[i][j] = rect[i-1][j];
	}
	to_x[x] = pos - 1;
}
void dcut(int pos){
	if (!pos)
		return;
	int y = -1;
	for (int i=0; i<count_y; ++i)
		if (to_y[i] >= pos){
			y = i;
			break;
		}
	if (y == -1)
		y = count_y - 1;
	if (y && to_y[y-1] == pos-1)
		return;
	for (int i=count_y++; i>y; --i){
		to_y[i] = to_y[i-1];
		for (int j=0; j<count_x; ++j)
			rect[j][i] = rect[j][i-1];
	}
	to_y[y] = pos - 1;
}

void cut(int x1, int y1, int x2, int y2, int c){
	lcut(x1);
	lcut(x2);
	dcut(y1);
	dcut(y2);
	for (int i=0; i<count_x; ++i)
		if (to_x[i] >= x1){
			x1 = i;
			break;
		}
	int t = x2;
	x2 = -1;
	for (int i=x1+1; i<count_x; ++i)
		if (to_x[i] >= t){
			x2 = i;
			break;
		}
	if (x2 == -1)
		x2 = count_x;
	for (int i=0; i<count_y; ++i)
		if (to_y[i] >= y1){
			y1 = i;
			break;
		}
	t = y2;
	y2 = -1;
	for (int i=y1+1; i<count_y; ++i)
		if (to_y[i] >= t){
			y2 = i;
			break;
		}
	if (y2 == -1)
		y2 = count_y;
#ifdef Debug
	output();
	printf("%d %d %d %d\n\n", x1, y1, x2, y2);
#endif
	for (int i=x1; i<x2; ++i)
		for (int j=y1; j<y2; ++j)
			rect[i][j] = c;
#ifdef Debug
	output();
#endif
}

int x, y;
void flood(){
	int sum(0);
	for (int c=1; ; ++c){
		int ans(0);
		for (int i=0; i<count_x; ++i){
			for (int j=0; j<count_y; ++j)
				if (rect[i][j] == c){
					int x = to_x[i], y = to_y[j];
					if (i)
						x -= to_x[i-1];
					else
						++x;
					if (j)
						y -= to_y[j-1];
					else
						++y;
#ifdef Debug
					printf("Found: %d, %d (%d, %d)\n", x, y, i, j);
#endif
					ans += x * y;
				}
		}
		if (ans){
			printf("%d %d\n", c, ans);
			if ((sum += ans) >= (x*y))
				exit(0);
		}
	}
}

int main(){
	freopen("rect1.in", "r", stdin);
	freopen("rect1.out", "w", stdout);
	int n;
	scanf("%d%d%d", &x, &y, &n);
	to_x[0] = x-1;
	to_y[0] = y-1;
	rect[0][0] = 1;
	for (int i=0; i<n; ++i){
		int x1, y1, x2, y2, color;
		scanf("%d%d%d%d%d", &x1, &y1, &x2, &y2, &color);
		cut(x1, y1, x2, y2, color);
	}
#ifndef Debug
	flood();
#endif
	return 0;
}
