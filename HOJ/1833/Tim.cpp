#include <iostream>

#define MAX(a,b) ((a) > (b) ? (a) : (b))
#define MIN(a,b) ((a) < (b) ? (a) : (b))
#define ll long long
#define L 13
using namespace std;

ll A,B;
ll f[L+1][10][10];
ll TEN[L+1];
void Init(){
     scanf("%I64d%I64d",&A,&B);
}
#define N 10
ll Num(int *a, int n){
   ll ret = 0;
   for (int i = n-1; i>=0; i--)
       ret = ret * 10 + a[i];
   return ret;
}

void Convert(ll A, int *a, int &len){
     len = 0;
     memset(a,0,sizeof(int)*(L+1));
     if (A == 0)
        a[len++] = 0;
     while (A)
           a[len++] = A%10, A /= 10;
}

void dfs(int *b, int len, ll *ans){
     if (len == 0) return;
     if (len == 1){
        for (int i = 0; i<=b[0]; i++)
            ans[i]++;
        return;
     }
     for (int i = 0; i<b[len-1]; i++)
         for (int k = 0; k<N; k++)
             ans[k] += f[len-1][i][k];
     ans[b[len-1]] += Num(b,len-1)+1;
     dfs(b,len-1,ans);
}

void Deal(ll B, ll *ans){
     memset(ans,0,sizeof(int)*10);
     if (B == -1) return;
     if (B == 0){
           ans[0]++;
           return;
     }
     int b[L+1] = {0},len;
     Convert(B,b,len);
     ans[0]++;
     for (int i = 0; i<len-1; i++)
         for (int j = 1; j<N; j++)
             for (int k = 0; k<N; k++)
                 ans[k] += f[i][j][k];
     for (int i = 1; i<b[len-1]; i++)
         for (int k = 0; k<N; k++)
             ans[k] += f[len-1][i][k];
     ans[b[len-1]] += 1+Num(b,len-1);
     dfs(b,len-1, ans);
}

void Solve(){
     A--;
     for (int i = 0; i<N; i++)
         f[0][i][i] = 1;
     TEN[0] = 1;
     for (int i = 1; i<=L; i++)
         TEN[i] = TEN[i-1] * (10ll);
     for (int i = 1; i<L; i++)
         for (int j = 0; j<N; j++)
             for (int k = 0; k<N; k++){
                 for (int l = 0; l<N; l++)
                     f[i][j][k] += f[i-1][l][k];
                 if (j == k)
                    f[i][j][k] += TEN[i];
             }
     ll a[10] = {0}, b[10] = {0};
     Deal(A,a);
     Deal(B,b);
     for (int i = 0; i<N; i++)
         printf("%I64d ",b[i]-a[i]);
}


int main(){
    Init();
    Solve();
    return 0;
}
