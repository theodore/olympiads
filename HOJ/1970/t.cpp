#include <iostream>
#include <cstdio>
#include <cstring>

#define TEN 10000
#define MAX(a,b) ((a) > (b) ? (a) : (b))
#define MIN(a,b) ((a) < (b) ? (a) : (b))

using namespace std;

class INT{
public:
    int a[17];
    INT(){memset(a,0,sizeof(a)); a[0] = 1;}
    INT(int n) {memset(a,0,sizeof(a)); a[0] = 1;a[1] = n;}
    friend INT operator + (const INT &a, const INT &b){
        INT c;
        int len = MAX(a.a[0],b.a[0]);
        for (int i = 1; i<=len; i++)
            c.a[i] += a.a[i] + b.a[i],
                c.a[i+1] += c.a[i] / TEN,
                c.a[i] %= TEN;
        while (c.a[len+1]) len++;
        c.a[0] = len;
        return c;
    }
    friend INT operator * (const INT &a, int b){
        INT c;
        for (int i = 1; i<=a.a[0]; i++)
            c.a[i] += a.a[i] * b,
                c.a[i+1] += c.a[i] / TEN,
                c.a[i] %= TEN;
        int len = a.a[0];
        while (c.a[len+1]){
            len++;
            c.a[len+1] = c.a[len] / TEN;
            c.a[len] %= TEN;
        }
        c.a[0] = len;
        return c;
    }
    void Out(){
        printf("%d",a[a[0]]);
        for (int i = a[0]-1; i>=1; i--){
            int t = TEN/10;
            while (t){
                printf("%d",(a[i]/t)%10);
                t/=10;
            }
        }
    }
};

int K;
char s[201];
int p = 0;
INT er[101];
INT dfs(int k){
    if (k == 0)
        return s[p++] == 0 ? 1 : 0;
    INT ret = 0;
    if (s[p] != 2){
        int t = s[p++];
        if (t == 0)
            return er[k<<1];
        return 0;
    }
    p++;
    for (int i = 1; i<=4; i++)
        ret = ret + dfs(k-1);
    return ret;
}
int main(){
    scanf("%d",&K);
    scanf("%s",s);
    int len = strlen(s);
    for (int i = 0; i<len; i++)
        s[i] -= '0';
    er[0] = 1;
    for (int i = 1; i<=(K<<1); i++)
        er[i] = er[i-1] * 2;
    dfs(K).Out();
    cout << endl;
    return 0;
}
