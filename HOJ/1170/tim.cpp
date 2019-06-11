#include <cstdio>
#include <map>
#include <vector>
#include <algorithm>
 
using namespace std;
 
typedef int Hash_t;
map<Hash_t, vector<pair<int, int> > > cnt_hash;
 
const int N = 1002;
char a[N][N];
int X, Y;
int n, m;
 
const int BASE = 257;
 
Hash_t hash_row[N][N];
 
Hash_t hash_len_pow;
Hash_t hash_len_pow_X;
 
int main()
{
    scanf("%d%d\n", &n, &m);
    for (int i = 0; i < n; i ++)
        gets(a[i]);
    scanf("%d%d", &X, &Y);
 
    hash_len_pow = 1;
    for (int i = 0; i < Y - 1; i ++)
        hash_len_pow = hash_len_pow * BASE;
    Hash_t tmp = hash_len_pow * BASE;
    hash_len_pow_X = 1;
    for (int i = 0; i < X - 1; i ++)
        hash_len_pow_X = hash_len_pow_X * tmp;
 
    for (int i = 0; i < n; i ++)
    {
        Hash_t val = 0;
        char *tch = a[i];
        for (int j = 0; j < Y; j ++, tch ++)
            val = val * BASE + (*tch);
        char *hch = a[i];
        for (int j = Y - 1; j < m; j ++, hch ++, tch ++)
        {
            hash_row[i][j] = val;
            val = (val - (*hch * hash_len_pow)) * BASE  + *tch;
        }
    }
 
    int ans = 0, ans_val;
    for (int end = Y - 1; end < m; end ++)
    {
        Hash_t val = 0;
        for (int i = 0; i < X; i ++)
            val = val * hash_len_pow * BASE +  hash_row[i][end];
        for (int i = X - 1; i < n; i ++)
        {
            cnt_hash[val].push_back(make_pair(i - X + 1, end - Y + 1));
            int t = cnt_hash[val].size();
            if (t > ans)
            {
                ans = t;
                ans_val = val;
            }
            val = (val - hash_row[i - X + 1][end] * hash_len_pow_X) * hash_len_pow * BASE
                + hash_row[i + 1][end];
        }
    }
     
    printf("%d %d\n", X, Y);
 
    vector<pair<int, int> > &ret = cnt_hash[ans_val];
    int startx = ret[0].first, starty = ret[0].second;
    for (int i = startx; i < startx + X; i ++, printf("\n"))
        for (int j = starty; j < starty + Y; j ++)
            printf("%c", a[i][j]);
    printf("%d\n", ret.size());
    sort(ret.begin(), ret.end());
    for (int i = 0; i < ret.size(); i ++)
        printf("%d %d\n", ret[i].first + 1, ret[i].second + 1);
    return 0;
}
