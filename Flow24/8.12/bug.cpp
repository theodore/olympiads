#include <cstdio>
#include <cstring>
#include <queue>

const int Max_v = (1 << 20) + 11;
const int Max_e = 133;
int n, m;
int leng[Max_e];
char str[Max_e][2][23];

bool Good(int x, int e)
{
    for (int i = 0; i < n; i++)
        if (str[e][0][i] == '-' && (x & (1 << i)))
            return false;
        else if (str[e][0][i] == '+' && !(x & (1 << i)))
            return false;
    return true;
}

int Go(int x, int e)
{
    int r = x;
    for (int i = 0; i < n; i++)
        if (str[e][1][i] == '+')
            r |= 1 << i;
        else if (str[e][1][i] == '-')
            r &= ~(1 << i);
    return r;
}

int SPFA()
{
    static unsigned dist[Max_v];
    static bool in[Max_v];
    memset(dist, -1, sizeof dist);
    dist[(1 << n) - 1] = 0;
    std::queue<int> q;
    for (q.push((1 << n) - 1); !q.empty(); ) {
        int x = q.front();
        q.pop();
        in[x] = false;
        for (int e = 0; e < m; e++)
            if (Good(x, e)) {
                int z = Go(x, e);
                if (dist[x] + leng[e] < dist[z]) {
                    dist[z] = dist[x] + leng[e];
                    if (!in[z]) {
                        in[z] = true;
                        q.push(z);
                    }
                }
            }
    }
    return dist[0] == -1u ? 0 : dist[0];
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; i++)
        scanf("%d%s%s", &leng[i], str[i][0], str[i][1]);
    printf("%d\n", SPFA());
}
