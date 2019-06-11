/*
ID:theodor8
PROG:ttwo
LANG:C++
*/
#include <iostream>
using namespace std;
#pragma warning(disable:4996)
//#define Debug

char forest[10][11];
bool seen[10][10][4][10][10][4];
int TIME;
const int add_x[] = {-1, 0, 1, 0},
	add_y[] = {0, 1, 0, -1};
struct X{
	int x, y, dir;
	bool inline ok();
	void inline go();
	void inline turn();
#ifdef Debug
	void inline output(const char* const);
#endif
}	john, cows;
bool X::ok(){
	int nx(x), ny(y);
	nx += add_x[dir];
	ny += add_y[dir];
	if (nx>=0 && nx<=9 && ny>=0 && ny<=9 && forest[nx][ny]!='*')
		return true;
	else
		return false;
}
void X::go(){
	x += add_x[dir];
	y += add_y[dir];
}
void X::turn(){
	++dir;
	if (dir == 4)
		dir = 0;
}
#ifdef Debug
void X::output(const char* const xx){
	printf("%s:\t", xx);
	printf("%d, %d\n", x, y);
}
#endif

inline void init(){
	for (int i=0; i<10; ++i)
		scanf("%s", forest[i]);
	for (int i=0; i<10; ++i)
		for (int j=0; j<10; ++j)
			if (forest[i][j] == 'F')
				john.x = i, john.y = j;
			else if (forest[i][j] == 'C')
				cows.x = i, cows.y = j;
	seen[john.x][john.y][john.dir][cows.x][cows.y][cows.dir] = true;
	john.dir = cows.dir = 0;
}
inline bool meet(){
	int x(cows.x), y(cows.y);
	x += add_x[cows.dir];
	y += add_y[cows.dir];
	if (x == john.x && y == john.y)
		return true;
	else
		return false;
}
inline void output(bool good){
	if (good)
		printf("%d\n", TIME);
	else
		printf("0\n");
	exit(0);
}
void inline go(){
	for (; ; ){
		++TIME;
		//Farmer goes
		if (john.ok())
			john.go();
		else
			john.turn();
		//Cows go, meet?
		if (meet())
			output(true);
		else if (cows.ok())
			cows.go();
		else
			cows.turn();
		const int &a(john.x),
			&b(john.y),
			&c(cows.x),
			&d(cows.y),
			&e(john.dir),
			&f(cows.dir);
		if (seen[a][b][e][c][d][f])
			output(false);
		else
			seen[a][b][e][c][d][f] = true;
#ifdef Debug
		if (seen[0][9][0][3])
			printf("Here!\n");
		printf("Time:%d\n", TIME);
		john.output("John");
		cows.output("Cows");
#endif
	}
}
int main(){
	freopen("ttwo.in", "r", stdin);
	freopen("ttwo.out", "w", stdout);
	init();
	go();
	return 0;
}
