#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cctype>
#include <cmath>

//#define DEBUG

const int MAXN = 30;
const int MAXH = 5;
const int MAXK = 5;
const int MAX_BINS = 1 << MAXK;
const int MAX_TRIS = 1 << (MAXK << 1);
const int MAXS = MAXN * MAXN * MAXH * MAX_TRIS;

#define IN_RANGE(nx, ny) (0 <= (nx) && (nx) < M && 0 <= (ny) && (ny) < N && map[nx][ny] != '#')
#define GET(S, p) (((S) >> ((p) << 1)) & 3)
#define MODIFY(S, p, x) ((S) | ((x) << ((p) << 1)))
#define SMODIFY(S, p, x) ((S) | ((x) << (p)))
#define SGET(S, p) (((S) >> (p)) & 1)

#define BLOCKED(x, y) (isalpha(map[x][y]) && GET(S, map[x][y] - 'A') != 1) 

int M, N, K, H;

double f[MAXS + 1], prob[MAX_TRIS][MAXK];
int id[MAXN][MAXN][MAXH][MAX_TRIS];
int id_cnt, P[MAX_BINS], Psum;

char map[MAXN][MAXN + 3];

void showbit(int x, const char *str) {
	for (int i = 0; i < K; i++) printf("%d ",GET(x, i));
	printf("%s", str);
}

void calc_prob(int step = 0, int inc = 0, int ucnt = 0) {

	if (step == K)
	{
#ifdef DEBUG
		showbit(inc, "\t");
#endif
		int tot = 0;
		for (int s = (1 << ucnt) - 1; s >= 0; s--)
		{
			int ts = 0, t;
			for (int i = 0, j = 0; i < K; i++)
				if ((t = GET(inc, i))) ts = SMODIFY(ts, i, t - 1);
				else ts = SMODIFY(ts, i, SGET(s, j)), j++;
			for (int i = 0; i < K; i++)
				if (!GET(inc, i) && SGET(ts, i)) prob[inc][i] += P[ts];
			tot += P[ts];
		}
		for (int i = 0; i < K; i++) prob[inc][i] /= tot;
#ifdef DEBUG
		for (int i = 0; i < K; i++) if (!GET(inc, i)) printf("%.3lf ", prob[inc][i]); printf("\n");
#endif
		return;
	}

	for (int i = 0; i < 3; i++)
		calc_prob(step + 1, MODIFY(inc, step, i), ucnt + (i == 0));
}


void pre_work() {

	scanf("%d %d %d %d", &M, &N, &K, &H);
	for (int i = 0; i < M; i++)
		scanf("%s", map[i]);
	for (int i = 0; i < (1 << K); i++)
		scanf("%d", P + i), Psum += P[i];

	calc_prob();
	memset(f, -1, sizeof(f));
}

const int det[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

struct Edge {

	int x, y;
	Edge *next;

} emem[MAXS + 1], *head[MAXS + 1];

int ecnt = 0;

void add(int x, int y, int nid) {

	emem[++ecnt].next = head[nid];
	head[nid] = emem + ecnt;
	emem[ecnt].x = x;
	emem[ecnt].y = y;
}

bool conn_search(int x, int y, int h, int S) {

	int &ptr = id[x][y][h][S];

	if (ptr) return 0;

	bool succ = 0;

	if (map[x][y] == '@') succ = 1;

	ptr = id_cnt;

	for (int d = 0; d < 4; d++)
	{
		int nx = det[d][0] + x,
			ny = det[d][1] + y;

		if (IN_RANGE(nx, ny)) 
		{
			if (BLOCKED(x, y) || BLOCKED(nx, ny)) add(nx, ny, id_cnt);
			else if (conn_search(nx, ny, h, S)) succ = 1;
		}
	}

	return succ;
}

void update(double &nptr, double v) { if (v > nptr) nptr = v; }

double dfs(int x, int y, int h, int S) {

	if (h < 0) return 0; // the life is everything !

	int nid = id[x][y][h][S];


	if (!nid)
	{
		nid = ++id_cnt;
		if (conn_search(x, y, h, S)) return f[nid] = 1;
	}

	if (!isnan(f[nid])) return f[nid];

	f[nid] = 0;


	for (Edge *ptr = head[nid]; ptr; ptr = ptr -> next)
	{
		int nx = ptr -> x, ny = ptr -> y;

		if (!isalpha(map[nx][ny])) update(f[nid], dfs(nx, ny, h, S));
		else
		{
			int type = map[nx][ny] - 'A', t;
			if ((t = GET(S, type))) // it is certain
				update(f[nid], dfs(nx, ny, h - (t - 1), S));
			else 
			{
				double istrap = prob[S][type];
				update(

						f[nid], 
						dfs(nx, ny, h - 1, MODIFY(S, type, 2)) * istrap + 
						dfs(nx, ny, h, MODIFY(S, type, 1)) * (1 - istrap)

					  );
			}
		}
	}
#ifdef DEBUG
	printf("f[%d, %d, %d, \t", x, y, h + 1); showbit(S, "");
	printf("] = %.5lf\n", f[nid]);
#endif
	return f[nid];
}

void work() {

	for (int i = 0; i < M; i++)
		for (int j = 0; j < N; j++)
			if (map[i][j] == '$') 
			{
				printf("%.3lf\n", dfs(i, j, H - 1, 0));
				return;
			}

}

int main() {

	pre_work();
	work();

	return 0;
}
