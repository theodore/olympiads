/** @file maze.cpp
 *  @brief SDOI2011, Round 1, Day 2, Problem 3, maze.
 *  We use f[i][j][s][h] to denote the probability to leave the maze from
 *  point (i, j) with h HP and ternary number s as information on the maze, in
 *  which the ith bit indicates our knowledge of trap type i: doesn't hurt(0),
 *  hurts(1), unknow(2).
 *  @author Theodore You <theodoreyou@gmail.com>
 *  @date Wed, 13 Apr 2011 10:46:14 +0800
 */

#include <cstdio>
#include <cstring>
#include <cctype>
#include <cmath>
#include <vector>
#include <utility>
#include <algorithm>

const char M_wall = '#';
const char M_start = '$';
const char M_end = '@';
const int dx[] = {-1, 0, 1, 0};
const int dy[] = {0, -1, 0, 1};
const int maxn = 37;
const int maxk = 5;
const int maxh = 7;
const int maxs = 1 << maxk << maxk;
int n, m, k, hp;
char maze[maxn][maxn];
double pr[maxs];
double f[maxn][maxn][maxs][maxh];
bool done[maxn][maxn][maxs][maxh];
bool vis[maxn][maxn];
//bool (*vis)[maxn];
typedef std::vector<std::pair<int, int> > Neighbor;

bool fill(const int x, const int y, const int s, Neighbor& list)
{
    vis[x][y] = true;
    for (int d = 0; d < 4; ++d)
    {
	const int nx = x + dx[d];
	const int ny = y + dy[d];
	if (!vis[nx][ny] && maze[nx][ny] != M_wall)
	{
	    if (isupper(maze[nx][ny]) && (s >> 2 * (maze[nx][ny] - 'A') & 3) != 0)
	    {
		list.push_back(std::make_pair(nx, ny));
		vis[nx][ny] = true;
		continue;
	    }
	    else if (maze[nx][ny] == M_end)
		return true;
	    if (fill(nx, ny, s, list))
		return true;
	}
    }
    return false;
}

double ff(const int x, const int y, const int s, const int h)
{
#if DB >= 1
    fprintf(stderr, "ff %d %d %d %d\n", x, y, s, h);
#endif
    double& z = f[x][y][s][h];
    Neighbor list;
    if (done[x][y][s][h])
	goto ret;
    if (h == 0)
    {
	z = 0;
	done[x][y][s][h] = true;
	goto ret;
    }
    //static bool largevis[ * maxs][maxn][maxn];
    //static int lvc = 0;
    //vis = largevis[lvc++];
    memset(vis, 0, sizeof vis);
    if (fill(x, y, s, list))
    {
	done[x][y][s][h] = true;
	z = 1;
	goto ret;
    }
#if DB >= 1
    fprintf(stderr, "size = %d\n", list.size());
#endif
    for (size_t i = 0; i < list.size(); ++i)
    {
	const int xp = list[i].first;
	const int yp = list[i].second;
#if DB >= 1
	fprintf(stderr, "x' = %d, y' = %d\n", xp, yp);
#endif
	const int id = maze[xp][yp] - 'A';
	int t;
	if ((t = (s >> id >> id) & 3) == 2)
	{
	    double d = 0;
	    int sp = s;
	    sp ^= 2 << id << id;
	    for (int j = 0; j < 2; ++j)
	    {
		sp |= j << id << id;
		if (std::abs(pr[s]) > 1e-6)
		    d += pr[sp] / pr[s] * ff(xp, yp, sp, h - j);
	    }
	    z = std::max(z, d);
	}
	else
	    z = std::max(z, ff(xp, yp, s, h - t));
    }
    done[x][y][s][h] = true;
ret:
#if DB >= 1
    fprintf(stderr, "f[%d %d %d %d] = %f\n\n", x, y, s, h, z);
#endif
    return z;
}


int tmp[1 << maxk];

bool check(const int a, const int b)
{
    for (int i = 0, t; i < k; ++i)
	if ((t = (a >> i >> i) & 3) != 2 && ((b >> i) & 1) != t)
	    return false;
    return true;
}

void initpr(int p = 0, int s = 0)
{
    if (p == k)
    {
	for (int i = 0; i < (1 << k); ++i)
	    if (check(s, i))
		pr[s] += tmp[i];
	pr[s] /= tmp[1 << k];
#if DB >= 1
	fprintf(stderr, "pr[%d] = %f\n", s, pr[s]);
#endif
	return;
    }
    initpr(p + 1, s << 2);
    initpr(p + 1, s << 2 | 1);
    initpr(p + 1, s << 2 | 2);
}

int main()
{
    scanf("%d%d%d%d", &n, &m, &k, &hp);
    if (n == 0)
	return 0;
    memset(maze[0], M_wall, sizeof maze[0]);
    memset(maze[n + 1], M_wall, sizeof maze[0]);
    int sx, sy;
    for (int i = 1; i <= n; ++i)
    {
	maze[i][0] = M_wall;
	scanf("%s", maze[i] + 1);
	maze[i][m + 1] = M_wall;
	for (int j = 1; j <= m; ++j)
	    if (maze[i][j] == M_start)
		sx = i, sy = j;
    }
    for (int i = 0; i < (1 << k); ++i)
	scanf("%d", &tmp[i]), tmp[1 << k] += tmp[i];
    initpr();
    int z = 0;
    for (int i = 0; i < k; ++i)
	z |= 2 << i << i;
    printf("%.3f\n", ff(sx, sy, z, hp));
}
