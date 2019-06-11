/*
PROB:camelot
LANG:C++
*/
#include <iostream>
#include <cmath>
#include <queue>
//#define FLOYD
//#define SP
//#define noprune
#define output ;// printf("meet(%d, %d), get(%d, %d), who %d, new %d\n", meet.x, meet.y, get.x, get.y, who, now);
//#define Test

using namespace std;

const int infinity = 1<<25;
int n, m;
int dist[31][31][31][31];
int dx[8] = {1, 2, 2, 1, -1, -2, -2, -1},
	dy[8] = {2, 1, -1, -2, -2, -1, 1, 2};
struct point{
	int x, y;
	inline bool operator!=(point);
} king, knight[800];
int knights;

bool point::operator!=(point a){
	return x!=a.x || y!=a.y;
}
#ifdef FLOYD
void floyd(){
	for (int x=0; x<n; ++x)
		for (int y=0; y<m; ++y)
			for (int dir=0; dir<8; ++dir){
				int nx = x + dx[dir],
					ny = y + dy[dir];
				if (nx>=0 && nx<=n && ny>=0 && ny<=m)
					dist[x][y][nx][ny] = dist[nx][ny][x][y] = 1;
			}
	//init for floyd above
	for (int k0=0; k0<n; ++k0)
		for (int k1=0; k1<m; ++k1)
			for (int i0=0; i0<n; ++i0)
				for (int i1=0; i1<m; ++i1)
					if ((i0!=k0 || i1!=k1) && dist[i0][i1][k0][k1])
						for (int j0=0; j0<n; ++j0)
							for (int j1=0; j1<m; ++j1)
if ((j0!=k0 || j1!=k1) && (j0!=i0 || j1!=i1) && dist[k0][k1][j0][j1] &&
	(!dist[i0][i1][j0][j1] || dist[i0][i1][j0][j1]>dist[i0][i1][k0][k1]+dist[k0][k1][j0][j1]))
	dist[i0][i1][j0][j1] = dist[j0][j1][i0][i1] = dist[i0][i1][k0][k1]+dist[k0][k1][j0][j1];
}
#endif
//inline bool ok(point a, int dir){
//	int nx = a.x + dx[dir],
//		ny = a.y + dy[dir];
//	return nx>=0 && nx<=n && ny>=0 && ny<=m;
//}

queue<point> q;
void search(point s){
	dist[s.x][s.y][s.x][s.y] = 0;
	q.push(s);
	while (!q.empty()){
		point now = q.front();
		q.pop();
		for (int dir=0; dir<8; ++dir){
			point to;
			to.x = now.x + dx[dir];
			to.y = now.y + dy[dir];
			if (to.x>=0 && to.x<n && to.y>=0 && to.y<m && dist[s.x][s.y][to.x][to.y]==infinity && to!=s){
				dist[s.x][s.y][to.x][to.y] = dist[s.x][s.y][now.x][now.y] + 1;
				q.push(to);
			}
		}
	}
}

void bfs(){
	point s;
//	s.x = s.y = 0;
//	search(s, s, 0);

	for (s.x=0; s.x<n; ++s.x)
		for (s.y=0; s.y<m; ++s.y)
			search(s);

}

void init(){
#ifndef Test
	freopen("camelot.in", "r", stdin);
	freopen("camelot.out", "w", stdout);
#endif
	scanf("%d%d", &m, &n);
	point s, e;
	for (s.x=0; s.x<n; ++s.x)
	for (s.y=0; s.y<m; ++s.y)
		for (e.x=0; e.x<n; ++e.x)
		for (e.y=0; e.y<m; ++e.y)
			dist[s.x][s.y][e.x][e.y] = infinity;
#ifdef FLOYD
	floyd();
#else
	bfs();
#endif
#ifdef SP
//	point s, e;
	for (s.x=0; s.x<n; ++s.x)
	for (s.y=0; s.y<m; ++s.y)
		for (e.x=0; e.x<n; ++e.x)
		for (e.y=0; e.y<m; ++e.y)
			printf("%d %d %d %d %d\n", s.x, s.y, e.x, e.y, dist[s.x][s.y][e.x][e.y]);
#endif
	///////////input
	char pos[5];
	int y;
	scanf("%s%d", pos, &y);
	king.x = pos[0] - 'A';
	king.y = y-1;
#ifdef Test
	for (int i=0; i<4; ++i){
		scanf("%s %d", pos, &y);
#else
	while (scanf("%s %d", pos, &y) != EOF){
#endif
		knight[knights].x = pos[0] - 'A';
		knight[knights++].y = y-1;
	}
}

int kingdist(int x, int y){
	return max(abs(x-king.x), abs(y-king.y));
}

#ifdef Test
void test(){
	int a, b, c, d;
	while (cin >> a >> b >> c >> d)
		cout << dist[a][b][c][d] << endl;
}
#else
void solve(){
#ifndef noprune
	//first choose someone to test
	int ans = 0;
	for (int i=0; i<knights; ++i)
		ans += dist[knight[i].x][knight[i].y][king.x][king.y];
	point meet, get;
	for (int i=0; i<knights; ++i){
		int now = kingdist(knight[i].x, knight[i].y);
		for (int j=0; j<knights; ++j){
			now += dist[knight[j].x][knight[j].y][knight[i].x][knight[i].y];
			if (now >= ans)
				goto pass;
		}
		if (now < ans)
			ans = now;
pass:;
	}
	//end test
#else
	point meet, get;
	int ans = 1<<30;
#endif
	for (meet.x=0; meet.x<n; ++meet.x)
		for (meet.y=0; meet.y<m; ++meet.y){
			int now = 0;
			for (int i=0; i<knights; ++i){
				now += dist[knight[i].x][knight[i].y][meet.x][meet.y];
#ifndef noprune
				if (now >= ans)
					goto next;
#endif
			}

			for (int who=0; who<knights; ++who){
				now -= dist[knight[who].x][knight[who].y][meet.x][meet.y];
				for (get.x=0; get.x<n; ++get.x)
					for (get.y=0; get.y<m; ++get.y){
						now += dist[knight[who].x][knight[who].y][get.x][get.y] + dist[get.x][get.y][meet.x][meet.y] +
							kingdist(get.x, get.y);
						if (now < ans){
							output
							ans = now;
						}
						now -= dist[knight[who].x][knight[who].y][get.x][get.y] + dist[get.x][get.y][meet.x][meet.y] +
							kingdist(get.x, get.y);
					}
				now += dist[knight[who].x][knight[who].y][meet.x][meet.y];
			}
next:;
		}
	printf("%d\n", ans);
}
#endif

int main(){
	init();
	if (!knights){
		printf("0\n");
		return 0;
	}
#ifdef Test
	test();
#else
	solve();
#endif
	return 0;
}
