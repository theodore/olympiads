#include <cstdio>
#include <cstring>
#include <cstdlib>

//#define DEBUG
#define MAXN 50
#define MAXTYPE 3

int statA[MAXTYPE], statB[MAXTYPE];
int Map[MAXN + 1][MAXN + 1];
int N, A, B;


void pre_work() {

	scanf("%d %d %d\n", &N, &A, &B);

	static char buff[MAXN + 4];
	for (int i = 1; i <= N; i++)
	{
		fgets(buff, sizeof(buff), stdin);
		for (int j = 1; j <= N; j++)
		{
			char ch = buff[j - 1];
			if (ch == '+') Map[i][j] = 2;
			else if (ch == '-') Map[i][j] = 1;
			else if (ch == '=') Map[i][j] = 0;
			else Map[i][j] = -1;
		}
	}
}

bool vis[MAXN + 1];

int ans_lt, ans_eq, ans_gt;

int find_dir(int src, int dir) {

#define CONNECT(x, y) (Map[x][y] == 0 || Map[x][y] == dir)
#define INC(x, y) (Map[x][y] == 0 ? 0 : 1)

	static int dist[MAXN + 1];
	int res = 0;

	memset(vis, 0, sizeof(vis));
	memset(dist, 240, sizeof(dist));
	dist[src] = 0;

	for (int i = 1; i <= N; i++)
	{
		int max_dis = -1, max_id, t;
		for (int j = 1; j <= N; j++)
			if (!vis[j] && dist[j] > max_dis)
			{
				max_dis = dist[j];
				max_id = j;
			}
		vis[max_id] = 1;
		if (max_dis > res) res = max_dis;
		for (int j = 1; j <= N; j++)
			if (!vis[j] && CONNECT(max_id, j) && (t = max_dis + INC(max_id, j)) > dist[j]) 
				dist[j] = t;
	}

	return res;
}

struct constr_t {

	int st, ed;

} c[MAXN + 1];

bool modify(int X, int x, constr_t *tmp) {

	for (int i = 1; i <= N; i++)
		if (i != X)
		{
			switch (Map[X][i]) {

				case 0 : if (x > tmp[i].ed || x < tmp[i].st) return 0;
						 tmp[i].st = tmp[i].ed = x; break;
				case 1 : if (x + 1 > tmp[i].st) tmp[i].st = x + 1; break;
				case 2 : if (x - 1 < tmp[i].ed) tmp[i].ed = x - 1; break;
			}
			if (tmp[i].ed < tmp[i].st) return 0;
		}
	return 1;
}

void check(int X, int Y) {

	int lt = 0, eq = 0, gt = 0;

		constr_t tmp[MAXN + 1];
	for (int a = c[A].st; a <= c[A].ed; a++)
		for (int b = c[B].st; b <= c[B].ed; b++)
			for (int x = c[X].st; x <= c[X].ed; x++)
				for (int y = c[Y].st; y <= c[Y].ed; y++)
				{
					memcpy(tmp + 1, c + 1, N * sizeof(constr_t));
					tmp[X].st = tmp[X].ed = x;
					tmp[Y].st = tmp[Y].ed = y;
					tmp[A].st = tmp[A].ed = a;
					tmp[B].st = tmp[B].ed = b;
					if (!modify(A, a, tmp)) continue;
					if (!modify(B, b, tmp)) continue;
					if (!modify(X, x, tmp)) continue;
					if (!modify(Y, y, tmp)) continue;
					if (a + b == x + y) eq++;
					else if (a + b > x + y) gt++;
					else lt++;
				}
	if ((gt | eq) == 0 && lt)
	{
		ans_lt++;
#ifdef DB
		fprintf(stderr, "%d %d\n", X, Y);
#endif
	}
	if ((lt | eq) == 0 && gt)
	{
		ans_gt++;
#ifdef DB
		fprintf(stderr, "%d %d gt\n", X, Y);
#endif
	}
	if ((lt | gt) == 0 && eq)
	{
		ans_eq++;
#ifdef DB
		fprintf(stderr, "%d %d eq\n", X, Y);
#endif
	}
}

void work() {

	for (int i = 1; i <= N; i++)
	{
		constr_t &nptr = c[i];
		nptr.st = 1, nptr.ed = 3;
		nptr.ed -= find_dir(i, 1);
		nptr.st += find_dir(i, 2);
	}

	for (int k = 1; k <= N; k++)
		for (int i = 1; i <= N; i++)
			for (int j = 1; j <= N; j++)
				if (Map[i][k] >= 0 && Map[k][j] >= 0 && (Map[i][k] ^ Map[k][j]) != 3) // < > > <
					Map[i][j] = Map[i][k] ? Map[i][k] : Map[k][j];
#ifdef DEBUG
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++)
			printf("%2d", Map[i][j]);
		printf("\n");
	}

	for (int i = 1; i <= N; i++)
		printf("%d [%d ~ %d]\n", i, c[i].st, c[i].ed);
#endif

	for (int i = 1; i <= N; i++)
		if (i != A && i != B)
			for (int j = i + 1; j <= N; j++)
				if (j != A && j != B)
					check(i, j);
	printf("%d %d %d\n", ans_gt, ans_eq, ans_lt);
}

int main() {

	pre_work();
	work();

	return 0;
}
