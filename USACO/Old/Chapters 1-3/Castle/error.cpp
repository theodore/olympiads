/*
ID:theodor8
PROB:castle
LANG:C++
*/
#include <iostream>
using namespace std;
#pragma warning(disable:4996)
#define Debug

//1(1<<0): wall to the west
//2(1<<1): wall to the north
//4(1<<2): wall to the east
//8(1<<3): wall to the south
const int add_v[] = {0, -1, 0, 1},
	add_h[] = {-1, 0, 1, 0};
int m, n, room[55][55], of_com[55][55], room_num, com_area[55];
bool visited[55][55];
void go(const int& v, const int& h, const int bullshit){
#ifdef Debuged
	printf("Came in, %d\t", room_num);
#endif
	visited[v][h] = true;
#ifdef Debuged
	printf("Now, %d\t\t", room_num);
#endif
	++com_area[of_com[v][h]=bullshit];
#ifdef Debuged
	printf("B4 the loop, %d\t", room_num);
#endif
	for (int dir=0; dir<4; ++dir)
		if (!(room[v][h] & (1<<dir))){
			int new_v(v + add_v[dir]),
				new_h(h + add_h[dir]);
			if (!visited[new_v][new_h])
				go(new_v, new_h, bullshit);
		}
}
struct {
	int ans, v, h;
	bool north;//true if at north
}	largest;
void calc(){
	for (int i=0; i<n; ++i)
		for (int j=0; j<m; ++j)
			if (!visited[i][j]){
#ifdef Debuged
				printf("B4 going, %d\t", room_num);
#endif
				go(i, j, room_num);
#ifdef Debuged
				printf("B4 addition, %d\t\t", room_num);
#endif
				++room_num;
#ifdef Debuged
				printf("(%d, %d), Added one\t%d\n", i, j, room_num);
#endif
			}
	//remove a wall
	int ans_at_n(m);
	for (int j=m-1; j>=0; --j)
		for (int i=0; i<n; ++i){
			//E first then N
			int& self(of_com[i][j]);
			if (j+1<m && self!=of_com[i][j+1] && com_area[self]+com_area[of_com[i][j+1]]>=largest.ans){
				//to update?
				if (com_area[self]+com_area[of_com[i][j+1]]==largest.ans && ans_at_n==j)
					goto out;
				largest.ans = com_area[self]+com_area[of_com[i][j+1]];
				largest.v = i;
				largest.h = j;
				largest.north = false;
			}
out:
			if (i && self!=of_com[i-1][j] && com_area[self]+com_area[of_com[i-1][j]]>=largest.ans){
				largest.ans = com_area[self]+com_area[of_com[i-1][j]];
				largest.v = i;
				largest.h = j;
				largest.north = true;
				ans_at_n = j;
			}
		}
}
int main(){
	freopen("castle.in", "r", stdin);
	freopen("castle.out", "w", stdout);
	scanf("%d%d", &m, &n);
	for (int i=0; i<n; ++i)
		for (int j=0; j<m; ++j)
			scanf("%d", &room[i][j]);
	calc();
	//output
#ifdef Debug
	for (int i=0; i<2; ++i){
		for (int j=0; j<50; ++j)
			printf("%d ", of_com[i][j]);
		printf("\n");
	}
#else
	printf("%d\n", room_num);
	int best(0);
	for (int i=0; i<room_num; ++i)
		best = best>com_area[i]?best:com_area[i];
	printf("%d\n", best);
	printf("%d\n", largest.ans);
	printf("%d %d ", largest.v+1, largest.h+1);
	if (largest.north)
		printf("N\n");
	else
		printf("E\n");
#endif
	return 0;
}
