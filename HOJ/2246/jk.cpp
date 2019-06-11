/**************************************************************
    Problem: 2246
    User: jiakai
    Language: C++
    Result: Accepted
    Time:180 ms
    Memory:277348 kb
****************************************************************/
 
#define STDIO
/*
 * $File: maze.cpp
 * $Date: Fri Apr 08 16:53:45 2011 +0800
 */
 
#define INPUT   "maze.in"
#define OUTPUT  "maze.out"
 
#include <cstdio>
#include <cassert>
 
namespace Solve
{
    const int NRC_MAX = 35,
          NTRAP_MAX = 6,
          HP_MAX = 6;
#define MAP_IS_EMPTY(x) ((x) == '.' || (x) == '$' || (x) == '@')
#define MAP_IS_WALL(x)  ((x) == '#')
#define MAP_IS_SRC(x)   ((x) == '$')
#define MAP_IS_TARGET(x)    ((x) == '@')
#define MAP_IS_TRAP(x)  ((x) >= 'A' && (x) <= 'Z')
#define MAP_GET_TRAP_NUM(x) ((x) - 'A')
 
    char map[NRC_MAX][NRC_MAX];
    int prob[1 << NTRAP_MAX];
    int nrow, ncol, ntrap;
 
    struct Coord_t
    {
        int row, col;
        inline void set(int r, int c)
        { row = r; col = c; }
    };
    Coord_t queue[NRC_MAX * NRC_MAX];
    int queue_size;
 
    // mask[i]:
    //  0: unknown
    //  1: safe
    //  2: dangerous
 
    int bfs_adj(Coord_t *adj, int row, int col, int mask);
    // find adjacent traps
    // return: -1 if target is encountered, or number of adjacent traps otherwise
    // global variables queue and queue_size are set accordingly
 
    double calc_f(int row, int col, int mask, int hp);
    double get_trap_safe_prob(int mask, int trap);
 
    void solve(FILE *fin, FILE *fout);
}
 
void Solve::solve(FILE *fin, FILE *fout)
{
    int hp;
    fscanf(fin, "%d%d%d%d", &nrow, &ncol, &ntrap, &hp);
    for (int i = 0; i < nrow; i ++)
        fscanf(fin, "%s", map[i]);
    for (int i = 0; i < (1 << ntrap); i ++)
        fscanf(fin, "%d", &prob[i]);
 
    for (int i = 0; i < nrow; i ++)
        for (int j = 0; j < ncol; j ++)
            if (MAP_IS_SRC(map[i][j]))
            {
                fprintf(fout, "%.3lf\n", calc_f(i, j, 0, hp));
                return;
            }
}
 
double Solve::get_trap_safe_prob(int mask, int trap)
{
    int stot = 0, s = 0;
    for (int i = 0; i < (1 << ntrap); i ++)
    {
        bool ok = true;
        for (int j = 0; j < ntrap; j ++)
        {
            int t = (mask >> (j << 1)) & 3;
            if (t && ((i >> j) & 1) != t - 1)
            {
                ok = false;
                break;
            }
        }
        if (ok)
        {
            stot += prob[i];
            if (!(i & (1 << trap)))
                s += prob[i];
        }
    }
    if (!stot)
        return 0;
    return double(s) / stot;
}
 
int Solve::bfs_adj(Coord_t *adj, int row, int col, int mask)
{
    int nadj = 0, qh = 0, qt = 1;
    static int visited[NRC_MAX][NRC_MAX], vis_test;
    vis_test ++;
    queue[0].set(row, col);
    visited[row][col] = vis_test;
    while (qh < qt)
    {
        int r0 = queue[qh].row,
            c0 = queue[qh].col;
        qh ++;
        static const int
            DR[] = {-1, 0, 1, 0},
            DC[] = {0, -1, 0, 1};
 
        for (int i = 0; i < 4; i ++)
        {
            int r1 = r0 + DR[i],
                c1 = c0 + DC[i];
            if (r1 < 0 || r1 >= nrow || c1 < 0 || c1 >= ncol ||
                    MAP_IS_WALL(map[r1][c1]) || visited[r1][c1] == vis_test)
                continue;
            visited[r1][c1] = vis_test;
            if (MAP_IS_TRAP(map[r1][c1]))
            {
                int tnum = MAP_GET_TRAP_NUM(map[r1][c1]);
                if (((mask >> (tnum << 1)) & 3) != 1)
                {
                    adj[nadj ++].set(r1, c1);
                    continue;
                }
            }
            queue[qt ++].set(r1, c1);
        }
    }
    queue_size = qt;
    for (int i = 0; i < qt; i ++)
        if (MAP_IS_TARGET(map[queue[i].row][queue[i].col]))
            return -1;
    return nadj;
}
 
double Solve::calc_f(int row, int col, int mask, int hp)
{
    static bool f_done[NRC_MAX][NRC_MAX][1 << (NTRAP_MAX * 2)][HP_MAX];
    static double f[NRC_MAX][NRC_MAX][1 << (NTRAP_MAX * 2)][HP_MAX];
    static Coord_t adj[NRC_MAX * NRC_MAX * NRC_MAX * NRC_MAX];
    static int nadj_tot;
    if (hp <= 0)
        return 0;
 
    if (f_done[row][col][mask][hp])
        return f[row][col][mask][hp];
 
    double ans = 0;
    int nadj = bfs_adj(adj + nadj_tot, row, col, mask), nadj_tot_orig = nadj_tot;
    if (nadj == -1)
        ans = 1;
    else
    {
        nadj_tot += nadj;
        for (int i = 0; i < nadj; i ++)
        {
            int r1 = adj[i + nadj_tot_orig].row,
                c1 = adj[i + nadj_tot_orig].col;
            assert(MAP_IS_TRAP(map[r1][c1]));
            int tnum = MAP_GET_TRAP_NUM(map[r1][c1]);
            if ((mask >> (tnum << 1)) & 3)
            {
                assert(((mask >> (tnum << 1)) & 3) == 2);
                double tmp = calc_f(r1, c1, mask, hp - 1);
                if (tmp > ans)
                    ans = tmp;
            } else
            {
                double prob = get_trap_safe_prob(mask, tnum),
                       tmp = calc_f(r1, c1, mask | (1 << (tnum << 1)), hp) * prob +
                           calc_f(r1, c1, mask | (2 << (tnum << 1)), hp - 1) * (1 - prob);
                if (tmp > ans)
                    ans = tmp;
            }
        }
        nadj_tot = nadj_tot_orig;
    }
 
    if (!MAP_IS_TRAP(map[row][col]) || ((mask >> (MAP_GET_TRAP_NUM(map[row][col]) << 1)) & 3) != 2)
    {
        if (nadj != -1)
            bfs_adj(adj + nadj_tot, row, col, mask);
        for (int i = 0; i < queue_size; i ++)
        {
            int r = queue[i].row, c = queue[i].col;
            f_done[r][c][mask][hp] = true;
            f[r][c][mask][hp] = ans;
        }
    } else
    {
        f_done[row][col][mask][hp] = true;
        f[row][col][mask][hp] = ans;
    }
    return ans;
}
 
int main()
{
#ifdef STDIO
    Solve::solve(stdin, stdout);
#else
    FILE *fin = fopen(INPUT, "r"),
         *fout = fopen(OUTPUT, "w");
    Solve::solve(fin, fout);
    fclose(fin);
    fclose(fout);
#endif
}
